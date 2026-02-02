#pragma once
#include <QObject>
#include <QByteArray>

class ProtocolParser : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolParser(QObject *parent = nullptr);
    void feed(const QByteArray &data);

signals:
    void spo2(int);
    void pulseRate(int);
    void temperature(float);
    void nibp(int sys, int dia, int mean);
    void weight(float);
    void height(int);
    /*
    void spo2(int value);
    void pulseRate(int bpm);
    void temperature(float value);
    void nibp(int sys, int dia, int mean);
    void weight(float kg);
    void height(int cm);
    */
private:
    enum State { WAIT_CTRL, WAIT_LEN, WAIT_DATA } m_state;
    quint8 m_ctrl{};
    quint8 m_len{};
    QByteArray m_payload;
};

