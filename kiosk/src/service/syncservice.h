#pragma once

#include <QObject>
#include "network/restclient.h"
#include "model/vitalsmodel.h"
#include "storage/vitalsrepository.h"

class SyncService : public QObject
{
    Q_OBJECT

public:

    //explicit SyncService(QObject *parent = nullptr);
    explicit SyncService(VitalsRepository *repo,QObject *parent = nullptr);

    void sendVitals(const QJsonObject &data);
    void postVitals(int sessionId);
    

private:
    RestClient m_client;
    VitalsRepository *m_repo;
    QJsonObject buildJson(const QVariantMap &data);

    QJsonObject m_pendingJson;
};