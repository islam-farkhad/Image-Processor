#include <catch.hpp>

#include "../bmp.h"

TEST_CASE("Bmp Read correctness") {
    BMP bmp;
    const std::string path =
        "/home/islam/pmi-223-2-Islam-Farkhad-islam.farhad.ba/tasks/image_processor/test_script/data/flag.bmp";
    bmp.Read(path);

    const uint16_t signature = 19778;  // "BM"

    REQUIRE(bmp.GetDIBHeader().image_height == bmp.GetImage().GetHeight());
    REQUIRE(bmp.GetDIBHeader().image_width == bmp.GetImage().GetWidth());
    REQUIRE(bmp.GetBMPHeader().signature == signature);
}
