#pragma once

#include "matrix_filter.h"

#include <memory>

class Sharpening : public MatrixFilter {
public:
    const Matrix& GetColorTransformationMatrix() override;

private:
    const Matrix sharpening_matrix_ = {std::array<int8_t, 3>{0, -1, 0}, std::array<int8_t, 3>{-1, 5, -1},
                                       std::array<int8_t, 3>{0, -1, 0}};
};

/** ProduceSharpening creates Sharpening object using smart shared pointer.  */
std::shared_ptr<Filter> ProduceSharpening(const FilterDescriptor& descriptor);