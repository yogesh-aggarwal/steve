#include "StyledNode.hpp"

Steve::UI::StyledNode::StyledNode(const Node &node) : Node(node) {}

Steve::UI::StyledNode
Steve::UI::StyledNode::FromNode(const Node &node)
{
   return StyledNode(node);
}

Steve::UI::StyledNode
Steve::UI::StyledNode::WithStyles(const Styles &styles)
{
   Properties properties {};
   properties.styles = styles;

   return WithProperties(std::move(properties));
}

void
Steve::UI::StyledNode::UpdateStyles(const Styles &styles)
{
   m_Properties.styles = std::move(styles);
}
