#include "filter_producing_exception.h"

FilterProducingException::FilterProducingException(const std::string& message)
    : ImageProcessorException("Filter producing factory exception. Message: " + message) {
}

FilterProducingException::FilterProducingException(const std::string& expected_filter_name,
                                                   const std::string& provided_filter_name)
    : FilterProducingException("Filter descriptor with unexpected filter name was given: expected \"" +
                               expected_filter_name + "\" got \"" + provided_filter_name + "\" instead") {
}

FilterProducingException::FilterProducingException(const size_t expected_filter_params_number,
                                                   const size_t provided_filter_param_number)
    : FilterProducingException("Incorrect number of blur filter parameters: expected " +
                               std::to_string(expected_filter_params_number) + " but " +
                               std::to_string(provided_filter_param_number) + " parameters were provided") {
}
