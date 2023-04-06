#pragma once

#include "image_processor_exception.h"

class FilterProducingException : public ImageProcessorException {
public:
    explicit FilterProducingException(const std::string& message);
    FilterProducingException(const std::string& expected_filter_name, const std::string& provided_filter_name);
    FilterProducingException(const size_t expected_filter_params_number, const size_t provided_filter_param_number);
};