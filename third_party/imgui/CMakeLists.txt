
file(GLOB_RECURSE IMGUI_SOURCES ./*.cpp)

find_package(SDL REQUIRED)
find_package(Vulkan REQUIRED)

add_library(IMGUI STATIC ${IMGUI_SOURCES})
target_include_directories(IMGUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(IMGUI PUBLIC ${SDL_INCLUDE_DIR})
target_link_libraries(IMGUI PUBLIC SDL2::SDL2-static Vulkan::Vulkan)
# target_include_directories(IMGUI PUBLIC /third_party/SDL2/include)