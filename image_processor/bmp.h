#pragma once

#include "image.h"

#include <cstdint>
#include <fstream>

class BMP {
public:
    static const uint32_t SIZE_OF_HEADERS = 54;

    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset_to_pixel_array;
    } __attribute__((packed));

    struct DIBHeader {
        uint32_t dib_header_size;
        uint32_t image_width;
        uint32_t image_height;
        uint16_t planes;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        uint32_t ppm_horizontal;
        uint32_t ppm_vertical;
        uint32_t palette_colors_num;
        uint32_t important_color_num;
    } __attribute__((packed));

    void Read(const std::string& input_file_name);
    void ReadBMPHeader(std::fstream& file);
    void ReadDIBHeader(std::fstream& file);

    void Write(const std::string& output_file_name);
    void Remove(const std::string& file_name);

    Image& GetImage();
    const BMPHeader& GetBMPHeader();
    const DIBHeader& GetDIBHeader();

private:
    uint32_t CountRawSize() const;
    uint32_t CountPadding() const;

private:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    Image image_;
};