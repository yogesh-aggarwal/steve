#pragma once

#include <Steve/Core/Result.tcc>

namespace Utility
{
   std::string
   GenerateNanoID(
       int         length,
       std::string dictionary = "1234567890abcdefghijklmnopqrstuvwxyz");

   Result<std::string>
   ReadFile(const std::string &path);
}
