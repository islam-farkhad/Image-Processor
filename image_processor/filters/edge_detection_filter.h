#pragma once

#include "matrix_filter.h"

#include <memory>

class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(const double threshold);

    const Matrix& GetColorTransformationMatrix() override;
    Image& Apply(Image& image) override;

private:
    const Matrix edge_detection_matrix_ = {std::array<int8_t, 3>{0, -1, 0}, std::array<int8_t, 3>{-1, 4, -1},
                                           std::array<int8_t, 3>{0, -1, 0}};
    const double threshold_;
};

/** ProduceEdgeDetection creates EdgeDetection object using smart shared pointer.  */
std::shared_ptr<Filter> ProduceEdgeDetection(const FilterDescriptor& descriptor);