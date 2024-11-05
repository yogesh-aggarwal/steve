#include <Steve/Steve.hpp>

int
main()
{
   system("clear");

   auto _ = Steve::Run();
   if (!_)
   {
      _.error->Print();
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
