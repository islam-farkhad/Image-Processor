add_catch(
        test_image_processor
        test_parser.cpp
        test_bmp_read.cpp
        test_bmp_write.cpp
        test_crop.cpp
        test_edge_detection.cpp
        test_gray_scale.cpp
        test_negative.cpp
        test_sharpening.cpp

        ../application.cpp
        ../bmp.cpp
        ../filter_producing_factory.cpp
        ../image.cpp
        ../parser.cpp
        ../pipeline.cpp

        ../filters/cover_filter.cpp
        ../filters/crop_filter.cpp
        ../filters/edge_detection_filter.cpp
        ../filters/gaussian_blur_filter.cpp
        ../filters/grayscale_filter.cpp
        ../filters/matrix_filter.cpp
        ../filters/negative_filter.cpp
        ../filters/sharpening_filter.cpp

        ../exceptions/filter_producing_exception.cpp
        ../exceptions/image_processor_exception.cpp
        ../exceptions/image_io_exception.cpp
        ../exceptions/parser_exception.cpp
)
