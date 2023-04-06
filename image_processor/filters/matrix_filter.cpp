#include "matrix_filter.h"

Image& MatrixFilter::Apply(Image& image) {
    return ApplyMatrix(image);
}

Image& MatrixFilter::ApplyMatrix(Image& image) {
    Image image_copy = image;

    Matrix color_transform_matrix = GetColorTransformationMatrix();

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {

            Image::Pixel new_pixel = {.red = 0, .green = 0, .blue = 0};

            for (size_t ii = 0; ii < color_transform_matrix.size(); ++ii) {
                for (size_t jj = 0; jj < color_transform_matrix[0].size(); ++jj) {

                    if (color_transform_matrix[ii][jj]) {
                        size_t temp_i = i;
                        size_t temp_j = j;
                        if (temp_i + ii > 0 && temp_i + ii <= image.GetHeight()) {
                            temp_i += ii - 1;
                        }
                        if (temp_j + jj > 0 && temp_j + jj <= image.GetWidth()) {
                            temp_j += jj - 1;
                        }
                        new_pixel += image[temp_i][temp_j] * color_transform_matrix[ii][jj];
                    }
                }
            }
            image_copy[i][j].red = std::min(1.0, std::max(0.0, new_pixel.red));
            image_copy[i][j].green = std::min(1.0, std::max(0.0, new_pixel.green));
            image_copy[i][j].blue = std::min(1.0, std::max(0.0, new_pixel.blue));
        }
    }
    image = image_copy;
    return image;
}
