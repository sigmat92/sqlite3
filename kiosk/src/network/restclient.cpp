#include "restclient.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QNetworkReply>

RestClient::RestClient(QObject *parent)
    : QObject(parent)
{
}

QString RestClient::token() const
{
    return m_token;
}

// LOGIN
void RestClient::login()
{
    QUrl url(m_baseUrl + "/example/user/login");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setTransferTimeout(10000);

    QJsonObject json;
    json["username"] = "Tnhmis_VitalMachine";
    json["password"] = "1234567";

    auto reply = m_manager.post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, &RestClient::handleLogin);
}

void RestClient::handleLogin()
{
    auto reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        emit loginFailed(reply->errorString());
        reply->deleteLater();
        return;
    }

    auto doc = QJsonDocument::fromJson(reply->readAll());

    m_token = doc.object().value("token").toString();

    if (m_token.isEmpty())
        emit loginFailed("Token missing");
    else
        emit loginSuccess();

    reply->deleteLater();
}

// POST VITALS
void RestClient::postVitals(const QJsonObject &json)
{
    QUrl url(m_baseUrl + "/HISIntegrationMachine/api/v1/vital-details");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + m_token.toUtf8());
    request.setTransferTimeout(10000);

    auto reply = m_manager.post(request, QJsonDocument(json).toJson());

    connect(reply, &QNetworkReply::finished, this, &RestClient::handlePost);
}

void RestClient::handlePost()
{
    auto reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() != QNetworkReply::NoError) {
        emit postFailed(reply->errorString());
    } else {
        emit postSuccess();
    }

    reply->deleteLater();
}