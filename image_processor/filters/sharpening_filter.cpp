#include "sharpening_filter.h"

#include "../exceptions/filter_producing_exception.h"

const MatrixFilter::Matrix& Sharpening::GetColorTransformationMatrix() {
    return sharpening_matrix_;
}

std::shared_ptr<Filter> ProduceSharpening(const FilterDescriptor& descriptor) {
    if (descriptor.name != "sharp") {
        throw FilterProducingException("sharp", descriptor.name);
    }

    return std::make_shared<Sharpening>();
}
