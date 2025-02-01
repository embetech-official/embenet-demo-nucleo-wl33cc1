cmake_minimum_required(VERSION 3.21)

add_library(crc STATIC crc16.c crc32.c crc8.c)
target_include_directories(
  crc PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

add_library(embetech::crc ALIAS crc)

if (CRC_USE_LUT_16)
  target_compile_definitions(crc PRIVATE CRC16_CCITT_USE_LUT=1 CRC16_MODBUS_USE_LUT=1)
endif ()

find_package(embetile QUIET)
if (embetile_FOUND)
  include(embetile_utils)

  target_sources(crc PRIVATE crc_embetile_api.c)
  target_compile_definitions(
    crc
    PRIVATE CRC_VERSION_MAJOR=${PROJECT_VERSION_MAJOR} CRC_VERSION_MINOR=${PROJECT_VERSION_MINOR}
            CRC_VERSION_PATCH=${PROJECT_VERSION_PATCH}
  )
  target_link_libraries(crc PRIVATE embetech::embetile)

  embetile_make_available(crc)
endif ()

if (CRC_INSTALL OR PROJECT_IS_TOP_LEVEL)
  include(${PROJECT_SOURCE_DIR}/cmake/crc_install.cmake)
endif ()
