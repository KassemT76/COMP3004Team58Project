#ifndef ERROR_H
#define ERROR_H

/**
 * @file error.h
 * @brief This file contains the Error class which is used to handle error messages for the insulin pump.
 * @details The Error class contains a method to get error messages based on the error type.
 * @author Ariz Kazani and Hollen Lo
 */

#include <QVector>

/**
 * @brief The ErrorType enum defines the different types of errors that can occur in the insulin pump.
 */
enum class ErrorType {LOW_INSULIN_BOLUS, LOW_INSULIN,LOW_POWER, INSULIN_OUT, POWER_OUT,LOW_GLUCOSE, HIGH_GLUCOSE, NONE};
//LOW_INSULIN_BOLUS is for the immediate does being over the insulin level, LOW_INSULIN applies to continuous bolus running out
class Error
{
public:
    Error();
    /**
     * @brief getErrorMessage returns the error message based on the error type.
     * @param errorType The type of error.
     * @return The error message as a QString.
     */
    QString getErrorMessage(ErrorType);

private:
    // The order of the messages in the vector corresponds to the order of the ErrorType enum
    QVector<QString> errorMessage;
};

#endif // ERROR_H
