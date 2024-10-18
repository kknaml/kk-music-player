//
// Created by ywnkm on 2024/10/17.
//

#include <corecrt_math.h>
#include <imgui.h>
#include <ui/MusicWindow.hpp>

namespace kmp::ui {
    void musicWindow(bool &active, MusicPlayer &player) {
        ImGui::Begin("Music Window", &active);

        float samples[128];
        for (int i = 0; i < 128; i++) {
            samples[i] = sinf(i * 0.2f + ImGui::GetTime() * 1.5f);
        }

        ImGui::PlotLines("Samples", samples, 128);

        ImGui::End();
    }
}
