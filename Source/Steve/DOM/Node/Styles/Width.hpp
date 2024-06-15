#pragma once

#include "Bound.tcc"

namespace Steve::DOM::StylingSpec
{
   class Width : public Bound
   {
   public:
      inline Width() : Bound(-1.0f) {};
      Width(float min, float max, float value) : Bound(min, max, value) {}
      inline Width(float all) : Bound(all) {}
   };
}
