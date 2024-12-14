#pragma once

#include "lifecycle.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve::application {
   struct Configuration {
      std::string Title;
      uint32_t    Width;
      uint32_t    Height;

      Ref<ILifecycle> Lifecycle;

      bool IsVSync;
   };

   struct State : Configuration {
      GLFWwindow *Window;
      bool        IsRunning;
   };
}

/* ------------------------------------------------------------------------------------------------------- */
