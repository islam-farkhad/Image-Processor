#include "bmp.h"

#include "exceptions/image_io_exception.h"

#include <limits>

void BMP::Read(const std::string& input_file_name) {
    std::fstream file(input_file_name, std::ios::binary | std::ios::in);
    if (!file) {
        throw ImageIOException("Could not open file. Provided path: " + input_file_name);
    }
    ReadBMPHeader(file);
    ReadDIBHeader(file);

    if (dib_header_.bits_per_pixel != 24) {
        throw ImageIOException("Only 24 bits per pixel format BMP supported. Input file is " +
                               std::to_string(dib_header_.bits_per_pixel) + " bits per pixel formatted");
    }

    std::vector<std::vector<Image::Pixel>> pixels_matrix(dib_header_.image_height,
                                                         std::vector<Image::Pixel>(dib_header_.image_width));
    for (size_t i = 0; i < dib_header_.image_height; ++i) {
        for (size_t j = 0; j < dib_header_.image_width; ++j) {
            Image::PixelToReadAndWrite pixel_to_read;
            file.read(reinterpret_cast<std::fstream::char_type*>(&pixel_to_read), sizeof(Image::PixelToReadAndWrite));
            pixels_matrix[i][j] = {
                .red = static_cast<double>(pixel_to_read.red) / std::numeric_limits<uint8_t>::max(),
                .green = static_cast<double>(pixel_to_read.green) / std::numeric_limits<uint8_t>::max(),
                .blue = static_cast<double>(pixel_to_read.blue) / std::numeric_limits<uint8_t>::max()};
        }

        uint32_t padding_qty = CountPadding();
        for (uint32_t j = 0; j < padding_qty; ++j) {
            file.get();
        }
    }
    image_ = Image(pixels_matrix);
}

void BMP::ReadBMPHeader(std::fstream& file) {
    file.read(reinterpret_cast<std::fstream::char_type*>(&bmp_header_), sizeof(BMPHeader));
}

void BMP::ReadDIBHeader(std::fstream& file) {
    file.read(reinterpret_cast<std::fstream::char_type*>(&dib_header_), sizeof(DIBHeader));
}

void BMP::Write(const std::string& output_file_name) {
    std::fstream file(output_file_name, std::ios::binary | std::ios::out);
    if (!file) {
        throw ImageIOException("Could not write to file. Provided path: " + output_file_name);
    }
    dib_header_.image_width = image_.GetWidth();
    dib_header_.image_height = image_.GetHeight();
    bmp_header_.file_size = SIZE_OF_HEADERS + CountRawSize() * dib_header_.image_height;

    file.write(reinterpret_cast<std::fstream::char_type*>(&bmp_header_), sizeof(BMPHeader));
    file.write(reinterpret_cast<std::fstream::char_type*>(&dib_header_), sizeof(DIBHeader));

    for (uint32_t i = 0; i < dib_header_.image_height; ++i) {
        for (uint32_t j = 0; j < dib_header_.image_width; ++j) {
            Image::Pixel pixel = image_[i][j];
            Image::PixelToReadAndWrite pixel_to_write = {
                .blue = static_cast<uint8_t>(pixel.blue * std::numeric_limits<uint8_t>::max()),
                .green = static_cast<uint8_t>(pixel.green * std::numeric_limits<uint8_t>::max()),
                .red = static_cast<uint8_t>(pixel.red * std::numeric_limits<uint8_t>::max())};

            file.write(reinterpret_cast<std::fstream::char_type*>(&pixel_to_write), sizeof(Image::PixelToReadAndWrite));
        }

        uint32_t padding_qty = CountPadding();
        for (uint32_t j = 0; j < padding_qty; ++j) {
            file.put(0);
        }
    }
}

void BMP::Remove(const std::string& file_name) {
    if (remove(file_name.data())) {
        throw ImageIOException("Could not remove file. Provided path: " + file_name);
    }
}

Image& BMP::GetImage() {
    return image_;
}

uint32_t BMP::CountRawSize() const {
    return ((3 * dib_header_.image_width - 1) / 4 + 1) * 4;
}

uint32_t BMP::CountPadding() const {
    return CountRawSize() - 3 * dib_header_.image_width;
}

const BMP::BMPHeader& BMP::GetBMPHeader() {
    return bmp_header_;
}

const BMP::DIBHeader& BMP::GetDIBHeader() {
    return dib_header_;
}
