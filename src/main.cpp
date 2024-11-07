#include "glad/glad.h"

#include "ui.h"
#include "structs.h"
#include "vendor/stb_image.h"

#include <array>
#include <fstream>
#include <iostream>
#include <optional>

/*
 * Constants.
 */
constexpr auto clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 0.90f);

/*
 * Globals. For convenience.
 */
static unsigned int g_program = 0;
static glm::mat4 g_model = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                     0.0f, 1.0f, 0.0f, 0.0f,
                                     0.0f, 0.0f, 1.0f, 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f);

/*
 * Forward declarations.
 */
static void set_pvm(unsigned int program, glm::mat4 pvm);
static glm::mat4 recalculate_pvm();

static unsigned int gl_print_error(void)
{
    unsigned int error = glGetError();
    if (error == 0)
        std::cout << "No GL errors." << std::endl;
    else
        std::cerr << "GL Error: " << error << std::endl;
    return error;
}

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << error << " " << description << std::endl;
}

static void key_callback(GLFWwindow* window,
                         int key,
                         int scancode,
                         int action,
                         int mode)
{
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_A:
            g_model = glm::rotate(g_model,
                                  glm::radians<float>(5.0f),
                                  glm::vec3(0.0f, 1.0f, 0.0f));
            set_pvm(g_program, recalculate_pvm());
            break;
        case GLFW_KEY_D:
            break;
        case GLFW_KEY_W:
            break;
        case GLFW_KEY_S:
            break;
        default:
            break;
    }
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0)
        return;

    glViewport(0, 0, width, height);
    cg::perspective.aspect = static_cast<float>(width) / height;
    set_pvm(g_program, recalculate_pvm());
};

GLFWwindow* init_window(void)
{
    glfwSetErrorCallback(glfw_error_callback);

    if (glfwInit() == GLFW_FALSE)
        return nullptr;

    /*
     * Required for Apple.
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, cg::version.gl_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, cg::version.gl_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /*
     * Multisampling.
     */
    glfwWindowHint(GLFW_SAMPLES, 4);

    /*
     * Create the graphics context and make it current.
     */
    GLFWwindow* const window = glfwCreateWindow(cg::window.window_width,
                                                cg::window.window_height,
                                                cg::window.window_title,
                                                nullptr,
                                                nullptr);

    if (window == nullptr)
        return nullptr;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    /*
     * Set event callbacks.
     */
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, size_callback);

    /*
     * Load OpenGL with GLAD.
     * Crashes if GL functions are called without this.
     */
    gladLoadGL();

    return window;
}

static void clear(void)
{
    glClearColor(clear_color.x * clear_color.w,
                 clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void cleanup_window(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

static std::optional<std::string> read_shader(const std::string& path)
{
    std::string result;

    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (in.good() == false)
        return std::nullopt;

    in.seekg(0, std::ios::end);
    size_t size = in.tellg();

    if (size == -1)
        return std::nullopt;

    result.resize(size);
    in.seekg(0, std::ios::beg);
    in.read(&result[0], size);

    return result;
}

/*
 * Copy the shader source string here just in case.
 * c_str will point to garbage if a string reference goes out of scope.
 */
static unsigned int compile_shader(const std::string shader_source,
                                   unsigned int type)
{
    unsigned int shader = glCreateShader(type);

    const char* c_str = shader_source.c_str();
    glShaderSource(shader, 1, &c_str, nullptr);

    glCompileShader(shader);

    /*
     * Compile error checking.
     */
    int is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == 0)
    {
        std::string log;
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        log.resize(length);
        glGetShaderInfoLog(shader, length, nullptr, &log[0]);

        std::string type_s = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
        std::cerr << "Failed to compile " << type_s << " shader." << std::endl;
        std::cerr << log << std::endl;

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static unsigned int create_shader(const std::string& vertex_source,
                                  const std::string& fragment_source)
{
    unsigned int program = glCreateProgram();
    unsigned int vertex_shader = compile_shader(vertex_source, GL_VERTEX_SHADER);
    if (vertex_shader == 0)
        return 0;
    unsigned int fragment_shader = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
    if (fragment_shader == 0)
        return 0;

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    return program;
}

static glm::mat4 recalculate_pvm()
{
    glm::mat4 projection = glm::perspective(cg::perspective.fov,
                                            cg::perspective.aspect,
                                            cg::perspective.z_near,
                                            cg::perspective.z_far);

    glm::mat4 view = glm::lookAt(cg::camera.eye,
                                 cg::camera.center,
                                 cg::camera.up);

    return projection * view * g_model;
}

static void set_pvm(unsigned int program, glm::mat4 pvm)
{
    unsigned int u_pvm = glGetUniformLocation(program, "u_pvm");
    glUniformMatrix4fv(u_pvm, 1, GL_TRUE, glm::value_ptr(pvm));
}

static void init(void)
{
    /*
     * Enable z-buffer and multisampling.
     */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    /*
     * Cube.
     */
    std::array<float, 288> vertices =
    {
    /* Position            Normal                Texture Coords */
    /* Front face */
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,

     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

    /* Back face */
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,

     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

    /* Left face */
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

    /* Right face */
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

    /* Top face */
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,

     0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,

    /* Bottom face */
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,

     0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f
    };

    /*
     * Triangle.
     */
    std::array triangle
    {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    /*
     * Load draw data to the GPU memory.
     */
    unsigned int vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    /*
     * Specify the format of the data.
     */
    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /*
     * Position attribute.
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*
     * Normal attribute.
     */
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /*
     * Texture coordinate attribute.
     */
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    std::cout << "Data init check:" << std::endl;
    if (gl_print_error() != 0)
        return;

    /*
     * Setup shaders.
     */
    const auto vertex_source = read_shader("resources/shaders/vertex.glsl");
    const auto fragment_source = read_shader("resources/shaders/fragment.glsl");
    if (vertex_source.has_value() == false ||
        fragment_source.has_value() == false)
    {
        std::cerr << "Failed to read shaders." << std::endl;
        return;
    }

    unsigned int program = create_shader(vertex_source.value(),
                                         fragment_source.value());

    if (program == 0)
    {
        std::cerr << "Failed to compile shaders." << std::endl;
        return;
    }

    int texture_width = 0;
    int texture_height= 0;
    int texture_channels = 0;

    unsigned char* texture_data = stbi_load("resources/textures/logo.png",
                                            &texture_width,
                                            &texture_height,
                                            &texture_channels,
                                            0);

    stbi_image_free(texture_data);

    glUseProgram(program);
    g_program = program;

    /*
     * Set PVM matrix.
     */
    set_pvm(program, recalculate_pvm());
}

static void render(void)
{
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

static void run(void)
{
    GLFWwindow* window = init_window();
    if (window == nullptr)
        std::exit(1);

    cg::init_ImGui(window);
    init();

    /*
     * Main loop.
     * Runs every frame.
     */
    while (glfwWindowShouldClose(window) == 0)
    {
        glfwPollEvents();

        cg::render_ImGui();

        clear();

        render();

        cg::display_ImGui();

        glfwSwapBuffers(window);
    }

    /*
     * Cleanup.
     */
    cg::cleanup_ImGui();
    cleanup_window(window);
}

int main(void)
{
    /*
     * Keep main function brief.
     */
    run();
}

