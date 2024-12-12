#pragma once

#include <array>
#include <glm/glm.hpp>

#include <steve/lib/graphics/renderer/vertex.hpp>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   /**
    * @brief Namespace for drawing functions which only operates in maths &
    * don't use any graphics context & no draw calls are made. Read details for
    * more information on the same.
    * @details Functions in this namespace has nothing to do with any of the
    * graphics contexts and for that very reason they don't make any of the draw
    * calls but rather they are used to generate vertices for drawing. They use
    * maths functions mainly provided by (`glm` math library) and algorithms to
    * generate to achieve the desired result.
    */
   namespace Draw {
      /**
       * @brief Draw a quad with the given parameters.
       * @param x The x-coordinate of the quad.
       * @param y The y-coordinate of the quad.
       * @param width The width of the quad.
       * @param height The height of the quad.
       * @param color The color of the quad.
       *
       * @return An `std::array` of 4 vertices which can be used to draw the
       * quad.
       * @details This function generates vertices for a quad with the given
       * parameters. The vertices are generated in the following order:
       *
       * 0. Top-left vertex.
       * 1. Top-right vertex.
       * 2. Bottom-right vertex.
       * 3. Bottom-left vertex.
       *
       * The vertices are generated in the counter-clockwise order.
       */
      std::array<Vertex, 4>
      DrawQuad(float x, float y, float width, float height, const glm::vec4 &color);
   }
}

/* ------------------------------------------------------------------------------------------------------- */
