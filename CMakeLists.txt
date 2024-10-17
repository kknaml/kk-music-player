cmake_minimum_required(VERSION 3.27)
project(kk-emm)

set(CMAKE_CXX_STANDARD 26)

set(SDL_LIBRARY /third_party/SDL2/src)
set(SDL_INCLUDE_DIR /third_party/SDL2/include)

set(DCMAKE_TOOLCHAIN_FILE ～/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)

# add_subdirectory(third_party/vulkan-sample)
add_subdirectory(third_party/SDL2)
add_subdirectory(third_party/imgui)
add_subdirectory(kk-app)