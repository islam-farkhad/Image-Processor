#pragma once

#include "filter.h"
#include "filter_descriptor.h"

#include <memory>

class Negative : public Filter {
public:
    Image& Apply(Image& image) override;
};

/** ProduceNegative creates Negative object using smart shared pointer.  */
std::shared_ptr<Filter> ProduceNegative(const FilterDescriptor& descriptor);
