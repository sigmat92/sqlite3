confirms the entire pipeline is now correct.

proven:

custom IPP client on i.MX93 works
TCP/HTTP framing works
IPP binary encoding works
document-format=image/pwg-raster works
HP AirPrint printer accepts the PWG file
The generated PWG raster is valid

So the issue was never:

socket code
IPP request format
printer compatibility
embedded Linux networking

The root cause was:

malformed PWG raster generated previously by Ghostscript/manual writer

Now we have a fully working architecture:

PDF
  ↓
PGM (pdftoppm)
  ↓
Custom PWG writer (CUPS raster API)
  ↓
working.pwg
  ↓
Custom IPP client
  ↓
HP AirPrint printer

final validated stack is:

Ubuntu 18.04 Generator Side

Generate grayscale raster:

pdftoppm -gray -r 300 sample.pdf page

Generate PWG:

./pwg_writer page-1.pgm working.pwg

Embedded i.MX93 Side

Send to printer:

./ipp_print_2 working.pwg 192.168.45.167

And printer accepts successfully.

log ref:

prakash@prakash-HP-ProBook-640-G2:~/networkPrinterTest$ pdftoppm -gray -r 300 test.pdf page
prakash@prakash-HP-ProBook-640-G2:~/networkPrinterTest$ ls
bkp                      network_printing_okmx93  sample.pdf
clean_600.pwg            out.jpg                  test.jpg
clean.pclm               out.pcl                  test.pcl
clean.pwg                out.pclm                 test.pdf
create_voild_file        out.pwg                  test.pwg
create_voild_file.cpp    page-1.pgm               test.txt
ipp_print_1.cpp          pclm-print.test          valid_gray.pwg
ipp_print_2              print.docx               valid.pwg
ipp_print_2.cpp          pwg_writer               valid_sgray8.pwg
ipp_print_monitor_2.cpp  pwg_writer_1             working_nwprinter_test_ubuntu1804
manual_sgray8.pwg        pwg_writer_1.cpp         working.pwg
metsl.png                pwg_writer.cpp
prakash@prakash-HP-ProBook-640-G2:~/networkPrinterTest$ ./pwg_writer_1 page-1.pgm working.pwg
Input image: 2480x3509
PWG raster created successfully
prakash@prakash-HP-ProBook-640-G2:~/networkPrinterTest$ ./ipp_print_2 working.pwg 192.168.45.167
Detected format: image/pwg-raster
Loaded file size: 17573 bytes
Connecting to printer...
Connected
IPP request sent

========== PRINTER RESPONSE ==========
HTTP/1.1 200 OK
Content-Type: application/ipp
Content-Length: 201

Gattributes-charsetutf-8Httributes-natural-languageenEjob-uri#ipp://192.168.45.167/ipp/print/0114!job-idr#	job-stateDjob-state-reasonsnoneAjob-state-message
======================================

IPP request accepted
prakash@prakash-HP-ProBook-640-G2:~/networkPrinterTest$

printing works
