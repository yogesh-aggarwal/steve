#pragma once

#include <iostream>
#include <stdint.h>
#include <string>

#include <steve/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

namespace steve {
   class Shader {
   public:
      enum Type { Vertex, Fragment };

   private:
      Type        m_Type;
      uint32_t    m_ID;
      std::string m_Source;

   public:
      Shader() = delete;

      Shader(Type type);

      static Shader
      from_source(Type type, std::string source);

      static Result<Shader>
      from_file(Type type, std::string path);

      uint32_t
      get_id() const;

      std::string
      get_source() const;

      VoidResult
      allocate();

   private:
      Shader(std::string);
   };
}

/* ------------------------------------------------------------------------------------------------------- */
