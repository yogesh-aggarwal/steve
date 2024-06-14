#include "StyledNode.hpp"

Steve::DOM::StyledNode::StyledNode(const Node &node) : Node(node) {}

Steve::DOM::StyledNode
Steve::DOM::StyledNode::FromNode(const Node &node)
{
   return StyledNode(node);
}

Steve::DOM::StyledNode
Steve::DOM::StyledNode::WithStyles(const Styles &styles)
{
   Properties properties {};
   properties.styles = styles;

   return WithProperties(std::move(properties));
}

void
Steve::DOM::StyledNode::UpdateStyles(const Styles &styles)
{
   m_Properties.styles = std::move(styles);
}
