#pragma once

#include "image_processor_exception.h"

class ImageIOException : public ImageProcessorException {
public:
    explicit ImageIOException(const std::string& message);
};