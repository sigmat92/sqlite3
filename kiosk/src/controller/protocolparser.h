#pragma once
#include <QObject>
#include <QByteArray>

class ProtocolParser : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolParser(QObject* parent = nullptr);

public slots:
    void feed(const QByteArray& data);

signals:
    //void temperature(double tempF);
    void temperature(double value, char unit);


private:
    QByteArray buffer;
    void parseFrames();
};

