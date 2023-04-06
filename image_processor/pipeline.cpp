#include "pipeline.h"

#include "exceptions/filter_producing_exception.h"

#include <iostream>

Pipeline::Pipeline(const std::vector<FilterDescriptor>& descriptors, const FilterProducingFactory& factory) {
    /**If filter descriptor is not valid, we just skip it*/
    for (auto& descriptor : descriptors) {
        try {
            Append(factory.GetFilterProducer(descriptor.name)(descriptor));
        } catch (const FilterProducingException& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

std::shared_ptr<Filter> Pipeline::Append(std::shared_ptr<Filter> filter) {
    filters_to_apply_.push_back(filter);
    return filter;
}

void Pipeline::ProcessImage(Image& image) {
    for (auto& filter : filters_to_apply_) {
        filter->Apply(image);
    }
}
