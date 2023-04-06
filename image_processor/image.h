#pragma once

#include <vector>
#include <cstdint>

class Image {
public:
    struct Pixel {
        double red;
        double green;
        double blue;

        Pixel& operator=(double color);
        Pixel& operator+=(const Pixel& other);
        Pixel operator+(const Pixel& other);
        Pixel& operator*=(double factor);
        Pixel operator*(double factor);
        bool operator==(const Pixel& other) const;
    };

    struct PixelToReadAndWrite {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
    };

    Image() = default;
    explicit Image(std::vector<std::vector<Pixel>> pixels_matrix);

    std::vector<Pixel>& operator[](size_t i);
    const std::vector<Pixel>& operator[](size_t i) const;
    bool operator==(const Image&) const;

    [[nodiscard]] size_t GetHeight() const;
    [[nodiscard]] size_t GetWidth() const;

private:
    std::vector<std::vector<Pixel>> pixels_matrix_;
};
