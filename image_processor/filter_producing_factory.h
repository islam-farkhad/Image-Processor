#pragma once

#include "filters/crop_filter.h"
#include "filters/negative_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/cover_filter.h"
#include "filters/gaussian_blur_filter.h"

#include <map>
#include <functional>

class FilterProducingFactory {
public:
    using FilterProducer = std::function<std::shared_ptr<Filter>(const FilterDescriptor&)>;

    struct FilterNameProducer {
        std::string filter_name;
        FilterProducer filter_producer;
    };

    FilterProducingFactory(std::initializer_list<FilterNameProducer> init_list);
    void AddFilterProducer(const std::string& filter_name, FilterProducer filter_producer);
    FilterProducer GetFilterProducer(const std::string& filter_name) const;

private:
    std::map<std::string, FilterProducer> filter_producing_manager_;
};
