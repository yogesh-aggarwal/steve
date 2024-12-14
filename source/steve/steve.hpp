#pragma once

#include <steve/lib/application/lifecycle.hpp>
#include <steve/lib/application/state.hpp>
#include <steve/lib/application/window.hpp>

#include <steve/lib/graphics/draw.hpp>
#include <steve/lib/graphics/shaders.hpp>
#include <steve/lib/graphics/renderer/renderer.hpp>
#include <steve/lib/graphics/renderer/vertex.hpp>
#include <steve/lib/graphics/renderer/backend/backend.hpp>
#include <steve/lib/graphics/renderer/context/graphics.hpp>
#include <steve/lib/graphics/renderer/context/opengl.hpp>
#include <steve/lib/graphics/renderer/context/vulkan.hpp>

#include <steve/lib/ui/container/container.hpp>
#include <steve/lib/ui/node/node.hpp>
#include <steve/lib/ui/node/styles/bound.hpp>
#include <steve/lib/ui/node/styles/color.hpp>
#include <steve/lib/ui/node/styles/edge_inset.tcc>
#include <steve/lib/ui/node/styles/height.hpp>
#include <steve/lib/ui/node/styles/margin.hpp>
#include <steve/lib/ui/node/styles/padding.hpp>
#include <steve/lib/ui/node/styles/styles.hpp>
#include <steve/lib/ui/node/styles/width.hpp>
#include <steve/lib/ui/node/styled_node.hpp>
#include <steve/lib/ui/ui.hpp>

/* ------------------------------------------------------------------------------------------------------- */

inline void
hello_steve() {
   std::cout << "Hello, from Steve!" << std::endl;
}

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   inline void
   run(application::Configuration initial_config) {
      application::Window::initialize(initial_config)   //
          .except("Failed to initialize application.")
          .panic_if_error();

      /* Run the mainloop */
      application::Window::run()   //
          .except("Failed to run application.")
          .panic_if_error();

      /* Terminate application */
      application::Window::terminate();
   }
}

/* ------------------------------------------------------------------------------------------------------- */
