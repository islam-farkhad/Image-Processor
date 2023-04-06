#include "image_io_exception.h"

ImageIOException::ImageIOException(const std::string& message)
    : ImageProcessorException("Image reading exception. Message: " + message) {
}
