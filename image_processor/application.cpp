#include "application.h"

#include <iostream>

Application::Application() : factory_{
          {.filter_name = "crop", .filter_producer = &ProduceCrop},
          {.filter_name = "neg", .filter_producer = &ProduceNegative},
          {.filter_name = "gs", .filter_producer = &ProduceGrayScale},
          {.filter_name = "sharp", .filter_producer = &ProduceSharpening},
          {.filter_name = "edge", .filter_producer = &ProduceEdgeDetection},
          {.filter_name = "cover", .filter_producer = &ProduceCover},
          {.filter_name = "blur", .filter_producer = &ProduceGaussianBlur}
      } {
}

void Application::Run(int argc, char **argv) {
    try {
        parser_.ParseCmdLineArgs(argc, argv);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    Pipeline pipeline(parser_.GetFilterDescriptors(), factory_);

    try {
        bmp_.Read(parser_.GetInputFileName());
        pipeline.ProcessImage(bmp_.GetImage());
        bmp_.Write(parser_.GetOutputFileName());

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

