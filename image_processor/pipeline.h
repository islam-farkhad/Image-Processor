#pragma once

#include "filter_producing_factory.h"

class Pipeline {
public:
    Pipeline(const std::vector<FilterDescriptor>& descriptors, const FilterProducingFactory& factory);
    std::shared_ptr<Filter> Append(std::shared_ptr<Filter> filter);

    /** takes the image matrix by a non-constant link, because we will
     * change the image. So as not to copy it every time. If necessary, we can
     * copy (for example, if the filter application history becomes necessary)  */
    void ProcessImage(Image& image);

private:
    std::vector<std::shared_ptr<Filter>> filters_to_apply_;
};
