#pragma once

#define STEVE_MAIN(TITLE, WIDTH, HEIGHT, APPLICATION_NAMESPACE)   \
   int main()                                                     \
   {                                                              \
      system("clear");                                            \
                                                                  \
      ApplicationWindow::Callbacks callbacks {};                  \
      callbacks.OnInit      = APPLICATION_NAMESPACE::OnInit;      \
      callbacks.OnRender    = APPLICATION_NAMESPACE::OnRender;    \
      callbacks.OnTerminate = APPLICATION_NAMESPACE::OnTerminate; \
      callbacks.OnKey       = APPLICATION_NAMESPACE::OnKey;       \
                                                                  \
      auto _ = Result<bool> { false };                            \
                                                                  \
      ApplicationWindow window(TITLE, WIDTH, HEIGHT, callbacks);  \
      _ = window.Initialize();                                    \
      _ = window.Run();                                           \
      window.Terminate();                                         \
                                                                  \
      return EXIT_SUCCESS;                                        \
   }
