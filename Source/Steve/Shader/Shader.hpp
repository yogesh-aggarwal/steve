#pragma once

#include <iostream>
#include <stdint.h>
#include <string>

#include <Steve/Core/Result.tcc>

class Shader
{
public:
   enum Type
   {
      Vertex,
      Fragment
   };

private:
   Type        m_Type;
   uint32_t    m_ID;
   std::string m_Source;

public:
   Shader() = delete;

   Shader(Type type);

   static Shader
   FromSource(Type type, std::string source);

   static Result<Shader>
   FromFile(Type type, std::string path);

   uint32_t
   GetID() const;

   std::string
   GetSource() const;

   Result<bool>
   Allocate();

private:
   Shader(std::string);
};
