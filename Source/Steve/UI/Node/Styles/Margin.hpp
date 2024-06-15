#pragma once

#include "EdgeInset.tcc"

namespace Steve::UI::StylingSpec
{
   class Margin : public EdgeInset<float>
   {
   public:
      inline Margin() : EdgeInset(0.0f) {};
      Margin(float top, float right, float bottom, float left)
          : EdgeInset(top, right, bottom, left)
      {
      }

      inline Margin(float all) : EdgeInset(all) {}
   };
}
