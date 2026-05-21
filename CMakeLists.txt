cmake_minimum_required(VERSION 3.21)

project(Kitra
    VERSION 0.2.0
    DESCRIPTION "A minimal, beginner-friendly 2D graphics library built on SDL2"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ============================================================
# Dependencies
# ============================================================

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2       REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_GFX   REQUIRED IMPORTED_TARGET SDL2_gfx)
pkg_check_modules(SDL2_TTF   REQUIRED IMPORTED_TARGET SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)

# ============================================================
# kitra_math — header-only interface library
# ============================================================

add_library(kitra_math INTERFACE)
add_library(Kitra::Math ALIAS kitra_math)

target_include_directories(kitra_math
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(kitra_math INTERFACE m)

# ============================================================
# kitra — main static library
# ============================================================

add_library(kitra STATIC
    src/kitra_subsystem.c
    src/kitra_color.c
    src/kitra_window.c
    src/kitra_loop.c
    src/kitra_timer.c
    src/kitra_input.c
    src/kitra_draw.c
    src/kitra_texture.c
    src/kitra_text.c
    src/kitra_error.c
    src/kitra_rng.c
    src/kitra_audio.c
    src/kitra_dialog.c
    src/kitra_surface.c
)
add_library(Kitra::Kitra ALIAS kitra)

target_include_directories(kitra
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(kitra PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wdouble-promotion
    -Wformat=2
    -Wundef
)

if(NOT APPLE)
    target_link_options(kitra PRIVATE -Wl,--allow-shlib-undefined)
endif()

target_link_libraries(kitra
    PUBLIC  Kitra::Math
    PRIVATE
        PkgConfig::SDL2
        PkgConfig::SDL2_IMAGE
        PkgConfig::SDL2_GFX
        PkgConfig::SDL2_TTF
        PkgConfig::SDL2_MIXER
)

# ============================================================
# Examples
# ============================================================

# foreach(EXAMPLE pong snake pendulum)
#     add_executable(${EXAMPLE} examples/${EXAMPLE}/${EXAMPLE}.c)

#     if(NOT APPLE)
#         target_link_options(${EXAMPLE} PRIVATE -Wl,--allow-shlib-undefined)
#     endif()

#     target_link_libraries(${EXAMPLE} PRIVATE Kitra::Kitra)
#     set_target_properties(${EXAMPLE} PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#     )
# endforeach()

# ============================================================
# Install
# ============================================================

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS kitra kitra_math
    EXPORT  KitraTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES
    include/kitra/kitra.h
    include/kitra/kitra_types.h
    include/kitra/kitra_math.h
    include/kitra/kitra_status.h
    include/kitra/kitra_subsystem.h
    include/kitra/kitra_window.h
    include/kitra/kitra_loop.h
    include/kitra/kitra_timer.h
    include/kitra/kitra_input.h
    include/kitra/kitra_color.h
    include/kitra/kitra_draw.h
    include/kitra/kitra_texture.h
    include/kitra/kitra_text.h
    include/kitra/kitra_error.h
    include/kitra/kitra_rng.h
    include/kitra/kitra_audio.h
    include/kitra/kitra_dialog.h
    include/kitra/kitra_surface.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/kitra
)

install(EXPORT KitraTargets
    FILE      KitraTargets.cmake
    NAMESPACE Kitra::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Kitra
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/KitraConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/KitraConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KitraConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Kitra
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KitraConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KitraConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Kitra
)

# ============================================================
# pkg-config
# ============================================================

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/kitra.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/kitra.pc"
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/kitra_math.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/kitra_math.pc"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/kitra.pc"
    "${CMAKE_CURRENT_BINARY_DIR}/kitra_math.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)