#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <QImage>

class V4L2Camera
{
public:
    V4L2Camera(const std::string& device, int width, int height);
    ~V4L2Camera();

    bool open();
    void close();

    bool grab(QImage& rgb, QImage& gray);

private:
    struct Buffer {
        void*  start;
        size_t length;
    };

    bool initDevice();
    bool initMMap();
    bool startStreaming();
    bool stopStreaming();

    std::string m_device;
    int m_fd{-1};
    int m_width;
    int m_height;

    std::vector<Buffer> m_buffers;
};

