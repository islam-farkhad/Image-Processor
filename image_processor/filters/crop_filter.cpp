#include "crop_filter.h"
#include "../exceptions/filter_producing_exception.h"

Crop::Crop(size_t height, size_t width) : height_(height), width_(width) {
}

Image& Crop::Apply(Image& image) {
    if (height_ >= image.GetHeight() && width_ >= image.GetWidth()) {
        return image;
    }

    if (height_ >= image.GetHeight()) {
        height_ = image.GetHeight();
    }

    if (width_ >= image.GetWidth()) {
        width_ = image.GetWidth();
    }

    std::vector<std::vector<Image::Pixel>> pixels_matrix_cropped(height_, std::vector<Image::Pixel>(width_));

    for (int64_t i = 0; i < height_; ++i) {
        for (int64_t j = 0; j < width_; ++j) {
            pixels_matrix_cropped[i][j] = image[image.GetHeight() - height_ + i][j];
        }
    }

    image = Image(pixels_matrix_cropped);
    return image;
}

std::shared_ptr<Filter> ProduceCrop(const FilterDescriptor& descriptor) {
    if (descriptor.name != "crop") {
        throw FilterProducingException("crop", descriptor.name);
    }
    if (descriptor.params.size() < 2) {
        const size_t expected = 2;
        const size_t provided = descriptor.params.size();
        throw FilterProducingException(expected, provided);
    }
    try {
        size_t height = std::stoul(descriptor.params[0]);
        size_t width = std::stoul(descriptor.params[1]);
        return std::make_shared<Crop>(height, width);
    } catch (const std::invalid_argument& e) {
        throw FilterProducingException("Invalid argument for Crop, could not convert them to size_t");
    }
}
