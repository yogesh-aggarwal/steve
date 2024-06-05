#pragma once

#include <string>
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

   std::string m_Title;
   uint32_t    m_Width;
   uint32_t    m_Height;

   std::function<void()> m_RenderCallback;

public:
   ApplicationWindow() = default;
   ApplicationWindow(std::string title,
                     uint32_t    width,
                     uint32_t    height,
                     Callbacks   callbacks);
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
