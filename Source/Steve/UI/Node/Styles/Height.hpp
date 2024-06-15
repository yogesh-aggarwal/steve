#pragma once

#include "Bound.hpp"

namespace Steve::UI::StylingSpec
{
   class Height : public Bound
   {
   public:
      inline Height() : Bound(-1.0f) {};
      Height(float min, float max, float value) : Bound(min, max, value) {}
      inline Height(float all) : Bound(all) {}
   };
}
