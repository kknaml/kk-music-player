#pragma once

#include <imgui_impl_vulkan.h>
#include <kmp_common.hpp>
#include <SDL_video.h>

namespace kmp {

    class KmpApp : NonCopy {
    public:
        friend void kmpInitVulkan(KmpApp &app);
        void init();

        void start();

        void onDraw();

        void onClose();

    private:
        SDL_Window *mWindow{nullptr};
        ImGui_ImplVulkanH_Window *mWd{nullptr};
        bool mDone{false};
        ImVec4 mClearColor{0.45f, 0.55f, 0.60f, 1.00f};
        bool mShowDemoWindow{true};
        bool mShowAnotherWindow{false};
    };

} // namespace kmp