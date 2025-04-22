#include "error.h"

/**
 * @brief This file contains the implementation of the Error class which is used to handle error messages for the insulin pump.
 * @details The Error class contains a method to get error messages based on the error type.
 * @author Hollen Lo
 */

Error::Error()
{
    //order: LOW_INSULIN_BOLUS, LOW_INSULIN_BASAL,LOW_POWER, INSULIN_OUT, POWER_OUT,LOW_GLUCOSE, HIGH_GLUCOSE, NONE
    errorMessage.append("Not enough insulin for Bolus, please select an appropriate amount or refill the insulin");
    errorMessage.append("Insulin supply low, please refill");
    errorMessage.append("Power is running out, please recharge the battery");
    errorMessage.append("No more insulin, please refill");
    errorMessage.append("No more power, shutting down...");
    errorMessage.append("Low glucose, stopping delivery");
    errorMessage.append("High glucose, adjusting delivery");
    errorMessage.append("No error");
}
QString Error::getErrorMessage(ErrorType errorType)
{
    return errorMessage[static_cast<int>(errorType)];//returns respective error message
}   


