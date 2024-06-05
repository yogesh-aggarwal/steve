#pragma once

#include <iostream>

struct Vertex
{
   alignas(4) float x;
   alignas(4) float y;
   alignas(4) float z;
   alignas(4) float r;
   alignas(4) float g;
   alignas(4) float b;
   alignas(4) float a;

   inline void
   Print() const
   {
      std::cout << x << " " << y << " " << z << " " << r << " " << g << " " << b
                << " " << a << std::endl;
   }
};
