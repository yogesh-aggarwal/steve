#include "Utility.hpp"

#include <string>
#include <fstream>

#include <nanoid/nanoid.h>

std::string
Utility::GenerateNanoID(int length, std::string dictionary)
{
   return nanoid::generate(dictionary, length);
}

Result<std::string>
Utility::ReadFile(const std::string &path)
{
   try
   {
      std::ifstream file(path);
      if (!file.is_open())
         return { "",
                  new Error({ FILE_IO, "Unable to open the file: " + path }) };

      std::string content;
      std::string line;
      while (std::getline(file, line))
         content += line + "\n";

      return { content };
   }
   catch (const std::exception &e)
   {
      return { "",
               new Error({ FILE_IO,
                           "Failed to read the file: " + path + " (" +
                               e.what() + ")" }) };
   }
}
