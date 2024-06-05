#pragma once

#include <array>
#include <glm/glm.hpp>

#include <Steve/Objects/Vertex.hpp>

namespace Steve
{
   namespace Draw
   {
      std::array<Vertex, 4>
      DrawQuad(float            x,
               float            y,
               float            width,
               float            height,
               const glm::vec4 &color);
   }
}
