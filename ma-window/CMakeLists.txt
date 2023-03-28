add_library(ma-window include/ma-window/ma-window.h)

target_include_directories(ma-window PUBLIC include)

find_package(X11)
if (X11_FOUND)
    target_sources(ma-window PRIVATE src/x11.c)
    target_link_libraries(ma-window PUBLIC X11::X11)
endif()