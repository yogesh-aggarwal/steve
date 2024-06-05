#pragma once

#define STEVE_MAIN(APPLICATION_NAMESPACE)                         \
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
      ApplicationWindow window(callbacks);                        \
      window.Initialize();                                        \
      window.Run();                                               \
      window.Terminate();                                         \
                                                                  \
      return EXIT_SUCCESS;                                        \
   }
