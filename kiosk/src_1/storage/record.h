#pragma once

#include <QString>

struct Record
{
    int sessionId;
    int patientId;
    QString date;
    QString time;
    QString name;
    QString gender;
    int mobile;
    int age;
    double temperature; 
    int spo2;
    int pulse;
    double weight;
    int height;
    int sys;
    int dia;
};