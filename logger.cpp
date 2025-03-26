#include "logger.h"
#include <QVector>
#include <QObject>
Logger::Logger()
{

}
QVector<QString> Logger::getLogs(){
    return logs;
}
QVector<QString> Logger::getLastXLogs(int num){
    return logs;
}
void Logger::addLog(QString){

}
