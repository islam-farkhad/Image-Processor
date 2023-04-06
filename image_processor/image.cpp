#include "image.h"

#include <utility>

Image::Pixel& Image::Pixel::operator=(double color) {
    red = green = blue = color;
    return *this;
}

Image::Pixel& Image::Pixel::operator+=(const Image::Pixel& other) {
    red += other.red;
    green += other.green;
    blue += other.blue;
    return *this;
}

Image::Pixel Image::Pixel::operator+(const Image::Pixel& other) {
    Pixel sum = *this;
    sum += other;
    return sum;
}

Image::Pixel& Image::Pixel::operator*=(const double factor) {
    red *= factor;
    green *= factor;
    blue *= factor;
    return *this;
}

Image::Pixel Image::Pixel::operator*(const double factor) {
    Pixel product = *this;
    product *= factor;
    return product;
}

bool Image::Pixel::operator==(const Image::Pixel& other) const {
    const double epsilon = 0.005; // assume that this is not significant difference
    return std::abs(red - other.red) < epsilon &&
           std::abs(green - other.green) < epsilon &&
           std::abs(blue - other.blue) < epsilon;
}

Image::Image(std::vector<std::vector<Pixel>> pixels_matrix) : pixels_matrix_(std::move(pixels_matrix)) {
}

std::vector<Image::Pixel>& Image::operator[](size_t i) {
    return pixels_matrix_[i];
}

const std::vector<Image::Pixel>& Image::operator[](size_t i) const {
    return pixels_matrix_[i];
}

size_t Image::GetHeight() const {
    return pixels_matrix_.size();
}

size_t Image::GetWidth() const {
    return pixels_matrix_[0].size();
}

bool Image::operator==(const Image& other) const {

    if (GetWidth() != other.GetWidth() || GetHeight() != other.GetHeight()) {
        return false;
    }
    for (size_t i = 0; i < GetHeight(); ++i) {
        for (size_t j = 0; j < GetWidth(); ++j) {
            if (!(this->operator[](i)[j] == other[i][j])) {
                return false;
            }
        }
    }
    return true;
}
