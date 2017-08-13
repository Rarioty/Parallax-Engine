# PIL project

set (Core_SRCS
    Settings.cpp
    ID.cpp

    Maths/Hash.cpp

    Video/Demultiplexer.cpp
    Video/Video.cpp

    Video/Decoders/VideoDecoder.cpp

    Parsers/CSV/CSVParser.cpp
    Parsers/CSV/CSVRow.cpp

    Parsers/PSF/PSFParser.cpp
)

add_library (Core STATIC ${Core_SRCS})
target_link_libraries(Core PIL)
target_link_libraries(Core ${FFMPEG_LIBRARIES})
add_coverage (Core)
