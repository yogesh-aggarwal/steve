#pragma once

#include "Margin.hpp"
#include "Padding.hpp"

namespace Steve::DOM
{
   class Styles
   {
   private:
      StylesSpec::Margin  m_Margin;
      StylesSpec::Padding m_Padding;

   public:
      Styles()  = default;
      ~Styles() = default;

      inline bool
      operator==(const Styles &other) const
      {
         // TODO: Implement this
         return true;
      }

      inline bool
      operator!=(const Styles &other) const
      {
         return !(*this == other);
      }

      inline StylesSpec::Margin
      GetMargin()
      {
         return m_Margin;
      }

      inline void
      SetMargin(StylesSpec::Margin margin)
      {
         m_Margin = margin;
      }

      inline StylesSpec::Padding
      GetPadding()
      {
         return m_Padding;
      }

      inline void
      SetPadding(StylesSpec::Padding padding)
      {
         m_Padding = padding;
      }
   };
}
