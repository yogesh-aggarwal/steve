#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <steve/core/pch>

namespace steve {
   class ApplicationWindow {
   public:
      class LifeCycle {
      public:
         LifeCycle() = default;

         virtual void
         on_init() {}

         virtual void
         on_render() {}

         virtual void
         on_terminate() {}

         virtual void
         on_key(int key) {}
      };

      struct Configuration {
         std::string Title;
         uint32_t    Width;
         uint32_t    Height;

         LifeCycle *LifeCyclePtr;

         bool IsVSync;
      };

      struct State : Configuration {
         GLFWwindow *Window;
         bool        IsRunning;
      };

   public:
      static VoidResult
      initialize(Configuration config);

      static VoidResult
      run();

      static bool
      is_running();

      static void
      terminate();

      static int
      get_width();

      static int
      get_height();

      static void
      set_vsync(bool enabled);

      static void
      refresh_vsync_enable_state();

      static Pair<float, float>
      get_display_dimensions();

   private:
      static void
      handle_inputs();
   };
}
