#include "v4l2camera.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <cstring>
#include <cstdio>

static inline uint8_t clamp(int v)
{
    return v < 0 ? 0 : (v > 255 ? 255 : v);
}

V4L2Camera::V4L2Camera(const std::string& dev, int w, int h)
    : m_device(dev), m_width(w), m_height(h)
{
}

V4L2Camera::~V4L2Camera()
{
    close();
}

bool V4L2Camera::open()
{
    m_fd = ::open(m_device.c_str(), O_RDWR);
    if (m_fd < 0) {
        perror("V4L2 open");
        return false;
    }

    return initDevice() && initMMap() && startStreaming();
}

void V4L2Camera::close()
{
    stopStreaming();

    for (auto& b : m_buffers)
        munmap(b.start, b.length);

    m_buffers.clear();

    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }
}

bool V4L2Camera::initDevice()
{
    v4l2_format fmt{};
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = m_width;
    fmt.fmt.pix.height = m_height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;

    if (ioctl(m_fd, VIDIOC_S_FMT, &fmt) < 0) {
        perror("VIDIOC_S_FMT");
        return false;
    }

    return true;
}

bool V4L2Camera::initMMap()
{
    v4l2_requestbuffers req{};
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (ioctl(m_fd, VIDIOC_REQBUFS, &req) < 0) {
        perror("VIDIOC_REQBUFS");
        return false;
    }

    m_buffers.resize(req.count);

    for (uint32_t i = 0; i < req.count; ++i) {
        v4l2_buffer buf{};
        buf.type = req.type;
        buf.memory = req.memory;
        buf.index = i;

        if (ioctl(m_fd, VIDIOC_QUERYBUF, &buf) < 0) {
            perror("VIDIOC_QUERYBUF");
            return false;
        }

        m_buffers[i].length = buf.length;
        m_buffers[i].start = mmap(nullptr, buf.length,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED, m_fd, buf.m.offset);

        ioctl(m_fd, VIDIOC_QBUF, &buf);
    }

    return true;
}

bool V4L2Camera::startStreaming()
{
    v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    return ioctl(m_fd, VIDIOC_STREAMON, &type) == 0;
}

bool V4L2Camera::stopStreaming()
{
    if (m_fd < 0)
        return true;

    v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl(m_fd, VIDIOC_STREAMOFF, &type);
    return true;
}

bool V4L2Camera::grab(QImage& rgb, QImage& gray)
{
    v4l2_buffer buf{};
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (ioctl(m_fd, VIDIOC_DQBUF, &buf) < 0)
        return false;

    uint8_t* yuyv = static_cast<uint8_t*>(m_buffers[buf.index].start);

    rgb = QImage(m_width, m_height, QImage::Format_RGB888);
    gray = QImage(m_width, m_height, QImage::Format_Grayscale8);

    uint8_t* rgbp = rgb.bits();
    uint8_t* grayp = gray.bits();

    for (int i = 0; i < m_width * m_height * 2; i += 4) {
        int y0 = yuyv[i + 0];
        int u  = yuyv[i + 1] - 128;
        int y1 = yuyv[i + 2];
        int v  = yuyv[i + 3] - 128;

        int r0 = y0 + 1.402 * v;
        int g0 = y0 - 0.344 * u - 0.714 * v;
        int b0 = y0 + 1.772 * u;

        int r1 = y1 + 1.402 * v;
        int g1 = y1 - 0.344 * u - 0.714 * v;
        int b1 = y1 + 1.772 * u;

        *rgbp++ = clamp(r0);
        *rgbp++ = clamp(g0);
        *rgbp++ = clamp(b0);

        *rgbp++ = clamp(r1);
        *rgbp++ = clamp(g1);
        *rgbp++ = clamp(b1);

        *grayp++ = y0;
        *grayp++ = y1;
    }

    ioctl(m_fd, VIDIOC_QBUF, &buf);
    return true;
}

