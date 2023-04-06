#include <catch.hpp>

#include "../parser.h"

TEST_CASE("Parser") {
    Parser parser;
    int argc = 3;

    std::string binary = "binary";
    std::string input = "input";
    std::string output = "output";

    char* argv[] = {binary.data(), input.data(), output.data()};
    parser.ParseCmdLineArgs(argc, argv);

    REQUIRE(parser.GetInputFileName() == input);
    REQUIRE(parser.GetOutputFileName() == output);
    REQUIRE(parser.GetFilterDescriptors().empty());

    argc += 3;
    std::string crop = "-crop";
    std::string param1 = "100";
    std::string param2 = "200";

    char* argv2[] = {binary.data(), input.data(), output.data(), crop.data(), param1.data(), param2.data()};
    Parser parser1;
    parser1.ParseCmdLineArgs(argc, argv2);

    REQUIRE(parser1.GetInputFileName() == input);
    REQUIRE(parser1.GetOutputFileName() == output);
    REQUIRE(parser1.GetFilterDescriptors().size() == 1);
    REQUIRE(parser1.GetFilterDescriptors()[0].name == crop.substr(1));
    REQUIRE(parser1.GetFilterDescriptors()[0].params == std::vector<std::string>{param1, param2});
}