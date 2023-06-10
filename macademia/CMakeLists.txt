add_library(
    macademia include/macademia/macademia.h src/log.c src/window.c
    include/macademia/window.h
)
set_property(TARGET macademia PROPERTY C_STANDARD 99)

target_include_directories(macademia PUBLIC include)
target_include_directories(macademia PUBLIC vendor/glad/include)

find_package(X11)
if (X11_FOUND)
    target_sources(macademia PRIVATE src/platform/x11/x11window.c)
    target_sources(macademia PRIVATE vendor/glad/src/gl.c vendor/glad/include/glad/gl.h)
    target_link_libraries(macademia PUBLIC X11::X11)
    target_link_libraries(macademia PUBLIC GL)
endif()

if (WIN32)
    target_sources(macademia PRIVATE src/platform/win32/win32window.c)
    target_sources(macademia PRIVATE vendor/glad/src/gl.c vendor/glad/src/wgl.c vendor/glad/include/glad/gl.h vendor/glad/include/glad/wgl.h)
endif()