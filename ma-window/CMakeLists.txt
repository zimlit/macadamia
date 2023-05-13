add_library(ma-window src/ma-window.c include/ma-window/ma-window.h)

set_property(TARGET ma-window PROPERTY C_STANDARD 99)

target_include_directories(ma-window PUBLIC include)
target_include_directories(ma-window PUBLIC vendor/glad/include)

find_package(X11)
if (X11_FOUND)
    target_sources(ma-window PRIVATE src/x11.c)
    target_sources(ma-window PRIVATE vendor/glad/src/gl.c vendor/glad/include/glad/gl.h)
    target_link_libraries(ma-window PUBLIC X11::X11)
    target_link_libraries(ma-window PUBLIC GL)
endif()

if (WIN32)
    target_sources(ma-window PRIVATE src/win32.c)
    target_sources(ma-window PRIVATE vendor/glad/src/gl.c vendor/glad/src/wgl.c vendor/glad/include/glad/gl.h vendor/glad/include/glad/wgl.h)
endif()
