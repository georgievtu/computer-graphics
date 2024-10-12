#ifndef CG_UI
#define CG_UI

#include "GLFW/glfw3.h"

namespace cg
{

void init_ImGui(GLFWwindow* window);
void render_ImGui(void);
void display_ImGui(void);
void cleanup_ImGui(void);

} // namespace cg

#endif

