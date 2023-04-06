#include "parser_exception.h"

ParserException::ParserException(const std::string& message)
    : ImageProcessorException("Parser exception. Message: " + message) {
}
