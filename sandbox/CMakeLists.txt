add_executable(sandbox src/main.c)

find_package(OpenGL REQUIRED)

target_link_libraries(sandbox PRIVATE ma-window ${OPENGL_gl_LIBRARY})

if(WIN32)
    target_compile_definitions(sandbox PRIVATE WIN32)
endif()

if (LINUX)
    target_link_libraries(sandbox PRIVATE GL)
endif()
