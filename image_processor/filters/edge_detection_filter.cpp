#include "edge_detection_filter.h"
#include "grayscale_filter.h"
#include "../exceptions/filter_producing_exception.h"

EdgeDetection::EdgeDetection(const double threshold) : threshold_(threshold) {
}

const MatrixFilter::Matrix& EdgeDetection::GetColorTransformationMatrix() {
    return edge_detection_matrix_;
}

Image& EdgeDetection::Apply(Image& image) {
    GrayScale gs;
    gs.Apply(image);

    ApplyMatrix(image);

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            // All r g b are same now, this why it is enough to check only one of them
            if (image[i][j].red > threshold_) {
                image[i][j] = 1;
            } else {
                image[i][j] = 0;
            }
        }
    }
    return image;
}

std::shared_ptr<Filter> ProduceEdgeDetection(const FilterDescriptor& descriptor) {
    if (descriptor.name != "edge") {
        throw FilterProducingException("edge", descriptor.name);
    }
    if (descriptor.params.empty()) {
        const size_t expected = 1;
        const size_t provided = 0;
        throw FilterProducingException(expected, provided);    }
    try {
        double threshold = std::stod(descriptor.params[0]);

        return std::make_shared<EdgeDetection>(threshold);
    } catch (const std::invalid_argument& e) {
        throw FilterProducingException("Invalid argument for Edge detection, could not convert it to double");
    }
}