#pragma once

#include "filters/filter_descriptor.h"

#include <string>
#include <vector>

class Parser {
public:
    void ParseCmdLineArgs(int argc, char* argv[]);
    std::string GetInputFileName();
    std::string GetOutputFileName();
    const std::vector<FilterDescriptor>& GetFilterDescriptors();

private:
    std::string input_file_name_;
    std::string output_file_name_;
    std::vector<FilterDescriptor> filter_descriptors_;
};