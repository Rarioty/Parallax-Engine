# PIL project

set (Core_SRCS
    Settings.cpp
    ID.cpp

    Maths/Hash.cpp

    Parsers/CSV/CSVParser.cpp
    Parsers/CSV/CSVRow.cpp

    Parsers/PSF/PSFParser.cpp
)

add_library (Core STATIC ${Core_SRCS})
add_coverage (Core)
