#include "image_processor_exception.h"

ImageProcessorException::ImageProcessorException(const std::string& message) : message_(message) {
}

const char* ImageProcessorException::what() const noexcept {
    return message_.data();
}
