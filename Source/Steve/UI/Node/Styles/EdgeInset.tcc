#pragma once

namespace Steve::UI::StylingSpec
{
   template<typename T>
   class EdgeInset
   {
   protected:
      T m_Top;
      T m_Right;
      T m_Bottom;
      T m_Left;

   public:
      inline EdgeInset(T all)
          : m_Top(all), m_Right(all), m_Bottom(all), m_Left(all)
      {
      }

      inline EdgeInset(T top, T right, T bottom, T left)
          : m_Top(top), m_Right(right), m_Bottom(bottom), m_Left(left)
      {
      }

      ~EdgeInset()                      = default;
      EdgeInset(const EdgeInset &other) = default;

      inline bool
      operator==(const EdgeInset &other) const
      {
         return m_Top == other.m_Top && m_Right == other.m_Right &&
                m_Bottom == other.m_Bottom && m_Left == other.m_Left;
      }

      inline bool
      operator!=(const EdgeInset &other) const
      {
         return !(*this == other);
      }

      inline T
      GetTop() const
      {
         return m_Top;
      }

      inline T
      GetRight() const
      {
         return m_Right;
      }

      inline T
      GetBottom() const
      {
         return m_Bottom;
      }

      inline T
      GetLeft() const
      {
         return m_Left;
      }

      inline void virtual SetTop(T top) { m_Top = top; }

      inline void virtual SetRight(T right) { m_Right = right; }

      inline void virtual SetBottom(T bottom) { m_Bottom = bottom; }

      inline void virtual SetLeft(T left) { m_Left = left; }

      inline void virtual SetVertical(T value)
      {
         m_Top    = value;
         m_Bottom = value;
      }

      inline void virtual SetVertical(T top, T bottom)
      {
         m_Top    = top;
         m_Bottom = bottom;
      }

      inline void virtual SetHorizontal(T value)
      {
         m_Right = value;
         m_Left  = value;
      }

      inline void virtual SetHorizontal(T right, T left)
      {
         m_Right = right;
         m_Left  = left;
      }

      inline void virtual Set(T top, T right, T bottom, T left)
      {
         m_Top    = top;
         m_Right  = right;
         m_Bottom = bottom;
         m_Left   = left;
      }

      inline void virtual SetAll(T all)
      {
         m_Top    = all;
         m_Right  = all;
         m_Bottom = all;
         m_Left   = all;
      }
   };
}