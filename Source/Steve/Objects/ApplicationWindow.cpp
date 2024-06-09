#include "ApplicationWindow.hpp"

#include <iostream>

ApplicationWindow::ApplicationWindow(std::string title,
                                     uint32_t    width,
                                     uint32_t    height,
                                     Callbacks   callbacks)
    : m_Window(nullptr), m_IsRunning(false), m_Title(std::move(title)),
      m_Width(width), m_Height(height), m_Callbacks(callbacks)
{
}

Result<bool>
ApplicationWindow::Initialize()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // MacOS only
#endif

   m_Window =
       glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
   if (!m_Window)
   {
      Terminate();
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_CREATION_FAILED,
                           "Failed to create application window" }) };
   }

   glfwSwapInterval(1);   // Enable vsync
   glfwMakeContextCurrent(m_Window);
   glfwSetFramebufferSizeCallback(
       m_Window,
       [](GLFWwindow *window, int width, int height) {
          glViewport(0, 0, width, height);
       });
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      Terminate();
      return { false,
               new Error(
                   { STEVE_APPLICATION_WINDOW_GLAD_OPENGL_INITIALIZATION_FAILED,
                     "Failed to initialize GLAD in application window" }) };
   }

   if (m_Callbacks.OnInit) m_Callbacks.OnInit();

   return true;
}

Result<bool>
ApplicationWindow::Run()
{
   if (!m_Window)
   {
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_NOT_INITIALIZED,
                           "Application window not initialized" }) };
   }
   if (m_IsRunning)
   {
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_ALREADY_RUNNING,
                           "Application window already running" }) };
   }

   m_IsRunning = true;

   while (!glfwWindowShouldClose(m_Window))
   {
      HandleInputs();

      // Render commands here
      int glError = glGetError();
      if (glError) std::cout << glError << std::endl;

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      if (m_Callbacks.OnRender) m_Callbacks.OnRender();

      glfwSwapBuffers(m_Window);
      glfwPollEvents();
   }

   m_IsRunning = false;

   return true;
}

void
ApplicationWindow::SetCallbacks(Callbacks callbacks)
{
   m_Callbacks = callbacks;
}

void
ApplicationWindow::Terminate()
{
   if (m_Callbacks.OnTerminate) m_Callbacks.OnTerminate();

   glfwTerminate();

   m_Window    = nullptr;
   m_IsRunning = false;
   m_Callbacks = {};

   glfwSetWindowShouldClose(m_Window, true);
}

void
ApplicationWindow::HandleInputs()
{
   if (m_IsRunning) return;

   if (m_Callbacks.OnKey)
   {
      m_Callbacks.OnKey(glfwGetKey(m_Window, GLFW_KEY_ESCAPE));
   }

   if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(m_Window, true);
      return;
   }
}
