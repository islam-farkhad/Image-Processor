#pragma once

#include "image_processor_exception.h"

class ParserException : public ImageProcessorException {
public:
    explicit ParserException(const std::string& message);
};