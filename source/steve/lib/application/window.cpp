#include "window.hpp"
#include "lifecycle.hpp"

using namespace steve::application;

/* ------------------------------------------------------------------------------------------------------- */

State s_ApplicationWindowState;

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
Window::initialize(Configuration config) {
   /* Initialize state */
   {
      s_ApplicationWindowState.Title  = config.Title;
      s_ApplicationWindowState.Width  = config.Width;
      s_ApplicationWindowState.Height = config.Height;

      s_ApplicationWindowState.Lifecycle = config.Lifecycle;

      s_ApplicationWindowState.IsVSync = config.IsVSync;

      s_ApplicationWindowState.IsRunning = false;
      s_ApplicationWindowState.Window    = nullptr;
   }

   /* Initialize GLFW and OpenGL */
   {
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
      glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // MacOS only
#endif
   }

   s_ApplicationWindowState.Window = glfwCreateWindow(s_ApplicationWindowState.Width,
                                                      s_ApplicationWindowState.Height,
                                                      s_ApplicationWindowState.Title.c_str(),
                                                      nullptr,
                                                      nullptr);
   if (!s_ApplicationWindowState.Window) {
      terminate();
      return Error("Failed to create application window");
   }

   auto [displayWidth, displayHeight] = get_display_dimensions();
   glfwSetWindowPos(s_ApplicationWindowState.Window,
                    displayWidth / 2 - s_ApplicationWindowState.Width / 2,
                    displayHeight / 2 - s_ApplicationWindowState.Height / 2);

   glfwSwapInterval(s_ApplicationWindowState.IsVSync);
   glfwMakeContextCurrent(s_ApplicationWindowState.Window);
   glfwSetFramebufferSizeCallback(s_ApplicationWindowState.Window,
                                  [](GLFWwindow *window, int width, int height) {
                                     glViewport(0, 0, width, height);

                                     s_ApplicationWindowState.Width  = width;
                                     s_ApplicationWindowState.Height = height;

                                     s_ApplicationWindowState.Lifecycle->on_render();
                                  });
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      terminate();
      return Error("Failed to initialize GLAD in application window");
   }

   s_ApplicationWindowState.Lifecycle->on_init();

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

VoidResult
Window::run() {
   if (!s_ApplicationWindowState.Window) {
      return Error("Application window not initialized");
   }
   if (s_ApplicationWindowState.IsRunning) {
      return Error("Application window already running");
   }

   s_ApplicationWindowState.IsRunning = true;

   while (!glfwWindowShouldClose(s_ApplicationWindowState.Window)) {
      handle_inputs();

      if (!s_ApplicationWindowState.IsRunning)
         break;

      // Render commands here
      int glError = glGetError();
      if (glError)
         std::cout << glError << std::endl;

      s_ApplicationWindowState.Lifecycle->on_render();

      glfwSwapBuffers(s_ApplicationWindowState.Window);
      glfwPollEvents();
   }

   s_ApplicationWindowState.IsRunning = false;

   return Ok();
}

/* ------------------------------------------------------------------------------------------------------- */

bool
Window::is_running() {
   return s_ApplicationWindowState.IsRunning;
}

/* ------------------------------------------------------------------------------------------------------- */

void
Window::terminate() {
   if (!s_ApplicationWindowState.Window)
      return;

   s_ApplicationWindowState.Lifecycle->on_terminate();

   glfwDestroyWindow(s_ApplicationWindowState.Window);
   glfwTerminate();

   s_ApplicationWindowState.Window    = nullptr;
   s_ApplicationWindowState.IsRunning = false;
   s_ApplicationWindowState.Lifecycle = nullptr;
}

/* ------------------------------------------------------------------------------------------------------- */

int
Window::get_width() {
   return s_ApplicationWindowState.Width;
}

/* ------------------------------------------------------------------------------------------------------- */

int
Window::get_height() {
   return s_ApplicationWindowState.Height;
}

/* ------------------------------------------------------------------------------------------------------- */

void
Window::set_vsync(bool enabled) {
   s_ApplicationWindowState.IsVSync = enabled;
   glfwSwapInterval(s_ApplicationWindowState.IsVSync);
}

/* ------------------------------------------------------------------------------------------------------- */

void
Window::refresh_vsync_enable_state() {
   glfwSwapInterval(s_ApplicationWindowState.IsVSync);
}

/* ------------------------------------------------------------------------------------------------------- */

Pair<float, float>
Window::get_display_dimensions() {
   const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
   return { static_cast<float>(mode->width), static_cast<float>(mode->height) };
}

/* ------------------------------------------------------------------------------------------------------- */

void
Window::handle_inputs() {
   if (!s_ApplicationWindowState.IsRunning)
      return;

   s_ApplicationWindowState.Lifecycle->on_key(glfwGetKey(s_ApplicationWindowState.Window, GLFW_KEY_ESCAPE));

   if (glfwGetKey(s_ApplicationWindowState.Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      terminate();
      return;
   }
}

/* ------------------------------------------------------------------------------------------------------- */
