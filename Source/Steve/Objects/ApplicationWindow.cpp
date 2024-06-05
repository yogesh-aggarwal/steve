#include "ApplicationWindow.hpp"

ApplicationWindow::ApplicationWindow(Callbacks callbacks)
    : m_Window(nullptr), m_IsRunning(false), m_Callbacks(callbacks)
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

   m_Window = glfwCreateWindow(800, 600, "Steve", nullptr, nullptr);
   if (!m_Window)
   {
      Terminate();
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_CREATION_FAILED,
                           "Failed to create application window" }) };
   }

   glfwMakeContextCurrent(m_Window);
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
