add_library(ma-window src/ma-window.c include/ma-window/ma-window.h)

set_property(TARGET ma-window PROPERTY C_STANDARD 99)

target_include_directories(ma-window PUBLIC include)

find_package(X11)
if (X11_FOUND)
    target_sources(ma-window PRIVATE src/x11.c)
    target_link_libraries(ma-window PUBLIC X11::X11)
endif()