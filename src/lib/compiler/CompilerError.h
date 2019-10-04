//
// Created by rvigee on 10/4/19.
//

#ifndef RISOTTOV2_COMPILERERROR_H
#define RISOTTOV2_COMPILERERROR_H

#include <exception>
#include <string>

class CompilerError: public std::exception {
public:
    std::string message;

    CompilerError(const std::string& message);

    [[nodiscard]] const char *what() const noexcept override;
};


#endif //RISOTTOV2_COMPILERERROR_H