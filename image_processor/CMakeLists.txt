project(bmp_image_processor)

add_executable(
        bmp_image_processor
        application.cpp
        image_processor.cpp
        parser.cpp
        filter_producing_factory.cpp
        pipeline.cpp
        bmp.cpp
        image.cpp
        filters/crop_filter.cpp
        filters/negative_filter.cpp
        filters/grayscale_filter.cpp
        filters/matrix_filter.cpp
        filters/sharpening_filter.cpp
        filters/edge_detection_filter.cpp
        filters/cover_filter.cpp
        filters/gaussian_blur_filter.cpp
        exceptions/image_processor_exception.cpp
        exceptions/filter_producing_exception.cpp
        exceptions/parser_exception.cpp
        exceptions/image_io_exception.cpp
)

add_subdirectory(tests)