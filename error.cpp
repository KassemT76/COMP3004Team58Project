#include "error.h"

Error::Error(int code, int subCode, const std::string& message, const std::string& subMessage)
    : errorCode(code), subErrorCode(subCode), errorMessage(message), subErrorMessage(subMessage)
{
    // TODO: Add error to logger
}

int Error::getErrorCode() const
{
    return errorCode;
}

int Error::getSubErrorCode() const
{
    return subErrorCode;
}

std::string Error::getErrorMessage() const
{
    return errorMessage;
}   

std::string Error::getSubErrorMessage() const
{
    return subErrorMessage;
}


