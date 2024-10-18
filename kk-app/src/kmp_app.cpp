#define SDL_HINT_WAVE_CHUNK_LIMIT 1000000000
#include <kmp_app.hpp>
#include <SDL.h>
#include <SDL_vulkan.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_vulkan.h>
#include <print>
#include <kmp_vulkan_init.hpp>
#include <ui/MusicWindow.hpp>
#include <iostream>
#include <fstream>


namespace kmp {


    struct WavHeader {
        char riff[4];
        unsigned int overall_size;
        char wave[4];
        char fmt[4];
        unsigned int fmt_size;
        unsigned short format_type;
        unsigned short channels;
        unsigned int sample_rate;
        unsigned int byterate;
        unsigned short block_align;
        unsigned short bits_per_sample;
        char data[4];
        unsigned int data_size;
    };

    bool loadWAV(const char* filename, WavHeader& header, std::vector<char>& audioData) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open WAV file." << std::endl;
            return false;
        }

        // 读取 WAV 文件头
        file.read(reinterpret_cast<char*>(&header), sizeof(WavHeader));
        if (header.riff[0] != 'R' || header.riff[1] != 'I' || header.riff[2] != 'F' || header.riff[3] != 'F') {
            std::cerr << "Not a valid WAV file!" << std::endl;
            return false;
        }

        // 读取音频数据
        size_t size = header.overall_size - sizeof(WavHeader);
        audioData.resize(size);
        file.read(audioData.data(), size);
        file.close();
        return true;
    }

    extern void kmpInitVulkan(KmpApp &app);

    static void FrameRender(ImGui_ImplVulkanH_Window *wd, ImDrawData *draw_data) {
        VkResult err;

        VkSemaphore image_acquired_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
        VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
        err = vkAcquireNextImageKHR(g_Device, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE,
                                    &wd->FrameIndex);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
            g_SwapChainRebuild = true;
            return;
        }
        check_vk_result(err);

        ImGui_ImplVulkanH_Frame *fd = &wd->Frames[wd->FrameIndex]; {
            err = vkWaitForFences(g_Device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);
            // wait indefinitely instead of periodically checking
            check_vk_result(err);

            err = vkResetFences(g_Device, 1, &fd->Fence);
            check_vk_result(err);
        } {
            err = vkResetCommandPool(g_Device, fd->CommandPool, 0);
            check_vk_result(err);
            VkCommandBufferBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
            check_vk_result(err);
        } {
            VkRenderPassBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            info.renderPass = wd->RenderPass;
            info.framebuffer = fd->Framebuffer;
            info.renderArea.extent.width = wd->Width;
            info.renderArea.extent.height = wd->Height;
            info.clearValueCount = 1;
            info.pClearValues = &wd->ClearValue;
            vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
        }

        // Record dear imgui primitives into command buffer
        ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

        // Submit command buffer
        vkCmdEndRenderPass(fd->CommandBuffer); {
            VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            VkSubmitInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            info.waitSemaphoreCount = 1;
            info.pWaitSemaphores = &image_acquired_semaphore;
            info.pWaitDstStageMask = &wait_stage;
            info.commandBufferCount = 1;
            info.pCommandBuffers = &fd->CommandBuffer;
            info.signalSemaphoreCount = 1;
            info.pSignalSemaphores = &render_complete_semaphore;

            err = vkEndCommandBuffer(fd->CommandBuffer);
            check_vk_result(err);
            err = vkQueueSubmit(g_Queue, 1, &info, fd->Fence);
            check_vk_result(err);
        }
    }

    static void FramePresent(ImGui_ImplVulkanH_Window *wd) {
        if (g_SwapChainRebuild)
            return;
        VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
        VkPresentInfoKHR info = {};
        info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &render_complete_semaphore;
        info.swapchainCount = 1;
        info.pSwapchains = &wd->Swapchain;
        info.pImageIndices = &wd->FrameIndex;
        VkResult err = vkQueuePresentKHR(g_Queue, &info);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
            g_SwapChainRebuild = true;
            return;
        }
        check_vk_result(err);
        wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->SemaphoreCount; // Now we can use the next set of semaphores
    }

    void KmpApp::init() {
        kmpInitVulkan(*this);
    }

    void KmpApp::start() {



        // mMusicPlayer.load("x97gp-807lu.wav");

        WavHeader header{};
        std::vector<char> audioData;
        if (!loadWAV("x97gp-807lu.wav", header, audioData)) {
            std::println(stderr, "Failed to load WAV file");
        }

        SDL_AudioSpec spec{};
        spec.freq = header.sample_rate;
        spec.format = AUDIO_S16SYS;
        spec.channels = header.channels;
        spec.silence = 0;
        spec.samples = audioData.size() / header.channels / (header.bits_per_sample / 8);
        spec.callback = [](void *userdata, Uint8 *stream, int len) {
            auto *audioData = static_cast<std::vector<char> *>(userdata);
            if (audioData->empty()) {
                return;
            }
            int amount = std::min(len, static_cast<int>(audioData->size()));
            std::memcpy(stream, audioData->data(), amount);
            audioData->erase(audioData->begin(), audioData->begin() + amount);
        };
        spec.userdata = &audioData;
        if (SDL_OpenAudio(&spec, nullptr) < 0) {
            std::cerr << "Failed to open audio device" << std::endl;
            std::println("{}", SDL_GetError());
            return;
        }
        SDL_PauseAudio(0);

        while (!mDone) {


            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    mDone = true;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.
                    windowID == SDL_GetWindowID(this->mWindow))
                    mDone = true;
            }

            if (SDL_GetWindowFlags(this->mWindow) & SDL_WINDOW_MINIMIZED) {
                SDL_Delay(10);
                continue;
            }

            // Resize swap chain?
            int fb_width, fb_height;
            SDL_GetWindowSize(this->mWindow, &fb_width, &fb_height);
            if (fb_width > 0 && fb_height > 0 && (
                    g_SwapChainRebuild || g_MainWindowData.Width != fb_width || g_MainWindowData.Height != fb_height)) {
                ImGui_ImplVulkan_SetMinImageCount(g_MinImageCount);
                ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, &g_MainWindowData,
                                                       g_QueueFamily, g_Allocator, fb_width, fb_height,
                                                       g_MinImageCount);
                g_MainWindowData.FrameIndex = 0;
                g_SwapChainRebuild = false;
            }

            // Start the Dear ImGui frame
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            onDraw();
        }

        this->onClose();
    }

    void KmpApp::onDraw() {
        ImGuiIO &io = ImGui::GetIO();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (this->mShowDemoWindow)
            ImGui::ShowDemoWindow(&this->mShowDemoWindow);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &(this->mShowDemoWindow)); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &this->mShowAnotherWindow);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *) &this->mClearColor); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))
                // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (this->mShowAnotherWindow) {
            ImGui::Begin("Another Window", &this->mShowAnotherWindow);
            // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                this->mShowAnotherWindow = false;
            ImGui::End();
        }

        bool active = true;
        ui::musicWindow(active, this->mMusicPlayer);

        // Rendering
        ImGui::Render();
        ImDrawData *draw_data = ImGui::GetDrawData();
        const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
        if (!is_minimized) {
            this->mWd->ClearValue.color.float32[0] = this->mClearColor.x * this->mClearColor.w;
            this->mWd->ClearValue.color.float32[1] = this->mClearColor.y * this->mClearColor.w;
            this->mWd->ClearValue.color.float32[2] = this->mClearColor.z * this->mClearColor.w;
            this->mWd->ClearValue.color.float32[3] = this->mClearColor.w;
            FrameRender(this->mWd, draw_data);
            FramePresent(this->mWd);
        }

    }

    void KmpApp::onClose() {
        // Cleanup
        auto err = vkDeviceWaitIdle(g_Device);
        check_vk_result(err);
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        CleanupVulkanWindow();
        CleanupVulkan();

        SDL_DestroyWindow(this->mWindow);
        SDL_Quit();
    }
} // namespace kmp
