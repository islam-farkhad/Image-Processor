#include <catch.hpp>

#include "../bmp.h"

TEST_CASE("Bmp Write correctness") {
    BMP bmp1;
    const std::string input_path =
        "/home/islam/pmi-223-2-Islam-Farkhad-islam.farhad.ba/tasks/image_processor/test_script/data/flag.bmp";
    const std::string output_path =
        "/home/islam/pmi-223-2-Islam-Farkhad-islam.farhad.ba/tasks/image_processor/tests/flag_new.bmp";

    bmp1.Read(input_path);
    bmp1.Write(output_path);

    BMP bmp2;
    BMP bmp3;
    bmp2.Read(input_path);
    bmp3.Read(output_path);

    Image& img2 = bmp2.GetImage();
    Image& img3 = bmp3.GetImage();

    REQUIRE(img2 == img3);
    bmp1.Remove(output_path);
}
