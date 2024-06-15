#include "Steve.hpp"

#include <Steve/UI/UI.hpp>
#include <Steve/UI/Container/Container.hpp>

void
Application::OnInit()
{
   auto _ = Renderer::Initialize().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_APPLICATION_INITIALIZATION_FAILED,
                    "Failed to initialize application." });
   });
   if (!_)
   {
      _.error->Print();
      return;
   }
}

// int width = ApplicationWindow::GetWidth();

void
Application::OnRender()
{
   // if (width == ApplicationWindow::GetWidth()) return;
   // std::cout << "Render\n";
   // width = ApplicationWindow::GetWidth();

   auto _ = Result<bool> { false };

   // Begin scene
   _ = Renderer::BeginScene().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_APPLICATION_RENDER_FAILED,
                    "Failed to being rendering scene." });
   });
   if (!_)
   {
      _.error->Print();
      return;
   }

   // Draw a quad
   {
      Steve::UI::Styles styles {};
      styles.SetWidth(4.0f);

      Steve::UI::Container c {};

      for (int i = 0; i < 10; i++)
      {
         Steve::UI::Container n {};
         n.UpdateStyles(styles);
         c.PushChild(n);
      }

      auto vertices = Steve::UI::TranslateToQuads(c);
      for (auto &v : vertices)
         Renderer::DrawVertices({ v.begin(), v.end() });
   }

   // End scene
   _ = Renderer::EndScene().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_APPLICATION_RENDER_FAILED,
                    "Failed to end rendering scene." });
   });
   if (!_)
   {
      _.error->Print();
      return;
   }
}

Result<bool>
Steve::Run()
{
   auto _ = Result<bool> { false };

   ApplicationWindow::Configuration config {
      .Title        = "Steve Browser",
      .Width        = 800,
      .Height       = 600,
      .LifeCyclePtr = new Application(),

      .IsVSync = false,
   };

   _ = ApplicationWindow::Initialize(config).WithErrorHandler(
       [](Ref<Error> error) {
          error->Push({ STEVE_ERROR, "Failed to initialize steve." });
       });
   if (!_) return _;

   _ = ApplicationWindow::Run().WithErrorHandler([](Ref<Error> error) {
      error->Push({ STEVE_ERROR, "Failed to run steve." });
   });
   if (!_) return _;

   ApplicationWindow::Terminate();

   return { true };
}
