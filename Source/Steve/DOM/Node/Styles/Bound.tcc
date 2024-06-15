#pragma once

namespace Steve::DOM::StylingSpec
{
   class Bound
   {
   protected:
      float m_Min;
      float m_Max;
      float m_Value;

   public:
      inline Bound(float all) : m_Min(all), m_Max(all), m_Value(all) {}

      inline Bound(float min, float max, float value)
          : m_Min(min), m_Max(max), m_Value(value)
      {
      }

      ~Bound()                  = default;
      Bound(const Bound &other) = default;

      inline bool
      operator==(const Bound &other) const
      {
         return m_Min == other.m_Min && m_Max == other.m_Max &&
                m_Value == other.m_Value;
      }

      inline bool
      operator!=(const Bound &other) const
      {
         return !(*this == other);
      }

      inline float
      GetMin() const
      {
         return m_Min;
      }

      inline float
      GetMax() const
      {
         return m_Max;
      }

      inline float
      GetValue() const
      {
         return m_Value;
      }

      inline void
      SetMin(float min)
      {
         m_Min = min;
      }

      inline void
      SetMax(float max)
      {
         m_Max = max;
      }

      inline void
      SetValue(float value)
      {
         m_Value = value;
      }

      inline void
      Set(float min, float max, float value)
      {
         m_Min   = min;
         m_Max   = max;
         m_Value = value;
      }

      inline void
      Set(float all)
      {
         m_Min   = all;
         m_Max   = all;
         m_Value = all;
      }

      inline bool
      IsBound() const
      {
         return m_Min != m_Max;
      }

      inline bool
      IsMinBoundDefined() const
      {
         return m_Min >= 0.0f;
      }

      inline bool
      IsMaxBoundDefined() const
      {
         return m_Max >= 0.0f;
      }

      inline bool
      IsValueBoundDefined() const
      {
         return m_Value >= 0.0f;
      }
   };
}
