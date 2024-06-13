#include "ApplicationWindow.hpp"

#include <iostream>

ApplicationWindow::State s_ApplicationWindowState;

Result<bool>
ApplicationWindow::Initialize(Configuration config)
{
   /* Initialize state */
   {
      s_ApplicationWindowState.Title  = config.Title;
      s_ApplicationWindowState.Width  = config.Width;
      s_ApplicationWindowState.Height = config.Height;

      s_ApplicationWindowState.LifeCyclePtr = config.LifeCyclePtr;

      s_ApplicationWindowState.IsVSync = config.IsVSync;

      s_ApplicationWindowState.IsRunning = false;
      s_ApplicationWindowState.Window    = nullptr;

      if (!s_ApplicationWindowState.LifeCyclePtr)
      {
         return { false,
                  new Error({ STEVE_APPLICATION_WINDOW_LIFECYCLE_NOT_PROVIDED,
                              "Application window lifecycle not provided" }) };
      }
   }

   /* Initialize GLFW and OpenGL */
   {
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // MacOS only
#endif
   }

   s_ApplicationWindowState.Window =
       glfwCreateWindow(s_ApplicationWindowState.Width,
                        s_ApplicationWindowState.Height,
                        s_ApplicationWindowState.Title.c_str(),
                        nullptr,
                        nullptr);
   if (!s_ApplicationWindowState.Window)
   {
      Terminate();
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_CREATION_FAILED,
                           "Failed to create application window" }) };
   }

   glfwSwapInterval(s_ApplicationWindowState.IsVSync);
   glfwMakeContextCurrent(s_ApplicationWindowState.Window);
   glfwSetFramebufferSizeCallback(
       s_ApplicationWindowState.Window,
       [](GLFWwindow *window, int width, int height) {
          glViewport(0, 0, width, height);

          s_ApplicationWindowState.Width  = width;
          s_ApplicationWindowState.Height = height;

          s_ApplicationWindowState.LifeCyclePtr->OnRender();
       });
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      Terminate();
      return { false,
               new Error(
                   { STEVE_APPLICATION_WINDOW_GLAD_OPENGL_INITIALIZATION_FAILED,
                     "Failed to initialize GLAD in application window" }) };
   }

   s_ApplicationWindowState.LifeCyclePtr->OnInit();

   return true;
}

Result<bool>
ApplicationWindow::Run()
{
   if (!s_ApplicationWindowState.Window)
   {
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_NOT_INITIALIZED,
                           "Application window not initialized" }) };
   }
   if (s_ApplicationWindowState.IsRunning)
   {
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_ALREADY_RUNNING,
                           "Application window already running" }) };
   }

   s_ApplicationWindowState.IsRunning = true;

   while (!glfwWindowShouldClose(s_ApplicationWindowState.Window))
   {
      HandleInputs();

      // Render commands here
      int glError = glGetError();
      if (glError) std::cout << glError << std::endl;

      s_ApplicationWindowState.LifeCyclePtr->OnRender();

      glfwSwapBuffers(s_ApplicationWindowState.Window);
      glfwPollEvents();
   }

   s_ApplicationWindowState.IsRunning = false;

   return true;
}

bool
ApplicationWindow::IsRunning()
{
   return s_ApplicationWindowState.IsRunning;
}

void
ApplicationWindow::Terminate()
{
   if (!s_ApplicationWindowState.Window) return;

   s_ApplicationWindowState.LifeCyclePtr->OnTerminate();

   s_ApplicationWindowState.Window       = nullptr;
   s_ApplicationWindowState.IsRunning    = false;
   s_ApplicationWindowState.LifeCyclePtr = nullptr;

   glfwTerminate();

   glfwSetWindowShouldClose(s_ApplicationWindowState.Window, true);
}

int
ApplicationWindow::GetWidth()
{
   return s_ApplicationWindowState.Width;
}

int
ApplicationWindow::GetHeight()
{
   return s_ApplicationWindowState.Height;
}

void
ApplicationWindow::SetVSync(bool enabled)
{
   s_ApplicationWindowState.IsVSync = enabled;
   glfwSwapInterval(s_ApplicationWindowState.IsVSync);
}

void
ApplicationWindow::RefreshVSyncEnableState()
{
   glfwSwapInterval(s_ApplicationWindowState.IsVSync);
}

void
ApplicationWindow::HandleInputs()
{
   if (s_ApplicationWindowState.IsRunning) return;

   s_ApplicationWindowState.LifeCyclePtr->OnKey(
       glfwGetKey(s_ApplicationWindowState.Window, GLFW_KEY_ESCAPE));

   if (glfwGetKey(s_ApplicationWindowState.Window, GLFW_KEY_ESCAPE) ==
       GLFW_PRESS)
   {
      glfwSetWindowShouldClose(s_ApplicationWindowState.Window, true);
      return;
   }
}
