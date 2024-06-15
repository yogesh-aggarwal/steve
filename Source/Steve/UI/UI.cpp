#include "UI.hpp"

#include <Steve/Graphics/Draw/Draw.hpp>

const auto DEFAULT_QUADS = {
   Steve::Draw::DrawQuad(4.0f,
                         4.0f,
                         32.0f,
                         32.0f,
                         glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)),
};

std::vector<std::array<Vertex, 4>>
Steve::UI::TranslateToQuads(StyledNode node)
{
   node.CalculateBounds();

   return DEFAULT_QUADS;
}
