#include <catch.hpp>

#include "../bmp.h"
#include "../filters/crop_filter.h"

TEST_CASE("Crop") {
    BMP bmp;
    const std::string path = "../image_processor/test_script/data/lenna.bmp";
    bmp.Read(path);

    const size_t w = 999;
    const size_t h = 1999;

    std::shared_ptr<Filter> crop = std::make_shared<Crop>(h, w);

    crop->Apply(bmp.GetImage());

    BMP bmp1;
    const std::string path1 = "../image_processor/test_script/data/lenna_crop.bmp";
    bmp1.Read(path1);

    REQUIRE(bmp1.GetImage() == bmp.GetImage());
}
