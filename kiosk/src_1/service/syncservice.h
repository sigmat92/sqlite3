#pragma once

#include <QObject>
#include "network/restclient.h"
#include "model/vitalsmodel.h"

class SyncService : public QObject
{
    Q_OBJECT

public:
    explicit SyncService(QObject *parent = nullptr);

    void sendVitals(const QJsonObject &data);

private:
    RestClient m_client;

    QJsonObject toJson(const QString &data);
};