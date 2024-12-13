#pragma once

#include "bound.hpp"

namespace steve::ui::StylingSpec {
   class Width : public Bound {
   public:
      inline Width() : Bound(-1.0f) {};
      Width(float min, float max, float value) : Bound(min, max, value) {}
      inline Width(float all) : Bound(all) {}
   };
}
