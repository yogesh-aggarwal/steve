#pragma once

#include <iostream>

#include <glm/glm.hpp>

struct Vertex
{
   glm::vec3 position;
   glm::vec4 color;

   inline void
   Print() const
   {
      std::cout << position.x << " " << position.y << " " << position.z << " "
                << color.r << " " << color.g << " " << color.b << " " << color.a
                << std::endl;
   }
};
