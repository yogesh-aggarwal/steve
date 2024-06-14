#pragma once

#include "EdgeStyle.tcc"

namespace Steve::DOM::StylesSpec
{
   class Margin : public EdgeStyle<float>
   {
   public:
      inline Margin() : EdgeStyle(0.0f) {};
      Margin(float top, float right, float bottom, float left)
          : EdgeStyle(top, right, bottom, left)
      {
      }

      inline Margin(float all) : EdgeStyle(all) {}
   };
}
