#include "cover_filter.h"
#include "../exceptions/filter_producing_exception.h"

#include <cmath>

Cover::Cover(const std::string& image_path, const double alpha, const bool cover_all, const size_t start_point_x,
             const size_t start_point_y)
    : alpha_(alpha), cover_all_(cover_all), start_point_x_(start_point_x), start_point_y_(start_point_y) {
    bmp_to_cover_.Read(image_path);
}

Image& Cover::Apply(Image& image) {
    Image& covering_image = bmp_to_cover_.GetImage();

    size_t i_stop = image.GetHeight();
    size_t j_stop = image.GetWidth();
    if (!cover_all_) {
        i_stop = std::min(covering_image.GetHeight(), i_stop);
        j_stop = std::min(covering_image.GetWidth(), j_stop);
    }

    for (size_t i = 0; i < i_stop; ++i) {
        for (size_t j = 0; j < j_stop; ++j) {

            if (i + start_point_y_ >= image.GetHeight() || j + start_point_x_ >= image.GetWidth()) {
                continue;
            }
            image[i + start_point_y_][j + start_point_x_].red =
                (1 - alpha_) * image[i + start_point_y_][j + start_point_x_].red +
                alpha_ * covering_image[i % covering_image.GetHeight()][j % covering_image.GetWidth()].red;
            image[i + start_point_y_][j + start_point_x_].green =
                (1 - alpha_) * image[i + start_point_y_][j + start_point_x_].green +
                alpha_ * covering_image[i % covering_image.GetHeight()][j % covering_image.GetWidth()].green;
            image[i + start_point_y_][j + start_point_x_].blue =
                (1 - alpha_) * image[i + start_point_y_][j + start_point_x_].blue +
                alpha_ * covering_image[i % covering_image.GetHeight()][j % covering_image.GetWidth()].blue;
        }
    }
    return image;
}

std::shared_ptr<Filter> ProduceCover(const FilterDescriptor& descriptor) {
    if (descriptor.name != "cover") {
        throw FilterProducingException("cover", descriptor.name);
    }
    if (descriptor.params.empty()) {
        throw FilterProducingException("0 arguments for cover were given. At least alpha must be provided");
    }
    try {
        const double default_alpha = 0.5;

        auto it = descriptor.params.begin();
        const std::string path = (*it);
        ++it;

        double alpha = default_alpha;
        bool cover_all = false;
        size_t rotation_point_x = 0;
        size_t rotation_point_y = 0;

        if (it != descriptor.params.end()) {
            alpha = std::stod(*it);
            ++it;
        }
        if (it != descriptor.params.end()) {
            cover_all = std::stoul(*it);
            ++it;
        }
        if (it != descriptor.params.end()) {
            rotation_point_x = std::stoul(*it);
            ++it;
        }
        if (it != descriptor.params.end()) {
            rotation_point_y = std::stoul(*it);
        }

        return std::make_shared<Cover>(path, alpha, cover_all, rotation_point_x, rotation_point_y);

    } catch (const std::invalid_argument& e) {
        throw FilterProducingException("Invalid argument(-s) for Cover, could not convert to needed types");
    }
}
