#include "filter_producing_factory.h"
#include "exceptions/filter_producing_exception.h"

FilterProducingFactory::FilterProducingFactory(std::initializer_list<FilterNameProducer> init_list) {
    for (const auto& [filter_name, filter_producer] : init_list) {
        AddFilterProducer(filter_name, filter_producer);
    }
}

void FilterProducingFactory::AddFilterProducer(const std::string& filter_name, FilterProducer filter_producer) {
    filter_producing_manager_[filter_name] = filter_producer;
}

FilterProducingFactory::FilterProducer FilterProducingFactory::GetFilterProducer(const std::string& filter_name) const {
    if (filter_producing_manager_.contains(filter_name)) {
        return filter_producing_manager_.at(filter_name);
    }
    throw FilterProducingException("No filter producer for filter \"" + filter_name + "\" found");
}
