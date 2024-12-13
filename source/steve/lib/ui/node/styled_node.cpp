#include "styled_node.hpp"

steve::ui::StyledNode::StyledNode(const Node &node) : Node(node) {}

steve::ui::StyledNode
steve::ui::StyledNode::FromNode(const Node &node) {
   return StyledNode(node);
}

steve::ui::StyledNode
steve::ui::StyledNode::WithStyles(const Styles &styles) {
   Properties properties {};
   properties.styles = styles;

   return WithProperties(std::move(properties));
}

void
steve::ui::StyledNode::UpdateStyles(const Styles &styles) {
   m_Properties.styles = std::move(styles);
}
