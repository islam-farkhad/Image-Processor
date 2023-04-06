#pragma once

#include "filter.h"
#include "filter_descriptor.h"

#include <memory>

class Crop : public Filter {
public:
    Crop(size_t height, size_t width);
    Image& Apply(Image& image) override;

private:
    uint32_t height_;
    uint32_t width_;
};

/** ProduceCrop creates Crop object using smart shared pointer.  */
std::shared_ptr<Filter> ProduceCrop(const FilterDescriptor& descriptor);
