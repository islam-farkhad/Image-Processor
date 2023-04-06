#pragma once

#include "../image.h"

class Filter {
public:
    virtual Image& Apply(Image& image) = 0;

    virtual ~Filter() = default;
};