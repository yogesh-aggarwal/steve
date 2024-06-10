#pragma once

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Steve/Core/Result.tcc>

class ApplicationWindow
{
public:
   class LifeCycle
   {
   public:
      LifeCycle() = default;

      virtual void
      OnInit()
      {
      }

      virtual void
      OnRender()
      {
      }

      virtual void
      OnTerminate()
      {
      }

      virtual void
      OnKey(int key)
      {
      }
   };

   struct Configuration
   {
      std::string Title;
      uint32_t    Width;
      uint32_t    Height;

      LifeCycle *LifeCyclePtr;

      bool IsVSync;
   };

   struct State : Configuration
   {
      GLFWwindow *Window;
      bool        IsRunning;
   };

public:
   static Result<bool>
   Initialize(Configuration config);

   static Result<bool>
   Run();

   static bool
   IsRunning();

   static void
   Terminate();

   static int
   GetWidth();

   static int
   GetHeight();

   static void
   SetVSync(bool enabled);

   static void
   RefreshVSyncEnableState();

private:
   static void
   HandleInputs();
};
