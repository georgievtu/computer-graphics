#ifndef CG_STRUCTS
#define CG_STRUCTS

#include "glm/ext.hpp"

namespace cg
{

struct Version
{
    const int gl_major;
    const int gl_minor;
    const char* glsl_version;
};
extern const Version version;

struct Window
{
    const int window_width;
    const int window_height;
    const char* window_title;
};
extern const Window window;

struct Perspective
{
    float fov;
    float aspect;
    float z_near;
    float z_far;
};
extern Perspective perspective;

struct Camera
{
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
};
extern Camera camera;

} // namespace cg

#endif

