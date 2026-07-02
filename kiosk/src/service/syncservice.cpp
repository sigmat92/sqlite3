#include "syncservice.h"
#include "service/healthmetricsservice.h"
#include <QJsonObject>
#include <QDebug>

SyncService::SyncService(
        VitalsRepository *repo,
        QObject *parent)
    : QObject(parent),
      m_repo(repo)
//SyncService::SyncService(QObject *parent)
//    : QObject(parent)
{
    connect(&m_client,
            &RestClient::loginSuccess,
            this,
            [this]()
    {
        if (!m_pendingJson.isEmpty())
            m_client.postVitals(m_pendingJson);
    });

    connect(&m_client,
            &RestClient::postSuccess,
            this,
            []()
    {
        qDebug() << "[SYNC] Upload successful";
    });

    connect(&m_client,
            &RestClient::postFailed,
            this,
            [](const QString &err)
    {
        qDebug() << "[SYNC] Upload failed:" << err;
    });
}
//SyncService::SyncService(QObject *parent)
//    : QObject(parent)
//{
//    connect(&m_client, &RestClient::loginSuccess, this, [this]() {
        // Retry post after login
//    });
//}
void SyncService::sendVitals(const QJsonObject &json)
{
    m_pendingJson = json;

    if (m_client.token().isEmpty())
    {
        m_client.login();
        return;
    }

    m_client.postVitals(m_pendingJson);
}

void SyncService::postVitals(int sessionId)
{
    QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    qDebug() << "SyncService::postVitals called for sessionId:" << sessionId;
    qDebug() << "Retrieved data:" << data;

    if (data.isEmpty())
    {
        qDebug() << "No vitals found";
        return;
    }
 
    QJsonObject json = buildJson(data);

    sendVitals(json);
}
//void SyncService::sendVitals(const QJsonObject &data)
//{
//    if (m_client.token().isEmpty()) {
//        m_client.login();
//        return;
//    }

//client.postVitals(toJson(data));
//}
QJsonObject SyncService::buildJson(const QVariantMap &data)
{
    QJsonObject json;
    //
       double weight = data["weight"].toDouble();
    int height    = data["height"].toInt();

    int age        = data["age"].toInt();
    QString gender = data["gender"].toString();

    int sys = data["systolic"].toInt();
    int dia = data["diastolic"].toInt();

    double bmi =
    HealthMetricsService::calculateBMI(
        weight,
        height);

    double bmr =
        HealthMetricsService::calculateBMR(
            weight,
            height,
            age,
            gender);

    double bsa =
        HealthMetricsService::calculateBSA(
            weight,
            height);

    int map =
        (sys + 2 * dia) / 3;
    //

    json["mId"]            = QString::number(data["sessionId"].toInt());
    json["pId"]            = QString::number(data["patientId"].toInt());

    json["entry_date"]     = QDate::currentDate().toString("dd/MM/yyyy");

    json["hospital_code"]  = "123456";
    json["hmis_code"]      = "12345689";

    json["mobile_no"]      = data["mobile"].toString();
    json["name"]           = data["name"].toString();
    json["age"]            = QString::number(data["age"].toInt());
    json["sex"]            = data["gender"].toString();

    json["height"]         = QString::number(data["height"].toInt());
    json["weight"]         = QString::number(data["weight"].toDouble());

    //json["bmi"]            = QString::number(d["bmi"].toDouble(),'f',1);
    //json["bmr"]            = QString::number(d["bmr"].toDouble(),'f',1);
    //json["bsa"]            = QString::number(d["bsa"].toDouble(),'f',2);
    json["bmi"]            = QString::number(bmi,'f',1);
    json["bmr"]            = QString::number(bmr,'f',1);
    json["bsa"]            = QString::number(bsa,'f',2);

    json["temp"]           = QString::number(data["temperature"].toDouble(),'f',1);

    json["systolic_bp"]    = QString::number(data["systolic"].toInt());
    json["diastolic_bp"]   = QString::number(data["diastolic"].toInt());
    //json["map"]            = QString::number(data["map"].toInt());
    json["map"]            = QString::number(map);

    json["spo2"]           = QString::number(data["spo2"].toInt());
    json["pr"]             = QString::number(data["pulse"].toInt());

    json["gnum_isvalid"]   = "yes";
    json["seatId"]         = "123";

    return json;
}
//JonObject SyncService::toJson(const QString &data)
//
// JsonObject json;
/*
    json["mId"] = "0004";
    json["pId"] = data["pId"].toString();
    json["entry_date"] = data["entry_date"].toVariant().toDateTime();

    json["height"] = data["height"].toDouble();
    json["weight"] = data["weight"].toDouble();
    json["temp"] = data["temp"].toDouble();

    json["spo2"] = data["spo2"].toInt();
    json["pr"] = data["pr"].toInt();

    json["systolic_bp"] = data["systolic_bp"].toInt();
    json["diastolic_bp"] = data["diastolic_bp"].toInt();


QJsonObject json =
{
        "mId": "0004",
        "pId": "4321",
        "entry_date": "27/02/2026",
	"hospital_code":"123456",
	"hmis_code":"12345689",
        "mobile_no": "9820856498",
        "name": "Prakash D",
        "age": "56",
        "sex": "Male",
        "height": "175",
        "weight": "75",
        "bmi": "24.5",
        "bmr": "1500",
        "bsa": "1.9",
        "temp": "98.6",
        "systolic_bp": "120",
        "diastolic_bp": "80",
        "map": "93",
        "spo2": "98",
        "pr": "72",
	"gnum_isvalid":"yes",
	"seatId":"123"
      }
    */
//  return json;
//