#ifndef ERROR_H
#define ERROR_H

#include <QVector>

enum class ErrorType {LOW_INSULIN_BOLUS, LOW_INSULIN,LOW_POWER, INSULIN_OUT, POWER_OUT,LOW_GLUCOSE, HIGH_GLUCOSE, NONE};
//LOW_INSULIN_BOLUS is for the immediate does being over the insulin level, LOW_INSULIN applies to continuous bolus running out
class Error
{
public:
    Error();
    QString getErrorMessage(ErrorType);


private:
    QVector<QString> errorMessage;
};

#endif // ERROR_H
