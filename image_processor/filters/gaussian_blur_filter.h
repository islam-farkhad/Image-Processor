#pragma once

#include "filter.h"
#include "filter_descriptor.h"

#include <memory>

class GaussianBlur : public Filter {
public:
    GaussianBlur(double sigma);

    Image& Apply(Image& image) override;

private:
    size_t GaussianMatrixSize() const;

private:
    double sigma_;
};

/** ProduceNegative creates GaussianBlur object using smart shared pointer.  */
std::shared_ptr<Filter> ProduceGaussianBlur(const FilterDescriptor& descriptor);
