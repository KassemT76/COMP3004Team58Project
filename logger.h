#ifndef LOGGER_H
#define LOGGER_H

#include <QVector>

class Logger
{
public:
    Logger();
    QVector<QString> getLogs();
    QVector<QString> getLastXLogs(int);
    void addLog(QString);
private:
    QVector<QString> logs;

};

#endif // LOGGER_H
