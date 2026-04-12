#include "syncservice.h"
#include <QJsonObject>

SyncService::SyncService(QObject *parent)
    : QObject(parent)
{
    connect(&m_client, &RestClient::loginSuccess, this, [this]() {
        // Retry post after login
    });
}

void SyncService::sendVitals(const QJsonObject &data)
{
    if (m_client.token().isEmpty()) {
        m_client.login();
        return;
    }

    //client.postVitals(toJson(data));
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