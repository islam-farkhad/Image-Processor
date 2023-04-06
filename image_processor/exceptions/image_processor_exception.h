#pragma once

#include <stdexcept>
#include <string>

class ImageProcessorException : public std::exception {
public:
    explicit ImageProcessorException(const std::string& message);
    const char* what() const noexcept override;

protected:
    std::string message_;
};