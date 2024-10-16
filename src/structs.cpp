#include "structs.h"

namespace cg
{

const Version version = {
    .gl_major = 4,
    .gl_minor = 6,
    .glsl_version = "#version 460"};

const Window window = {
    .window_width = 1280,
    .window_height = 720,
    .window_title = "Computer Graphics"};

/*
 * Projection.
 * FOV, Aspect, Z_NEAR, Z_FAR
 */
Perspective perspective = {
    .fov = 45.0f,
    .aspect = static_cast<float>(window.window_width) / window.window_height,
    .z_near = 1.0f,
    .z_far = 100.0f};

/*
 * View.
 * Eye not in the center so we are outside the object.
 * Center at 0.
 * Up = y direction.
 */
Camera camera = {
    .eye = glm::vec3(0.0f, 0.0f, 5.0f),
    .center = glm::vec3(0.0f),
    .up = glm::vec3(0.0f, 1.0f, 0.0f)};

} // namespace cg

