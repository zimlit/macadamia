ma-window
=========

this is a simple windowing library used by macademia.

.. code-block:: c
    :caption: Sample code that makes a window with a purple background.

    #include <ma-window/ma-window.h>
    #include <GL/gl.h>

    int main() {
        MaWindow *window = maWindowNew(640, 480, "Hello, World!");
        if (!window)
            return 1;
        if (!maWindowMakeGlContext(window, 4, 0))
            return 1;
        while (maWindowPollEvents(window)) {
            glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            maWindowSwapBuffers(window);
        }
        maWindowFree(window);
        return 0;
    }

.. c:struct:: MaWindow

    Represents a window. Manages its own display server connection and graphics contexts.

    .. c:member:: int width
            
            The width of the window.
    .. c:member:: int height
            
            The height of the window.

    .. c:member:: const char *title
            
            The title of the window.
    
    .. c:member:: bool hasGlContext
            
            Whether the window has a OpenGL context.
    
    .. c:member:: void (*mouseMovedCallback)(int x, int y)
        
            Is called in the event loop when the mouse is moved.
    
    .. c:member:: void (*resizeCallback)(int width, int height)
        
            Is called in the event loop when the window is resized.

.. c:function:: MaWindow *maWindowNew(int width, int height, const char *title);
    
    Initializes a new window. Returns NULL on failure

.. c:function:: void maWindowFree(MaWindow *window);
    
    Frees a window along with its asociated graphics contexts.

.. c:function:: bool maWindowPollEvents(MaWindow *window);
        
    Polls the window for events. Returns true if the window is still open.

.. c:function:: void maWindowSwapBuffers(MaWindow *window);

    Swaps the buffers of the window.

.. c:function:: void maWindowMouseMovedCallback(MaWindow *window, void (*callback)(int x, int y));
    
    Sets the mouse moved callback of the window.

.. c:function:: void maWindowResizeCallback(MaWindow *window, void (*callback)(int width, int height));
        
    Sets the resize callback of the window.

.. c:function:: void maWindowMakeGlContext(MaWindow *window, int glVersionMajor, int glVersionMinor);
    
    Initializes an OpenGL context with the specified version.