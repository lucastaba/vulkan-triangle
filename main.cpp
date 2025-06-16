#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication
{
public:
    void run()
    {
        m_initWindow();
        m_initVulkan();
        m_mainLoop();
        m_cleanup();
    }

private:
    GLFWwindow* m_window;
    const uint32_t m_WIDTH = 800;
    const uint32_t m_HEIGHT = 600;

    void m_initWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void m_initVulkan()
    {

    }

    void m_mainLoop()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();
        }
    }

    void m_cleanup()
    {
        glfwDestroyWindow(m_window);

        glfwTerminate();
    }
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}