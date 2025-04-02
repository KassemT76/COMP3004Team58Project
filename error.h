#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <logger.h>

class Error
{
public:
    Error(int code = 0, int subCode = 0, const std::string& message = "", const std::string& subMessage = "");

    int getErrorCode() const;
    int getSubErrorCode() const;
    std::string getErrorMessage() const;
    std::string getSubErrorMessage() const;


private:
    int errorCode; // main error code
    int subErrorCode; // sub error code

    std::string errorMessage; // error message
    std::string subErrorMessage; // sub error message
};

#endif // ERROR_H
