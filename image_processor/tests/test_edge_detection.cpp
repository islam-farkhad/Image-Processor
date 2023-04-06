#include <catch.hpp>

#include "../bmp.h"
#include "../filters/edge_detection_filter.h"

#include <memory>

TEST_CASE("EdgeDetection") {
    BMP bmp;
    const std::string path = "../image_processor/test_script/data/flag.bmp";
    bmp.Read(path);

    const double threshold = 0.1;

    std::shared_ptr<Filter> crop = std::make_shared<EdgeDetection>(threshold);

    crop->Apply(bmp.GetImage());

    BMP bmp1;
    const std::string path1 = "../image_processor/test_script/data/flag_edge.bmp";
    bmp1.Read(path1);

    REQUIRE(bmp1.GetImage() == bmp.GetImage());
}
