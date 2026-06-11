#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>

class RestClient : public QObject
{
    Q_OBJECT

public:
    explicit RestClient(QObject *parent = nullptr);

    void login();
    void postVitals(const QJsonObject &json);

    QString token() const;

signals:
    void loginSuccess();
    void loginFailed(QString error);

    void postSuccess();
    void postFailed(QString error);

private slots:
    void handleLogin();
    void handlePost();

private:
    QNetworkAccessManager m_manager;
    QString m_token;

    QString m_baseUrl = "https://coddleonline.com";
};