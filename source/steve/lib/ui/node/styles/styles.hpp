#pragma once

#include "margin.hpp"
#include "padding.hpp"
#include "width.hpp"
#include "height.hpp"
#include "color.hpp"

namespace steve::ui {
   class Styles {
   private:
      StylingSpec::Margin  m_Margin;
      StylingSpec::Padding m_Padding;
      StylingSpec::Width   m_Width;
      StylingSpec::Height  m_Height;
      StylingSpec::Color   m_BackgroundColor;

   public:
      Styles()  = default;
      ~Styles() = default;

      inline bool
      operator==(const Styles &other) const {
         // TODO: Implement this
         return true;
      }

      inline bool
      operator!=(const Styles &other) const {
         return !(*this == other);
      }

      inline StylingSpec::Margin &
      GetMargin() {
         return m_Margin;
      }

      inline void
      SetMargin(StylingSpec::Margin margin) {
         m_Margin = margin;
      }

      inline StylingSpec::Padding &
      GetPadding() {
         return m_Padding;
      }

      inline void
      SetPadding(StylingSpec::Padding padding) {
         m_Padding = padding;
      }

      inline StylingSpec::Width &
      GetWidth() {
         return m_Width;
      }

      inline void
      SetWidth(StylingSpec::Width width) {
         m_Width = width;
      }

      inline StylingSpec::Height &
      GetHeight() {
         return m_Height;
      }

      inline void
      SetHeight(StylingSpec::Height height) {
         m_Height = height;
      }

      inline StylingSpec::Color &
      GetBackgroundColor() {
         return m_BackgroundColor;
      }

      inline void
      SetBackgroundColor(StylingSpec::Color color) {
         m_BackgroundColor = color;
      }
   };
}
