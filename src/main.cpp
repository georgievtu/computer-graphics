#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "config.h"

#include <array>
#include <fstream>
#include <iostream>
#include <optional>

constexpr auto clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 0.90f);

// TODO
/*
 * Forward declarations.
 */
// static void set_pvm(unsigned int program, glm::mat4 pvm);

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
        default:
            break;
    }
}

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

    /*
     * Set event callbacks.
     */
    glfwSetKeyCallback(window, key_callback);

    /*
     * Load OpenGL with GLAD.
     * Crashes if GL functions are called without this.
     */
    gladLoadGL();

    return window;
}

static void init_ImGui(GLFWwindow* window)
{
    /*
     * ImGui context.
     */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    /*
     * ImGui style.
     */
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(cg::version.glsl_version);
}

static void reset_viewport(GLFWwindow* window)
{
    int display_w = 0;
    int display_h = 0;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
}

static void clear(void)
{
    glClearColor(clear_color.x * clear_color.w,
                 clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void render_ImGui(void)
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

static void display_ImGui(void)
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static void cleanup_ImGui(void)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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

// TODO
static void recalculate_pvm()
{
    glm::mat4 projection = glm::perspective(cg::perspective.fov,
                                            cg::perspective.aspect,
                                            cg::perspective.z_near,
                                            cg::perspective.z_far);
}

// TODO
static void set_pvm(unsigned int program, glm::mat4 pvm)
{
    unsigned int u_pvm = glGetUniformLocation(program, "u_pvm");
    glUniformMatrix4fv(u_pvm, 1, GL_TRUE, glm::value_ptr(pvm));
}

static void init(void)
{
    /*
     * Enable z-buffer.
     */
    glEnable(GL_DEPTH_TEST);

    std::array vertices
    {
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,

         0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,

        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
         0.5f,-0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,

         0.5f,-0.5f,-0.5f,
         0.5f, 0.5f, 0.5f,
         0.5f,-0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
         0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,

         0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
         0.5f,-0.5f, 0.5f
    };

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

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

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

    glUseProgram(program);

    glm::mat4 projection = glm::perspective(cg::perspective.fov,
                                            cg::perspective.aspect,
                                            cg::perspective.z_near,
                                            cg::perspective.z_far);

    glm::mat4 view = glm::lookAt(cg::camera.eye,
                                 cg::camera.center,
                                 cg::camera.up);

    /*
     * Model.
     * Order of operations is important.
     */
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

    /*
     * Set PVM matrix.
     */
    glm::mat4 pvm = projection * view * model;
    unsigned int u_pvm = glGetUniformLocation(program, "u_pvm");
    glUniformMatrix4fv(u_pvm, 1, GL_TRUE, glm::value_ptr(pvm));
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

    init_ImGui(window);
    init();

    /*
     * Main loop.
     * Runs every frame.
     */
    while (glfwWindowShouldClose(window) == 0)
    {
        glfwPollEvents();

        render_ImGui();

        reset_viewport(window);

        clear();

        render();

        display_ImGui();

        glfwSwapBuffers(window);
    }

    /*
     * Cleanup.
     */
    cleanup_ImGui();
    cleanup_window(window);
}

int main(void)
{
    /*
     * Keep main function brief.
     */
    run();
}

