#pragma once

#include <Steve/Core/Result.tcc>

namespace Utility
{
   Result<std::string>
   ReadFile(const std::string &path);
}
