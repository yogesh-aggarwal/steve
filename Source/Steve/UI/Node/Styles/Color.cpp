#include "Color.hpp"
#include <iostream>

Steve::UI::StylingSpec::Color
Steve::UI::StylingSpec::Color::FromHexString(const std::string &hexString)
{
   std::string hex = hexString;

   if (hex.size() < 3) return Color(glm::vec4(0.0f));
   // eg: #2c -> #2c2c2c
   if (hex.size() == 3) hex += hexString.substr(1, 2) + hexString.substr(1, 2);
   // eg: #fff -> #ffffff
   if (hex.size() == 4) hex += hexString.substr(1, 3);
   // eg: #2c2c2c -> #2c2c2cff
   if (hex.size() == 7) hex += "FF";

   float r =
       static_cast<float>(std::stoi(hex.substr(1, 2), nullptr, 16)) / 255.0f;
   float g =
       static_cast<float>(std::stoi(hex.substr(3, 2), nullptr, 16)) / 255.0f;
   float b =
       static_cast<float>(std::stoi(hex.substr(5, 2), nullptr, 16)) / 255.0f;
   float a =
       static_cast<float>(std::stoi(hex.substr(7, 2), nullptr, 16)) / 255.0f;

   return Color(glm::vec4(r, g, b, a));
}

Steve::UI::StylingSpec::Color
Steve::UI::StylingSpec::Color::FromHex(uint32_t hex)
{
   float r = static_cast<float>((hex >> 24) & 0xFF) / 255.0f;
   float g = static_cast<float>((hex >> 16) & 0xFF) / 255.0f;
   float b = static_cast<float>((hex >> 8) & 0xFF) / 255.0f;
   float a = static_cast<float>(hex & 0xFF) / 255.0f;

   return Color(glm::vec4(r, g, b, a));
}

Steve::UI::StylingSpec::Color
Steve::UI::StylingSpec::Color::FromRGB(uint8_t r, uint8_t g, uint8_t b)
{
   return FromRGBA(r, g, b, 255);
}

Steve::UI::StylingSpec::Color
Steve::UI::StylingSpec::Color::FromRGBA(uint8_t r,
                                        uint8_t g,
                                        uint8_t b,
                                        uint8_t a)
{
   return Color(glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f));
}

std::string
Steve::UI::StylingSpec::Color::ToHexString() const
{
   char hexString[9];
   std::snprintf(hexString,
                 sizeof(hexString),
                 "#%02x%02x%02x%02x",
                 static_cast<int>(m_Color.r * 255),
                 static_cast<int>(m_Color.g * 255),
                 static_cast<int>(m_Color.b * 255),
                 static_cast<int>(m_Color.a * 255));
   return std::string(hexString);
}

uint32_t
Steve::UI::StylingSpec::Color::ToHex() const
{
   return static_cast<uint32_t>(m_Color.r * 255) << 24 |
          static_cast<uint32_t>(m_Color.g * 255) << 16 |
          static_cast<uint32_t>(m_Color.b * 255) << 8 |
          static_cast<uint32_t>(m_Color.a * 255);
}
