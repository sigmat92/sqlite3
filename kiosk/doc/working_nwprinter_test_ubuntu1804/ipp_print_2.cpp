// ipp_print_1.cpp
//
// Minimal embedded IPP print client
// Supports:
//   - image/pwg-raster
//   - image/jpeg
//
// BUILD:
//   g++ ipp_print_1.cpp -o ipp_print_1
//
// RUN:
//   ./ipp_print_1 valid.pwg 192.168.45.167
//
// TESTED TARGET:
// HP LaserJet M208dw AirPrint/IPP printer

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

#define IPP_PORT 631

// ============================================================
// FORMAT
// ============================================================

enum Format {
    PWG,
    JPEG,
    UNKNOWN
};

Format detectFormat(const string& file)
{
    ifstream f(file, ios::binary);

    if (!f)
        return UNKNOWN;

    vector<unsigned char> buf(64, 0);

    f.read((char*)buf.data(), buf.size());

    // --------------------------------------------------------
    // PWG Raster detection
    // --------------------------------------------------------

    for (size_t i = 0; i + 3 < buf.size(); i++)
    {
        if (buf[i]     == 'R' &&
            buf[i + 1] == 'a' &&
            buf[i + 2] == 'S' &&
            buf[i + 3] == '2')
        {
            return PWG;
        }
    }

    // --------------------------------------------------------
    // JPEG detection
    // --------------------------------------------------------

    if (buf[0] == 0xFF &&
        buf[1] == 0xD8)
    {
        return JPEG;
    }

    return UNKNOWN;
}

string mimeType(Format f)
{
    switch (f)
    {
        case PWG:
            return "image/pwg-raster";

        case JPEG:
            return "image/jpeg";

        default:
            return "";
    }
}

// ============================================================
// HELPERS
// ============================================================

void appendUint16(vector<uint8_t>& v, uint16_t val)
{
    v.push_back((val >> 8) & 0xFF);
    v.push_back(val & 0xFF);
}

void appendUint32(vector<uint8_t>& v, uint32_t val)
{
    v.push_back((val >> 24) & 0xFF);
    v.push_back((val >> 16) & 0xFF);
    v.push_back((val >> 8) & 0xFF);
    v.push_back(val & 0xFF);
}

void addIPPString(
    vector<uint8_t>& ipp,
    uint8_t tag,
    const string& name,
    const string& value)
{
    ipp.push_back(tag);

    appendUint16(ipp, name.size());

    ipp.insert(
        ipp.end(),
        name.begin(),
        name.end());

    appendUint16(ipp, value.size());

    ipp.insert(
        ipp.end(),
        value.begin(),
        value.end());
}

// ============================================================
// MAIN
// ============================================================

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Usage:\n";
        cout << "./ipp_print_1 file printer_ip\n";
        return 1;
    }

    string filename = argv[1];
    string printerIP = argv[2];

    // --------------------------------------------------------
    // Detect format
    // --------------------------------------------------------

    Format fmt = detectFormat(filename);

    if (fmt == UNKNOWN)
    {
        cout << "Unsupported file format\n";
        return 1;
    }

    cout << "Detected format: "
         << mimeType(fmt)
         << endl;

    // --------------------------------------------------------
    // Read file
    // --------------------------------------------------------

    ifstream in(filename, ios::binary);

    if (!in)
    {
        cout << "Cannot open file\n";
        return 1;
    }

    vector<uint8_t> fileData(
        (istreambuf_iterator<char>(in)),
        istreambuf_iterator<char>());

    cout << "Loaded file size: "
         << fileData.size()
         << " bytes\n";

    // --------------------------------------------------------
    // Build IPP packet
    // --------------------------------------------------------

    vector<uint8_t> ipp;

    // IPP version 2.0
    ipp.push_back(0x02);
    ipp.push_back(0x00);

    // Operation: Print-Job
    ipp.push_back(0x00);
    ipp.push_back(0x02);

    // Request ID
    appendUint32(ipp, 1);

    // operation-attributes-tag
    ipp.push_back(0x01);

    string uri =
        "ipp://" +
        printerIP +
        ":631/ipp/print";

    addIPPString(
        ipp,
        0x47,
        "attributes-charset",
        "utf-8");

    addIPPString(
        ipp,
        0x48,
        "attributes-natural-language",
        "en");

    addIPPString(
        ipp,
        0x45,
        "printer-uri",
        uri);

    addIPPString(
        ipp,
        0x42,
        "requesting-user-name",
        "okmx");

    addIPPString(
        ipp,
        0x49,
        "document-format",
        mimeType(fmt));

    // end-of-attributes-tag
    ipp.push_back(0x03);

    // append document payload
    ipp.insert(
        ipp.end(),
        fileData.begin(),
        fileData.end());

    // --------------------------------------------------------
    // HTTP Header
    // --------------------------------------------------------

    string http =
        "POST /ipp/print HTTP/1.1\r\n"
        "Host: " + printerIP + "\r\n"
        "Content-Type: application/ipp\r\n"
        "Content-Length: " + to_string(ipp.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n";

    // --------------------------------------------------------
    // Create socket
    // --------------------------------------------------------

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("socket");
        return 1;
    }

    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(IPP_PORT);

    inet_pton(
        AF_INET,
        printerIP.c_str(),
        &addr.sin_addr);

    cout << "Connecting to printer...\n";

    if (connect(sock,
        (sockaddr*)&addr,
        sizeof(addr)) < 0)
    {
        perror("connect");

        close(sock);
        return 1;
    }

    cout << "Connected\n";

    // --------------------------------------------------------
    // Send HTTP
    // --------------------------------------------------------

    ssize_t sent =
        send(
            sock,
            http.c_str(),
            http.size(),
            0);

    if (sent <= 0)
    {
        perror("send http");

        close(sock);
        return 1;
    }

    // --------------------------------------------------------
    // Send IPP
    // --------------------------------------------------------

    sent =
        send(
            sock,
            ipp.data(),
            ipp.size(),
            0);

    if (sent <= 0)
    {
        perror("send ipp");

        close(sock);
        return 1;
    }

    cout << "IPP request sent\n";

    // --------------------------------------------------------
    // Receive response
    // --------------------------------------------------------

    char buf[8192];

    memset(buf, 0, sizeof(buf));

    int n =
        recv(
            sock,
            buf,
            sizeof(buf) - 1,
            0);

    close(sock);

    if (n <= 0)
    {
        cout << "No response from printer\n";
        return 1;
    }

    cout << "\n========== PRINTER RESPONSE ==========\n";

    cout.write(buf, n);

    cout << "\n======================================\n";

    // --------------------------------------------------------
    // Basic response check
    // --------------------------------------------------------

    string response(buf, n);

    if (response.find("200 OK") != string::npos)
    {
        cout << "\nIPP request accepted\n";
    }
    else
    {
        cout << "\nIPP request failed\n";
    }

    return 0;
}
