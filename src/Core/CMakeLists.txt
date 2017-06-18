# PIL project

set (Core_SRCS
    Parsers/CSV/CSVRow.cpp
)

add_library (Core SHARED ${Core_SRCS})
add_coverage (Core)
