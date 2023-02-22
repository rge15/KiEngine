#include "WindowDelegate.hpp"
#include <utilities/MacrosAssert.hpp>

WindowDelegate::WindowDelegate( String p_windowName, size_t p_w, size_t p_h )
: window_name { p_windowName }, width { p_w }, heigth { p_h }
{
    initGLFW();
    createWindow();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
WindowDelegate::initGLFW() const noexcept
{
    glfwInit();

    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
WindowDelegate::createWindow() noexcept
{
    WindowHandler t_window {
        glfwCreateWindow( width, heigth, window_name.data(), nullptr, nullptr),
        deleteWindow
    };

    ASSERT( t_window.get(), "Window Creation Failed" )

    window = std::move(t_window);
}