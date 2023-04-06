#pragma once

#include "pipeline.h"
#include "parser.h"
#include "bmp.h"

class Application {
public:
    Application();
    void Run(int argc, char** argv);

private:
    Parser parser_;
    FilterProducingFactory factory_;
    BMP bmp_;
};