#pragma once

#include <steve/core/pch>

#include <steve/lib/application/window.hpp>

#include <steve/lib/graphics/draw.hpp>
#include <steve/lib/graphics/shaders.hpp>
#include <steve/lib/graphics/renderer/renderer.hpp>
#include <steve/lib/graphics/renderer/vertex.hpp>
#include <steve/lib/graphics/renderer/backend/backend.hpp>
#include <steve/lib/graphics/renderer/context/graphics.hpp>
#include <steve/lib/graphics/renderer/context/opengl.hpp>
#include <steve/lib/graphics/renderer/context/vulkan.hpp>

/* ------------------------------------------------------------------------------------------------------- */

inline void
hello_steve() {
   std::cout << "Hello, from Steve!" << std::endl;
}

/* ------------------------------------------------------------------------------------------------------- */
