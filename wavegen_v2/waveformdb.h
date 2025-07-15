#ifndef WAVEFORMDB_H
#define WAVEFORMDB_H

#include <QVector>
#include <QString>
#include <QStringList>

class WaveformDB {
public:
    static WaveformDB& instance();
    void save(const QString& name, const QVector<double>& waveform);
    QVector<double> load(const QString& name);
    QStringList listWaveforms() const;

private:
    WaveformDB();
    void ensureTable();
    QString dbPath = "waveforms.db";
};

#endif // WAVEFORMDB_H