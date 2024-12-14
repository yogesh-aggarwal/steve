#include "ui.hpp"

#include <steve/lib/graphics/draw.hpp>

/* ------------------------------------------------------------------------------------------------------- */

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

const auto DEFAULT_QUADS = {
   Draw::DrawQuad(4.0f, 4.0f, 200.0f, 32.0f, glm::vec4(0.23f, 0.23f, 0.23f, 1.0f)),
};

/* ------------------------------------------------------------------------------------------------------- */

std::vector<std::array<Vertex, 4>>
ui::TranslateToQuads(Ref<Node> node) {
   std::vector<std::array<Vertex, 4>> quads;

   auto vertices = Draw::DrawQuad(node->GetPaintBounds().GetXOffset(),
                                  node->GetPaintBounds().GetYOffset(),
                                  node->GetPaintBounds().GetCalculatedMaxWidth(),
                                  node->GetProperties().styles.GetHeight().GetValue(),
                                  node->GetProperties().styles.GetBackgroundColor().GetColor());
   quads.push_back(vertices);

   for (auto child : node->GetChildren()) {
      auto childQuads = TranslateToQuads(child);
      quads.insert(quads.end(), childQuads.begin(), childQuads.end());
   }

   // system("clear");

   // for (auto &quad : quads)
   // {
   //    for (auto &vertex : quad)
   //    {
   //       vertex.Print();
   //    }

   //    std::cout << std::endl;
   // }

   return quads;
}

/* ------------------------------------------------------------------------------------------------------- */
