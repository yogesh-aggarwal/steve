#include "Draw.hpp"

std::array<Vertex, 4>
Steve::Draw::DrawQuad(float            x,
                      float            y,
                      float            width,
                      float            height,
                      const glm::vec4 &color)
{
   Vertex v1, v2, v3, v4;

   v1.position = { x, y, 0.0f };
   v1.color    = color;

   v2.position = { x + width, y, 0.0f };
   v2.color    = color;

   v3.position = { x + width, y + height, 0.0f };
   v3.color    = color;

   v4.position = { x, y + height, 0.0f };
   v4.color    = color;

   return { v1, v2, v3, v4 };
}
