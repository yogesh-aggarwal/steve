#pragma once

#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Steve/Core/Result.tcc>

class ApplicationWindow
{
public:
   struct Callbacks
   {
      std::function<void()>    OnInit;
      std::function<void()>    OnRender;
      std::function<void()>    OnTerminate;
      std::function<void(int)> OnKey;
   };

private:
   GLFWwindow *m_Window;
   bool        m_IsRunning;
   Callbacks   m_Callbacks;

   std::function<void()> m_RenderCallback;

public:
   ApplicationWindow() = default;
   ApplicationWindow(Callbacks callbacks);
   ~ApplicationWindow() = default;

   Result<bool>
   Initialize();

   Result<bool>
   Run();

   inline bool
   IsRunning() const
   {
      return m_IsRunning;
   }

   void
   SetCallbacks(Callbacks callbacks);

   void
   Terminate();

private:
   void
   HandleInputs();
};
