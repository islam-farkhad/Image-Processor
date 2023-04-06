#pragma once

#include "filter.h"
#include "filter_descriptor.h"

#include <memory>

class GrayScale : public Filter {
public:
    Image& Apply(Image& image) override;
};

/** ProduceGrayScale creates GrayScale object using smart shared pointer.  */
std::shared_ptr<Filter> ProduceGrayScale(const FilterDescriptor& descriptor);
