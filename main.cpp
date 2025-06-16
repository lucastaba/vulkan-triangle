#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication
{
public:
    void run()
    {
        m_initVulkan();
        m_mainLoop();
        m_cleanup();
    }

private:
    void m_initVulkan()
    {

    }

    void m_mainLoop()
    {

    }

    void m_cleanup()
    {

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