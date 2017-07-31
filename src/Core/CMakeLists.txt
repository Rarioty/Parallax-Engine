# PIL project

set (Core_SRCS
    Settings.cpp

    Parsers/CSV/CSVRow.cpp
    Parsers/CSV/CSVParser.cpp

    Parsers/PSF/PSFParser.cpp
)

add_library (Core STATIC ${Core_SRCS})
add_coverage (Core)
