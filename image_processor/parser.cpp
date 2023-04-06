#include "parser.h"

#include "exceptions/parser_exception.h"

void Parser::ParseCmdLineArgs(int argc, char** argv) {

    if (argc < 3) {
        throw ParserException("Invalid command line argument amount. Expected at least 3 arguments but " +
                              std::to_string(argc) + " were provided");
    }
    input_file_name_ = argv[1];
    output_file_name_ = argv[2];

    FilterDescriptor descriptor;
    for (int i = 3; i < argc; ++i) {
        // every filter description should start with '-'
        if (argv[i][0] == '-') {

            if (!descriptor.name.empty()) {
                filter_descriptors_.emplace_back(descriptor);
                descriptor.params.clear();
            }
            descriptor.name = std::string(argv[i]).substr(1);
            continue;
        }
        descriptor.params.emplace_back(argv[i]);
    }
    if (!descriptor.name.empty()) {
        filter_descriptors_.emplace_back(descriptor);
    }
}

std::string Parser::GetInputFileName() {
    return input_file_name_;
}

std::string Parser::GetOutputFileName() {
    return output_file_name_;
}

const std::vector<FilterDescriptor>& Parser::GetFilterDescriptors() {
    return filter_descriptors_;
}
