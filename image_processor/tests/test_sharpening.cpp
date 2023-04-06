#include <catch.hpp>

#include "../bmp.h"
#include "../filters/sharpening_filter.h"

#include <memory>

TEST_CASE("Sharpening") {
    BMP bmp;
    const std::string path = "../image_processor/test_script/data/flag.bmp";
    bmp.Read(path);

    std::shared_ptr<Filter> crop = std::make_shared<Sharpening>();
    crop->Apply(bmp.GetImage());

    BMP bmp1;
    const std::string path1 = "../image_processor/test_script/data/flag_sharp.bmp";
    bmp1.Read(path1);

    REQUIRE(bmp1.GetImage() == bmp.GetImage());
}
