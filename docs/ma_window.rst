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
        
        Is called by :c:func:`maWindowPollEvents` when the mouse is moved.
    
    .. c:member:: void (*resizeCallback)(int width, int height)
        
        Is called by :c:func:`maWindowPollEvents` when the window is resized.
    
    .. c:member:: void (*keyPressedCallback)(int key)
        
        Is called by :c:func:`maWindowPollEvents` when a key is pressed.

    .. c:member:: void (*KeyReleasedCallback)(int key)
        
        Is called by :c:func:`maWindowPollEvents` when a key is released.

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

.. c:function:: void maWindowKeyPresedCallback(MaWindow *window, void (*callback)(int key));
        
    Sets the key pressed callback of the window.

.. c:function:: void maWindowKeyReleasedCallback(MaWindow *window, void (*callback)(int key));
            
    Sets the key released callback of the window.

.. c:function:: void maWindowMakeGlContext(MaWindow *window, int glVersionMajor, int glVersionMinor);
    
    Initializes an OpenGL context with the specified version.

Keycodes
--------

.. c:macro:: MA_KEY_SPACE              
.. c:macro:: MA_KEY_APOSTROPHE         
.. c:macro:: MA_KEY_COMMA               
.. c:macro:: MA_KEY_MINUS               
.. c:macro:: MA_KEY_PERIOD              
.. c:macro:: MA_KEY_SLASH               
.. c:macro:: MA_KEY_0                  
.. c:macro:: MA_KEY_1                  
.. c:macro:: MA_KEY_2                  
.. c:macro:: MA_KEY_3                  
.. c:macro:: MA_KEY_4                  
.. c:macro:: MA_KEY_5                  
.. c:macro:: MA_KEY_6                  
.. c:macro:: MA_KEY_7                  
.. c:macro:: MA_KEY_8                  
.. c:macro:: MA_KEY_9                  
.. c:macro:: MA_KEY_SEMICOLON           
.. c:macro:: MA_KEY_EQUAL               
.. c:macro:: MA_KEY_A                  
.. c:macro:: MA_KEY_B                  
.. c:macro:: MA_KEY_C                  
.. c:macro:: MA_KEY_D                  
.. c:macro:: MA_KEY_E                  
.. c:macro:: MA_KEY_F                  
.. c:macro:: MA_KEY_G                  
.. c:macro:: MA_KEY_H                  
.. c:macro:: MA_KEY_I          
.. c:macro:: MA_KEY_J                  
.. c:macro:: MA_KEY_K                  
.. c:macro:: MA_KEY_L                  
.. c:macro:: MA_KEY_M                  
.. c:macro:: MA_KEY_N                  
.. c:macro:: MA_KEY_O                  
.. c:macro:: MA_KEY_P                  
.. c:macro:: MA_KEY_Q                  
.. c:macro:: MA_KEY_R                  
.. c:macro:: MA_KEY_S                  
.. c:macro:: MA_KEY_T                  
.. c:macro:: MA_KEY_U                  
.. c:macro:: MA_KEY_V                  
.. c:macro:: MA_KEY_W                  
.. c:macro:: MA_KEY_X                  
.. c:macro:: MA_KEY_Y                  
.. c:macro:: MA_KEY_Z                  
.. c:macro:: MA_KEY_LEFT_BRACKET       
.. c:macro:: MA_KEY_BACKSLASH          
.. c:macro:: MA_KEY_RIGHT_BRACKET      
.. c:macro:: MA_KEY_GRAVE_ACCENT       
.. c:macro:: MA_KEY_ESCAPE           
.. c:macro:: MA_KEY_ENTER            
.. c:macro:: MA_KEY_TAB              
.. c:macro:: MA_KEY_BACKSPACE        
.. c:macro:: MA_KEY_INSERT           
.. c:macro:: MA_KEY_DELETE           
.. c:macro:: MA_KEY_RIGHT            
.. c:macro:: MA_KEY_LEFT             
.. c:macro:: MA_KEY_DOWN             
.. c:macro:: MA_KEY_UP               
.. c:macro:: MA_KEY_PAGE_UP          
.. c:macro:: MA_KEY_PAGE_DOWN        
.. c:macro:: MA_KEY_HOME             
.. c:macro:: MA_KEY_END              
.. c:macro:: MA_KEY_CAPS_LOCK        
.. c:macro:: MA_KEY_SCROLL_LOCK      
.. c:macro:: MA_KEY_NUM_LOCK         
.. c:macro:: MA_KEY_PRINT_SCREEN     
.. c:macro:: MA_KEY_PAUSE            
.. c:macro:: MA_KEY_F1               
.. c:macro:: MA_KEY_F2               
.. c:macro:: MA_KEY_F3               
.. c:macro:: MA_KEY_F4               
.. c:macro:: MA_KEY_F5               
.. c:macro:: MA_KEY_F6               
.. c:macro:: MA_KEY_F7               
.. c:macro:: MA_KEY_F8               
.. c:macro:: MA_KEY_F9               
.. c:macro:: MA_KEY_F10              
.. c:macro:: MA_KEY_F11              
.. c:macro:: MA_KEY_F12              
.. c:macro:: MA_KEY_F13              
.. c:macro:: MA_KEY_F14              
.. c:macro:: MA_KEY_F15              
.. c:macro:: MA_KEY_F16              
.. c:macro:: MA_KEY_F17              
.. c:macro:: MA_KEY_F18              
.. c:macro:: MA_KEY_F19              
.. c:macro:: MA_KEY_F20              
.. c:macro:: MA_KEY_F21              
.. c:macro:: MA_KEY_F22              
.. c:macro:: MA_KEY_F23              
.. c:macro:: MA_KEY_F24              
.. c:macro:: MA_KEY_F25              
.. c:macro:: MA_KEY_KP_0             
.. c:macro:: MA_KEY_KP_1             
.. c:macro:: MA_KEY_KP_2             
.. c:macro:: MA_KEY_KP_3             
.. c:macro:: MA_KEY_KP_4             
.. c:macro:: MA_KEY_KP_5             
.. c:macro:: MA_KEY_KP_6             
.. c:macro:: MA_KEY_KP_7             
.. c:macro:: MA_KEY_KP_8             
.. c:macro:: MA_KEY_KP_9             
.. c:macro:: MA_KEY_KP_DECIMAL       
.. c:macro:: MA_KEY_KP_DIVIDE        
.. c:macro:: MA_KEY_KP_MULTIPLY      
.. c:macro:: MA_KEY_KP_SUBTRACT      
.. c:macro:: MA_KEY_KP_ADD           
.. c:macro:: MA_KEY_KP_ENTER         
.. c:macro:: MA_KEY_KP_EQUAL         
.. c:macro:: MA_KEY_LEFT_SHIFT       
.. c:macro:: MA_KEY_LEFT_CONTROL     
.. c:macro:: MA_KEY_LEFT_ALT         
.. c:macro:: MA_KEY_LEFT_SUPER       
.. c:macro:: MA_KEY_RIGHT_SHIFT      
.. c:macro:: MA_KEY_RIGHT_CONTROL    
.. c:macro:: MA_KEY_RIGHT_ALT        
.. c:macro:: MA_KEY_RIGHT_SUPER      
.. c:macro:: MA_KEY_MENU             