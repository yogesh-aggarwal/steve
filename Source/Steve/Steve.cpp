#include "Steve.hpp"

#include <Steve/UI/UI.hpp>
#include <Steve/UI/Container/Container.hpp>

Steve::UI::Container
DrawUI()
{
   Steve::UI::Container canvas {};
   auto                 cRef = CreateRef<Steve::UI::Container>(canvas);
   {
      Steve::UI::Styles styles {};
      styles.GetPadding().SetAll(8.0f);

      canvas.UpdateStyles(styles);
   }

   // Rest of the UI
   {   // Topbar container
      {
         Steve::UI::Container n {};
         n.GetProperties().id = "topbar";
         n.SetParent(cRef);

         Steve::UI::Styles styles {};
         styles.SetHeight(16.0f);
         n.UpdateStyles(styles);

         canvas.PushChild(n);
      }

      // Banner
      {
         Steve::UI::Container n {};
         n.GetProperties().id = "banner";
         n.SetParent(cRef);

         Steve::UI::Styles styles {};
         styles.SetHeight(32.0f);
         n.UpdateStyles(styles);

         canvas.PushChild(n);

         // Left side
         {
            Steve::UI::Container l {};
            l.GetProperties().id = "left-side";
            l.SetParent(cRef);

            Steve::UI::Styles styles {};
            styles.SetWidth(200.0f);
            l.UpdateStyles(styles);

            l.PushChild(n);
         }

         // Right side
         {
            Steve::UI::Container r {};
            r.GetProperties().id = "right-side";
            r.SetParent(cRef);

            Steve::UI::Styles styles {};
            styles.SetWidth(200.0f);
            r.UpdateStyles(styles);

            r.PushChild(n);
         }
      }
   }

   return canvas;
}

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

   // Draw UI
   {
      auto canvas   = DrawUI();
      auto vertices = Steve::UI::TranslateToQuads(canvas);
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

   // ApplicationWindow::Terminate();
}

Result<bool>
Steve::Run()
{
   auto _ = Result<bool> { false };

   ApplicationWindow::Configuration config {
      .Title        = "Steve Browser",
      .Width        = (uint32_t)(1920.0f * 0.55f),
      .Height       = (uint32_t)(1080.0f * 0.65f),
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
