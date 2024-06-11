#include "ApplicationWindow.hpp"

#include <iostream>

ApplicationWindow::State s_State;

Result<bool>
ApplicationWindow::Initialize(Configuration config)
{
   /* Initialize state */
   {
      s_State.Title  = config.Title;
      s_State.Width  = config.Width;
      s_State.Height = config.Height;

      s_State.LifeCyclePtr = config.LifeCyclePtr;

      s_State.IsVSync = config.IsVSync;

      s_State.IsRunning = false;
      s_State.Window    = nullptr;

      if (!s_State.LifeCyclePtr)
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
#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // MacOS only
#endif
   }

   s_State.Window = glfwCreateWindow(s_State.Width,
                                     s_State.Height,
                                     s_State.Title.c_str(),
                                     nullptr,
                                     nullptr);
   if (!s_State.Window)
   {
      Terminate();
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_CREATION_FAILED,
                           "Failed to create application window" }) };
   }

   glfwSwapInterval(s_State.IsVSync);
   glfwMakeContextCurrent(s_State.Window);
   glfwSetFramebufferSizeCallback(
       s_State.Window,
       [](GLFWwindow *window, int width, int height) {
          glViewport(0, 0, width, height);

          s_State.Width  = width;
          s_State.Height = height;

          s_State.LifeCyclePtr->OnRender();
       });
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      Terminate();
      return { false,
               new Error(
                   { STEVE_APPLICATION_WINDOW_GLAD_OPENGL_INITIALIZATION_FAILED,
                     "Failed to initialize GLAD in application window" }) };
   }

   s_State.LifeCyclePtr->OnInit();

   return true;
}

Result<bool>
ApplicationWindow::Run()
{
   if (!s_State.Window)
   {
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_NOT_INITIALIZED,
                           "Application window not initialized" }) };
   }
   if (s_State.IsRunning)
   {
      return { false,
               new Error({ STEVE_APPLICATION_WINDOW_ALREADY_RUNNING,
                           "Application window already running" }) };
   }

   s_State.IsRunning = true;

   while (!glfwWindowShouldClose(s_State.Window))
   {
      HandleInputs();

      // Render commands here
      int glError = glGetError();
      if (glError) std::cout << glError << std::endl;

      s_State.LifeCyclePtr->OnRender();

      glfwSwapBuffers(s_State.Window);
      glfwPollEvents();
   }

   s_State.IsRunning = false;

   return true;
}

bool
ApplicationWindow::IsRunning()
{
   return s_State.IsRunning;
}

void
ApplicationWindow::Terminate()
{
   if (!s_State.Window) return;

   s_State.LifeCyclePtr->OnTerminate();

   s_State.Window       = nullptr;
   s_State.IsRunning    = false;
   s_State.LifeCyclePtr = nullptr;

   glfwTerminate();

   glfwSetWindowShouldClose(s_State.Window, true);
}

int
ApplicationWindow::GetWidth()
{
   return s_State.Width;
}

int
ApplicationWindow::GetHeight()
{
   return s_State.Height;
}

void
ApplicationWindow::SetVSync(bool enabled)
{
   s_State.IsVSync = enabled;
   glfwSwapInterval(s_State.IsVSync);
}

void
ApplicationWindow::RefreshVSyncEnableState()
{
   glfwSwapInterval(s_State.IsVSync);
}

void
ApplicationWindow::HandleInputs()
{
   if (s_State.IsRunning) return;

   s_State.LifeCyclePtr->OnKey(glfwGetKey(s_State.Window, GLFW_KEY_ESCAPE));

   if (glfwGetKey(s_State.Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(s_State.Window, true);
      return;
   }
}
