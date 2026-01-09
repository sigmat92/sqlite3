
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

/*
#pragma once
#include <QThread>
#include <QImage>

class V4L2Camera;

class CameraController : public QThread
{
    Q_OBJECT
public:
    explicit CameraController(const QString& device,
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
    V4L2Camera* m_camera = nullptr;
    bool m_running = true;
};



#pragma once
#include <QThread>
#include <QImage>
#include "../platform/v4l2/v4l2camera.h"

class CameraController : public QThread
{
    Q_OBJECT
public:
    explicit CameraController(QObject* parent = nullptr);
    void stop();

signals:
    void frameReady(const QImage& rgb);
    void grayFrameReady(const QImage& gray);

protected:
    void run() override;

private:
    bool m_running{true};
    V4L2Camera m_camera;
};
*/
