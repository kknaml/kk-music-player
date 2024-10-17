#pragma once
#include <imgui_impl_vulkan.h>
#include <vulkan/vulkan_core.h>


namespace kmp {

    extern VkAllocationCallbacks *g_Allocator;
    extern VkInstance g_Instance;
    extern VkPhysicalDevice g_PhysicalDevice;
    extern VkDevice g_Device;
    extern uint32_t g_QueueFamily;
    extern VkQueue g_Queue;
    extern VkDebugReportCallbackEXT g_DebugReport;
    extern VkPipelineCache g_PipelineCache;
    extern VkDescriptorPool g_DescriptorPool;


    extern ImGui_ImplVulkanH_Window g_MainWindowData;
    extern uint32_t g_MinImageCount;
    extern bool g_SwapChainRebuild;

    void check_vk_result(VkResult err);

    void CleanupVulkan();

    void CleanupVulkanWindow();
} // namespace kmp
