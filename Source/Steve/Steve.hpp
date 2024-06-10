#pragma once

#define STEVE_MAIN(TITLE, WIDTH, HEIGHT, APPLICATION_LIFECYCLE) \
   int main()                                                   \
   {                                                            \
      system("clear");                                          \
                                                                \
      APPLICATION_LIFECYCLE lifecycle {};                       \
                                                                \
      ApplicationWindow::Configuration config {                 \
         .Title        = TITLE,                                 \
         .Width        = WIDTH,                                 \
         .Height       = HEIGHT,                                \
         .LifeCyclePtr = &lifecycle,                            \
      };                                                        \
                                                                \
      auto _ = Result<bool> { false };                          \
                                                                \
      _ = ApplicationWindow::Initialize(config);                \
      _ = ApplicationWindow::Run();                             \
      ApplicationWindow::Terminate();                           \
                                                                \
      return EXIT_SUCCESS;                                      \
   }
