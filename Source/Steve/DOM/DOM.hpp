#pragma once

#include <Steve/Graphics/Renderer/Core/Vertex.hpp>

#include "Node/StyledNode.hpp"

namespace Steve::DOM
{
   std::vector<std::array<Vertex, 4>>
   TranslateToQuads(const StyledNode &node);
}
