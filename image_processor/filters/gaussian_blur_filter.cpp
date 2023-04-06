#include "gaussian_blur_filter.h"

#include "../exceptions/filter_producing_exception.h"

#include <cmath>

GaussianBlur::GaussianBlur(double sigma) : sigma_(sigma) {
}

Image& GaussianBlur::Apply(Image& image) {
    // calculate coefficients
    std::vector<double> coefficients(GaussianMatrixSize(), 1.0 / (sigma_ * sqrt(2 * M_PI)));
    size_t middle = coefficients.size() / 2;

    for (size_t i = middle + 1; i < coefficients.size(); ++i) {
        coefficients[i] =
            exp(-pow(static_cast<double>(i - middle), 2) / (2 * pow(sigma_, 2))) / (sigma_ * sqrt(2 * M_PI));
        coefficients[2 * middle - i] = coefficients[i];  // coefficient on the same distant with i from middle;
    }

    // first approach (horizontal)
    for (size_t i = 0; i < image.GetHeight(); ++i) {

        std::vector<Image::Pixel> processed_pixel_raw;
        processed_pixel_raw.reserve(image.GetWidth());

        for (size_t j = 0; j < image.GetWidth(); ++j) {

            processed_pixel_raw.emplace_back(image[i][j] * coefficients[middle]);
            double applied_coefficients_sum = coefficients[middle];
            size_t r = 2 * middle;

            for (size_t l = 0; l < middle; ++l, --r) {

                if (j >= middle - l) {
                    processed_pixel_raw[j] += image[i][j - (middle - l)] * coefficients[l];
                    applied_coefficients_sum += coefficients[l];
                }

                if (j + (r - middle) < image.GetWidth()) {
                    processed_pixel_raw[j] += image[i][j + (r - middle)] * coefficients[r];
                    applied_coefficients_sum += coefficients[r];
                }
            }
            processed_pixel_raw[j] *= 1 / applied_coefficients_sum;
        }

        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image[i][j] = processed_pixel_raw[j];
        }
    }

    // second approach (vertical)
    for (size_t j = 0; j < image.GetWidth(); ++j) {

        std::vector<Image::Pixel> processed_pixel_col;
        processed_pixel_col.reserve(image.GetHeight());

        for (size_t i = 0; i < image.GetHeight(); ++i) {

            processed_pixel_col.emplace_back(image[i][j] * coefficients[middle]);
            double applied_coefficients_sum = coefficients[middle];
            size_t r = 2 * middle;

            for (size_t l = 0; l < middle; ++l, --r) {

                if (i >= middle - l) {
                    processed_pixel_col[i] += image[i - (middle - l)][j] * coefficients[l];
                    applied_coefficients_sum += coefficients[l];
                }

                if (i + (r - middle) < image.GetHeight()) {
                    processed_pixel_col[i] += image[i + (r - middle)][j] * coefficients[r];
                    applied_coefficients_sum += coefficients[r];
                }
            }
            processed_pixel_col[i] *= 1 / applied_coefficients_sum;
        }

        for (size_t i = 0; i < image.GetHeight(); ++i) {
            image[i][j] = processed_pixel_col[i];
        }
    }

    return image;
}

size_t GaussianBlur::GaussianMatrixSize() const {
    const double optimal_sigma_factor = 3;
    return static_cast<size_t>(std::ceil(optimal_sigma_factor * sigma_)) * 2 + 1;
}

std::shared_ptr<Filter> ProduceGaussianBlur(const FilterDescriptor& descriptor) {
    if (descriptor.name != "blur") {
        throw FilterProducingException("blur", descriptor.name);
    }
    if (descriptor.params.empty()) {
        const size_t expected = 1;
        const size_t provided = 0;
        throw FilterProducingException(expected, provided);
    }
    try {
        double sigma = std::stod(descriptor.params[0]);
        return std::make_shared<GaussianBlur>(sigma);
    } catch (const std::invalid_argument& e) {
        throw FilterProducingException("Invalid argument for Gaussian blur, could not convert it to double");
    }
}
