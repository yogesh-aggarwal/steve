#pragma once

#include "Margin.hpp"
#include "Padding.hpp"

namespace Steve::DOM
{
   class Styles
   {
   private:
      StylingSpec::Margin  m_Margin;
      StylingSpec::Padding m_Padding;

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

      inline StylingSpec::Margin
      GetMargin()
      {
         return m_Margin;
      }

      inline void
      SetMargin(StylingSpec::Margin margin)
      {
         m_Margin = margin;
      }

      inline StylingSpec::Padding
      GetPadding()
      {
         return m_Padding;
      }

      inline void
      SetPadding(StylingSpec::Padding padding)
      {
         m_Padding = padding;
      }
   };
}
