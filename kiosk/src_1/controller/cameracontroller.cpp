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

