#pragma once

#include "bound.hpp"

namespace steve::ui::StylingSpec {
   class Height : public Bound {
   public:
      inline Height() : Bound(-1.0f) {};
      Height(float min, float max, float value) : Bound(min, max, value) {}
      inline Height(float all) : Bound(all) {}
   };
}
