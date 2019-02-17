set(CMAKE_CXX_STANDARD 11)

set(HEADERS
    common/math.h
    common/mem.h
    common/types.h
    common/util.h
)

set(SOURCES
    main.cpp

    common/log.cpp
    common/mem.cpp
    common/util.cpp
    common/math.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
