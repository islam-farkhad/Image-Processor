#pragma once

#include "filter.h"
#include "filter_descriptor.h"
#include "../bmp.h"

#include <memory>

class Cover : public Filter {
public:

    /** alpha is how opaque the overlay image will be, start_point_x and start_point_y
     * is starting from which point the image will be superimposed and cover_all is
     * responsible for whether the entire image will be covered */
    explicit Cover(const std::string& image_path, const double alpha = 0.5, const bool cover_all = false,
                   const size_t start_point_x = 0, const size_t start_point_y = 0);
    Image& Apply(Image& image) override;

private:
    const double alpha_;
    const bool cover_all_;
    const size_t start_point_x_;
    const size_t start_point_y_;
    BMP bmp_to_cover_;
};

/** ProduceCover creates Cover object using smart shared pointer.   */
std::shared_ptr<Filter> ProduceCover(const FilterDescriptor& descriptor);
