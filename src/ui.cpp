#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ui.h"
#include "structs.h"

namespace cg
{

void init_ImGui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(cg::version.glsl_version);
}

void render_ImGui(void)
{
    bool show_demo_window = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (show_demo_window == true)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    ImGui::Render();
}

void display_ImGui(void)
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void cleanup_ImGui(void)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

} // namespace cg

