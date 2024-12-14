#include "container.hpp"

/* ------------------------------------------------------------------------------------------------------- */

using namespace steve;

/* ------------------------------------------------------------------------------------------------------- */

ui::Container::Container() {
   m_Properties.id      = "Container";
   m_Properties.tagName = "Container";
   m_Properties.classes = {};
   m_Properties.styles  = {};

   m_Parent   = nullptr;
   m_Children = {};
}

/* ------------------------------------------------------------------------------------------------------- */
