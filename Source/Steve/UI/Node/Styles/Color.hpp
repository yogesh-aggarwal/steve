#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Steve::UI::StylingSpec
{
   class Color
   {
   private:
      glm::vec4 m_Color;

   public:
      Color() = default;
      inline Color(const glm::vec4 &color) : m_Color(color) {}

      inline const glm::vec4 &
      GetColor() const
      {
         return m_Color;
      }

      inline void
      SetColor(const glm::vec4 &color)
      {
         m_Color = color;
      }

      static Color
      FromHexString(const std::string &hexString);

      static Color
      FromHex(uint32_t hex);

      static Color
      FromRGB(uint8_t r, uint8_t g, uint8_t b);

      static Color
      FromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

      std::string
      ToHexString() const;

      uint32_t
      ToHex() const;
   };
}
