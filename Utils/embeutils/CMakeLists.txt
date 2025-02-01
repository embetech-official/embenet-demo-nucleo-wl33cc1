add_library(embeutils INTERFACE)

target_include_directories(
  embeutils INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                      $<INSTALL_INTERFACE:include>
)

add_library(embetech::utils ALIAS embeutils)

if (EMBEUTILS_EXPECT_VERBOSE)
  target_compile_definitions(embeutils INTERFACE EMBEUTILS_EXPECT_VERBOSE=1)
endif ()

if (EMBEUTILS_EXTRA_CHECKS)
  target_compile_definitions(embeutils INTERFACE EMBEUTILS_EXTRA_CHECKS=1)
endif ()

