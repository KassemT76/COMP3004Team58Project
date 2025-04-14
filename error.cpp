#include "error.h"

Error::Error()
{
    //order: LOW_INSULIN_BOLUS, LOW_INSULIN_BASAL,LOW_POWER, INSULIN_OUT, POWER_OUT,LOW_GLUCOSE, HIGH_GLUCOSE, NONE
    errorMessage.append("Not enough insulin for Bolus, please select an appropriate amount or refill the insulin");
    errorMessage.append("Insulin will run out in 30 minutes, please refill the insulin");
    errorMessage.append("Power will run out in 30 minutes, please recharge the battery");
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


