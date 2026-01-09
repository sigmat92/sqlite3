#include "cameracontroller.h"
#include "platform/v4l2/v4l2camera.h"

CameraController::CameraController(const QString& device,
                                   int width,
                                   int height,
                                   QObject* parent)
    : QThread(parent),
      m_device(device),
      m_width(width),
      m_height(height)
{
}

CameraController::~CameraController()
{
    stop();
    wait();
}

void CameraController::stop()
{
    m_running = false;
}

void CameraController::run()
{
    m_camera = new V4L2Camera(
        m_device.toStdString(),
        m_width,
        m_height
    );

    if (!m_camera->open())
        return;

    while (m_running) {
        QImage color, gray;

        if (m_camera->grab(color, gray)) {
            emit frameColorReady(color);
            emit frameGrayReady(gray);
        }
    }

    m_camera->close();
    delete m_camera;
    m_camera = nullptr;
}


/*
#include "cameracontroller.h"
#include "platform/v4l2/v4l2camera.h"

CameraController::CameraController(const QString& device, QObject* parent)
    : QThread(parent), m_device(device)
{
}

CameraController::~CameraController()
{
    stop();
    wait();
}

void CameraController::stop()
{
    m_running = false;
}

void CameraController::run()
{
    m_camera = new V4L2Camera(m_device.toStdString());
    if (!m_camera->open())
        return;

    while (m_running) {
        QImage color, gray;
        if (m_camera->grabFrame(color, gray)) {
            emit frameColorReady(color);
            emit frameGrayReady(gray);
        }
    }

    m_camera->close();
    delete m_camera;
    m_camera = nullptr;
}



#include "cameracontroller.h"

CameraController::CameraController(QObject* parent)
    : QThread(parent),
      m_camera("/dev/video0", 640, 480)
{
}

void CameraController::run()
{
    if (!m_camera.open())
        return;

    QImage rgb, gray;

    while (m_running) {
        if (m_camera.grab(rgb, gray)) {
            emit frameReady(rgb);
            emit grayFrameReady(gray);
        }
    }

    m_camera.close();
}

void CameraController::stop()
{
    m_running = false;
    wait();
}
*/
