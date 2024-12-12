#pragma once

#include <steve/core/pch>

#include <glm/glm.hpp>

/* ------------------------------------------------------------------------------------------------------- */

struct Vertex {
   glm::vec3 position;
   glm::vec4 color;

   inline void
   print() const {
      // clang-format off
      std::cout << position.x << " " << position.y << " " << position.z << " "
                << color.r << " " << color.g << " " << color.b << " " << color.a
                << std::endl;
      // clang-format on
   }

   inline
   operator float *() {
      return &position.x;
   }

   inline
   operator const float *() const {
      return &position.x;
   }

   inline
   operator glm::vec3 &() {
      return position;
   }

   inline
   operator const glm::vec3 &() const {
      return position;
   }

   inline
   operator glm::vec4 &() {
      return color;
   }

   inline
   operator const glm::vec4 &() const {
      return color;
   }

   inline Vertex
   operator*(const float &scalar) const {
      return { position * scalar, color };
   }
};

/* ------------------------------------------------------------------------------------------------------- */
