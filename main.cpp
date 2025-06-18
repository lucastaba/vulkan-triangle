#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

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
    VkInstance m_instance;
    const uint32_t m_WIDTH = 800;
    const uint32_t m_HEIGHT = 600;

    void m_createInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtentions;

        glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtentions;
        createInfo.enabledLayerCount = 0;

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:\n";
        for (const auto& extension : extensions)
        {
            std::cout << "\t" << extension.extensionName << "::" << extension.specVersion << '\n';
        }

        int missing_extensions = 0;
        int not_found;
        std::cout << "check required extensions:\n";
        for (int i=0; i < glfwExtensionCount; i++)
        {
            not_found = 0;
            if (std::find_if(extensions.begin(),extensions.end(),
                [&](VkExtensionProperties extension)->bool {
                    return !std::strncmp(extension.extensionName, glfwExtentions[i], strlen(glfwExtentions[i]));
                }) == extensions.end())
            {
                not_found++;
                missing_extensions++;
            }
            std::cout << "\t" << glfwExtentions[i] << "\t::" << (not_found? "No" : "Yes") << '\n';
        }
        std::cout << "Missing a total of [" << missing_extensions << "] extensions...\n";
        if (missing_extensions)
        {
            throw std::runtime_error("missing extensions!");
        }
        
        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }

    }

    void m_initWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void m_initVulkan()
    {
        m_createInstance();
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
        vkDestroyInstance(m_instance, nullptr);
        
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