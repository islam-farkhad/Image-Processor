#include "grayscale_filter.h"

#include "../exceptions/filter_producing_exception.h"

Image& GrayScale::Apply(Image& image) {
    const double red_coefficient = 0.299;
    const double green_coefficient = 0.587;
    const double blue_coefficient = 0.114;

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (auto& pix : image[i]) {
            pix = (red_coefficient * pix.red + green_coefficient * pix.green + blue_coefficient * pix.blue);
        }
    }

    return image;
}

std::shared_ptr<Filter> ProduceGrayScale(const FilterDescriptor& descriptor) {
    if (descriptor.name != "gs") {
        throw FilterProducingException("gs", descriptor.name);
    }

    return std::make_shared<GrayScale>();
}
