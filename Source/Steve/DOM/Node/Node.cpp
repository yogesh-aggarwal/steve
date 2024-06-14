#include "Node.hpp"

Steve::DOM::Node::Node() : m_Properties({}), m_Parent(nullptr), m_Children({})
{
}

Steve::DOM::Node::Node(const Node &other)
{
   m_Properties = other.m_Properties;
   m_Parent     = other.m_Parent;
   m_Children   = other.m_Children;
}

Steve::DOM::Node
Steve::DOM::Node::WithProperties(const Properties &properties)
{
   Node node;
   node.m_Properties = properties;

   return node;
}

Steve::DOM::Node
Steve::DOM::Node::WithParent(const Ref<Node> &parent)
{
   Node node;
   node.m_Parent = parent;

   return node;
}

Steve::DOM::Node
Steve::DOM::Node::WithChildren(const std::vector<Ref<Node>> &children)
{
   Node node;
   node.m_Children = children;

   return node;
}
