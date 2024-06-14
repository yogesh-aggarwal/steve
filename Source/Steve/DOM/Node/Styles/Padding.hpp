#pragma once

#include "EdgeStyle.tcc"

namespace Steve::DOM::StylingSpec
{
   class Padding : public EdgeStyle<float>
   {
   public:
      inline Padding() : EdgeStyle(0.0f) {};
      Padding(float top, float right, float bottom, float left)
          : EdgeStyle(top, right, bottom, left)
      {
         m_Top    = ClampToZero(top);
         m_Right  = ClampToZero(right);
         m_Bottom = ClampToZero(bottom);
         m_Left   = ClampToZero(left);
      }

      inline Padding(float all) : EdgeStyle(all) {}

      void
      SetTop(float top) override
      {
         m_Top = ClampToZero(top);
      }

      void
      SetRight(float right) override
      {
         m_Right = ClampToZero(right);
      }

      void
      SetBottom(float bottom) override
      {
         m_Bottom = ClampToZero(bottom);
      }

      void
      SetLeft(float left) override
      {
         m_Left = ClampToZero(left);
      }

      void
      SetVertical(float value) override
      {
         value = ClampToZero(value);

         m_Top    = value;
         m_Bottom = value;
      }

      void
      SetVertical(float top, float bottom) override
      {
         m_Top    = ClampToZero(top);
         m_Bottom = ClampToZero(bottom);
      }

      void
      SetHorizontal(float value) override
      {
         value = ClampToZero(value);

         m_Right = value;
         m_Left  = value;
      }

      void
      SetHorizontal(float right, float left) override
      {
         m_Right = ClampToZero(right);
         m_Left  = ClampToZero(left);
      }

      void
      Set(float top, float right, float bottom, float left) override
      {
         m_Top    = ClampToZero(top);
         m_Right  = ClampToZero(right);
         m_Bottom = ClampToZero(bottom);
         m_Left   = ClampToZero(left);
      }

      void
      SetAll(float all) override
      {
         all = ClampToZero(all);

         m_Top    = all;
         m_Right  = all;
         m_Bottom = all;
         m_Left   = all;
      }

   private:
      inline float
      ClampToZero(float value)
      {
         if (value < 0.0f) value = 0.0f;
         return value;
      }
   };
}
