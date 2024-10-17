
file(GLOB_RECURSE SOURCE_FILES src/**.cpp)
file(GLOB_RECURSE MODULE_FILES src/**.ixx)

add_executable(kk-emm ${SOURCE_FILES})

# target_include_directories(kk-emm PUBLIC include /home/rainy/project/kk-emm/third_party/SDL2/include)

#target_sources(
#        kk-emm
#        PUBLIC
#        FILE_SET CXX_MODULES
#        TYPE CXX_MODULES
#        FILES ${MODULE_FILES}
#)

# find_package(IMGUI CONFIG)
target_link_libraries(kk-emm PUBLIC IMGUI)
# target_include_directories(kk-emm PUBLIC ${SDL_INCLUDE_DIR})

