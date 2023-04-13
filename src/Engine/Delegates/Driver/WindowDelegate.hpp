#pragma once
#include <utilities/typeAliases.hpp>
#include <utilities/Includes/graphicInclude.hpp>

class WindowDelegate
{
private:
    //Typedef for Window UniquePtr 
    using WindowHandler = UniqPtr<GLFWwindow, void(*)(GLFWwindow*)>;

    //Window handler
    WindowHandler window { nullptr, nullptr };

    //Window title
    String window_title { "Window" };
    //Resolution of the window
    size_t width { 1280 }, heigth { 720 };

private:
    /**
     *  @brief It initialices the GLFW lib
    */
    void
    initGLFW() const noexcept;

    /**
     *  @brief It creates the window
    */
    void
    createWindow() noexcept;

public:
    explicit WindowDelegate( String p_windowName, size_t p_w, size_t p_h ) noexcept;
    ~WindowDelegate() = default;

    /**
     *  @brief Static method that finalices the window and GLFW execution
     * 
     *  @param p_window Pointer to the window for destruction
    */
    static
    void deleteWindow(GLFWwindow* p_window)
    {
        glfwDestroyWindow( p_window );
        glfwTerminate();
    }

    /**
     *  @brief Getter to obtain a reference to the window
     * 
     *  @return Reference to the GLFWwindow
    */
    GLFWwindow&
    getWindow()
    {
        return *window.get();
    }
};