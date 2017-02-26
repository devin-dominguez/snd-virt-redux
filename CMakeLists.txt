project(ofApp)
set(APP ofApp)

cmake_minimum_required(VERSION 2.8)

set(OF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../of/" CACHE PATH "The root directory of ofnode/of project.")
include(${OF_ROOT}/openFrameworks.cmake)

#ofxaddon()

option(COTIRE "Use cotire" ON)

set(SOURCES
    src/main.cpp
    src/ofApp.cpp
    src/projector.cpp
    src/fake_height.cpp
    src/virt/entity.cpp
    src/virt/pulsar.cpp
    src/virt/node.cpp
    src/virt/pulse_node.cpp
    src/virt/rocket_node.cpp
    src/virt/blimp_node.cpp
    src/virt/pulse.cpp
    src/virt/virt.cpp
    src/virt/rocket.cpp
    src/virt/blimp.cpp
    src/virt/explosion.cpp
    src/virt/trail.cpp
    src/virt/depth_physics.cpp

)

include_directories(
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/virt"
)

add_executable(
    ${APP}
    MACOSX_BUNDLE
    ${SOURCES}
    ${OFXADDONS_SOURCES}
)

target_link_libraries(
    ${APP}
    ${OPENFRAMEWORKS_LIBRARIES}
)

set_target_properties(
    ${APP} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST
    "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties( ${APP} PROPERTIES OUTPUT_NAME "${APP}-Debug")
endif()

if (CMAKE_CROSSCOMPILING)
    set_target_properties( ${APP} PROPERTIES OUTPUT_NAME
      "${APP}-${OF_PLATFORM}-${CMAKE_BUILD_TYPE}")
endif()

if (COTIRE)
    cotire(${APP})
endif()
