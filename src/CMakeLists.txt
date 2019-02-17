set(CMAKE_CXX_STANDARD 11)

set(PROBLEMS
    prob3.h
)

set(HEADERS
    common/math.h
    common/mem.h
    common/types.h
    common/util.h

    ${PROBLEMS}
)

set(SOURCES
    main.cpp

    common/log.cpp
    common/mem.cpp
    common/util.cpp
    common/math.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
