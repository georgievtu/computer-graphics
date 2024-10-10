# Path to dependencies
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/dependencies/imgui)

# Add the library directly from local sources
add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_SOURCE_DIR}/../dependencies/glfw/include)

target_link_libraries(imgui PRIVATE glfw)

#----------------------------------------------------------------------
# Path to GLM directory
set(GLM_DIR ${CMAKE_SOURCE_DIR}/dependencies/glm)

# Add GLM to your project
add_subdirectory(${GLM_DIR})

# Optionally, if GLM uses header-only, just include it directly
target_include_directories(your_target PUBLIC ${GLM_DIR})

# Set compile definitions as before
target_compile_definitions(glm INTERFACE GLM_FORCE_SILENT_WARNINGS)

#----------------------------------------------------------------------

# Path to your local GLFW directory
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/dependencies/glfw)

# Add GLFW directly
add_subdirectory(${GLFW_DIR})

# Link GLFW to your target
target_link_libraries(your_target PRIVATE glfw)

#----------------------------------------------------------------------

# Path to your local GLAD directory
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/dependencies/glad)

# Add GLAD to your project
add_subdirectory(${GLAD_DIR})

# Set the correct definitions and options for GLAD
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=4.6" CACHE STRING "API type/version pairs")
set(GLAD_GENERATOR "c" CACHE STRING "Language for bindings")
set(GLAD_EXTENSIONS "GL_ARB_bindless_texture" CACHE STRING "Extensions for bindings")