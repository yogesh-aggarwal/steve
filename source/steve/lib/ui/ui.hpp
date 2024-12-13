#pragma once

#include <steve/lib/graphics/renderer/vertex.hpp>

#include "node/node.hpp"

namespace steve::ui {
   std::vector<std::array<Vertex, 4>>
   TranslateToQuads(Ref<Node> node);
}
