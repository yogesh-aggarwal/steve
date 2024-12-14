#include "styled_node.hpp"

/* ------------------------------------------------------------------------------------------------------- */

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

ui::StyledNode::StyledNode(const Node &node) : Node(node) {}

/* ------------------------------------------------------------------------------------------------------- */

ui::StyledNode
ui::StyledNode::FromNode(const Node &node) {
   return StyledNode(node);
}

/* ------------------------------------------------------------------------------------------------------- */

ui::StyledNode
ui::StyledNode::WithStyles(const Styles &styles) {
   Properties properties {};
   properties.styles = styles;

   return WithProperties(std::move(properties));
}

/* ------------------------------------------------------------------------------------------------------- */

void
ui::StyledNode::UpdateStyles(const Styles &styles) {
   m_Properties.styles = std::move(styles);
}

/* ------------------------------------------------------------------------------------------------------- */
