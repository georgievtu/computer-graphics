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

};

struct Camera
{

};

} // namespace cg

#endif

