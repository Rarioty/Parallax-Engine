# PIL project

set (Core_SRCS
    Parsers/CSV/CSVRow.cpp
    Parsers/CSV/CSVParser.cpp
)

add_library (Core STATIC ${Core_SRCS})
add_coverage (Core)
