#include "UI.hpp"

#include <Steve/Graphics/Draw/Draw.hpp>

const auto DEFAULT_QUADS = {
   Steve::Draw::DrawQuad(4.0f,
                         4.0f,
                         200.0f,
                         32.0f,
                         glm::vec4(0.23f, 0.23f, 0.23f, 1.0f)),
};

std::vector<std::array<Vertex, 4>>
Steve::UI::TranslateToQuads(StyledNode node)
{
   node.CalculateBounds();

   std::vector<std::array<Vertex, 4>> quads;

   auto vertices = Steve::Draw::DrawQuad(
       0.0f,
       0.0f,
       node.GetPaintBounds().GetHorizontalBound().GetMin(),
       node.GetPaintBounds().GetVerticalBound().GetMin(),
       glm::vec4(0.23f, 0.23f, 0.23f, 1.0f));
   quads.push_back(vertices);

   for (const auto &child : node.GetChildren())
   {
      auto childQuads = TranslateToQuads(*child);
      quads.insert(quads.end(), childQuads.begin(), childQuads.end());
   }

   return quads;

   return DEFAULT_QUADS;
}
