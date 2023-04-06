#pragma once

#include "filter.h"
#include "filter_descriptor.h"

#include <array>

class MatrixFilter : public Filter {
public:
    using Matrix = std::array<std::array<int8_t, 3>, 3>;

    Image& Apply(Image& image) override;
    Image& ApplyMatrix(Image& image);

protected:
    virtual const Matrix& GetColorTransformationMatrix() = 0;
};