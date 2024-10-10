#include "config.h"

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

const Perspective perspective = {
    .fov = 45.0f,
    .aspect = static_cast<float>(window.window_width) / window.window_height,
    .z_near = 1.0f,
    .z_far = 100.0f};

} // namespace cg

