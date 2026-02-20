
#pragma once
#include <QThread>
#include <QImage>
#include <QString>

class V4L2Camera;

class CameraController : public QThread
{
    Q_OBJECT
public:
    explicit CameraController(const QString& device,
                              int width = 640,
                              int height = 480,
                              QObject* parent = nullptr);
    ~CameraController();

    void stop();

signals:
    void frameColorReady(const QImage& img);
    void frameGrayReady(const QImage& img);

protected:
    void run() override;

private:
    QString m_device;
    int m_width;
    int m_height;

    V4L2Camera* m_camera = nullptr;
    bool m_running = true;
};

