#include <utilities/typeAliases.hpp>
#include <utilities/Includes/graphicInclude.hpp>

class WindowDelegate
{
private:
    using WindowHandler = UniqPtr<GLFWwindow, void(*)(GLFWwindow*)>;

    WindowHandler window { nullptr, nullptr };

    String window_name { "Window" };
    size_t width { 1280 }, heigth { 720 };

private:
    void
    initGLFW() const noexcept;

    void
    createWindow() noexcept;

public:
    WindowDelegate( String p_windowName = "KiEngine", size_t p_w = 1280 , size_t p_h = 720 );
    ~WindowDelegate() = default;

    static
    void deleteWindow(GLFWwindow* p_window)
    {
        glfwDestroyWindow( p_window );
        glfwTerminate();
    }
};