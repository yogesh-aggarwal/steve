#include "Container.hpp"

Container::Container()
{
   m_TagName = "Container";
   m_ID      = "Container";
   m_Classes = {};

   m_Parent   = nullptr;
   m_Children = {};
}
