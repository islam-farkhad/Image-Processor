#include "negative_filter.h"

#include "../exceptions/filter_producing_exception.h"

Image& Negative::Apply(Image& image) {

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (auto& pix : image[i]) {
            pix.red = 1 - pix.red;
            pix.green = 1 - pix.green;
            pix.blue = 1 - pix.blue;
        }
    }

    return image;
}

std::shared_ptr<Filter> ProduceNegative(const FilterDescriptor& descriptor) {
    if (descriptor.name != "neg") {
        throw FilterProducingException("neg", descriptor.name);
    }

    return std::make_shared<Negative>();
}
