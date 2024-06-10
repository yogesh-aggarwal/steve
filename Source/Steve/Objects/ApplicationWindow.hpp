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
      LifeCycle()          = default;
      virtual ~LifeCycle() = default;

      virtual void
      OnInit() = 0;

      virtual void
      OnRender() = 0;

      virtual void
      OnTerminate() = 0;

      virtual void
      OnKey(int key) = 0;
   };

   struct Configuration
   {
      std::string Title;
      uint32_t    Width;
      uint32_t    Height;

      LifeCycle *LifeCyclePtr;
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

private:
   static void
   HandleInputs();
};
