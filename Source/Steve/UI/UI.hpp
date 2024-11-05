#pragma once

#include <Steve/Graphics/Renderer/Core/Vertex.hpp>

#include "Node/Node.hpp"

namespace Steve::UI
{
   std::vector<std::array<Vertex, 4>>
   TranslateToQuads(Ref<Node> node);
}
