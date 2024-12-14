#pragma once

#include "state.hpp"
#include "lifecycle.hpp"

namespace steve::application {
   class Window {
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
