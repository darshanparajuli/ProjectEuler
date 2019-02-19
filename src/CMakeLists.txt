set(CMAKE_CXX_STANDARD 11)

set(HEADERS
    common/math.h
    common/mem.h
    common/types.h
    common/util.h

    prob3.h
    prob4.h
    prob5.h
    prob6.h
    prob7.h
    prob8.h
    prob9.h
    prob10.h
    prob11.h
    prob12.h
    prob13.h
    prob14.h
    prob15.h
    prob16.h
)

set(SOURCES
    main.cpp

    common/log.cpp
    common/mem.cpp
    common/util.cpp
    common/math.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
