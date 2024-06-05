#include "Draw.hpp"

std::array<Vertex, 4>
Steve::Draw::DrawQuad(float            x,
                      float            y,
                      float            width,
                      float            height,
                      const glm::vec4 &color)
{
   // clang-format off
   Vertex v1 = {x,         y,          0.0f, color.r, color.g, color.b, color.a};
   Vertex v2 = {x + width, y,          0.0f, color.r, color.g, color.b, color.a};
   Vertex v3 = {x + width, y + height, 0.0f, color.r, color.g, color.b, color.a};
   Vertex v4 = {x,         y + height, 0.0f, color.r, color.g, color.b, color.a};
   // clang-format on

   return { v1, v2, v3, v4 };
}
