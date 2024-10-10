#ifndef CG_CONFIG
#define CG_CONFIG

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

struct Camera
{

};

} // namespace cg

#endif

