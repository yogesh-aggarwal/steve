#pragma once

#define STEVE_MAIN(CONFIG)                       \
   int main()                                    \
   {                                             \
      system("clear");                           \
                                                 \
      auto _ = Result<bool> { false };           \
                                                 \
      _ = ApplicationWindow::Initialize(CONFIG); \
      _ = ApplicationWindow::Run();              \
      ApplicationWindow::Terminate();            \
                                                 \
      return EXIT_SUCCESS;                       \
   }
