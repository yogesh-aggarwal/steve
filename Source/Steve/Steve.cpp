#include "Steve.hpp"

#include <Steve/UI/UI.hpp>
#include <Steve/UI/Container/Container.hpp>

Ref<Steve::UI::Container>
DrawUI()
{
   auto canvas                = CreateRef<Steve::UI::Container>();
   canvas->GetProperties().id = "body";
   {
      Steve::UI::Styles styles {};
      styles.GetPadding().SetAll(8.0f);
      styles.SetBackgroundColor(
          Steve::UI::StylingSpec::Color::FromHexString("#fff"));
      styles.SetWidth(1056.0f);

      canvas->UpdateStyles(styles);
   }

   // Rest of the UI
   {
      Steve::UI::StylingSpec::Width width {};
      width.SetMin(100.0f);

      // Left side
      {
         auto l                = CreateRef<Steve::UI::Container>();
         l->GetProperties().id = "left-side";
         l->SetParent(canvas);

         Steve::UI::Styles styles {};
         // styles.SetWidth(width);
         styles.GetWidth().SetMin(500.0f);
         styles.SetHeight(100.0f);
         styles.SetBackgroundColor(
             Steve::UI::StylingSpec::Color::FromHexString("#ff0000"));
         l->UpdateStyles(styles);

         canvas->PushChild(l);
      }
      // Right side
      {
         auto r                = CreateRef<Steve::UI::Container>();
         r->GetProperties().id = "right-side";
         r->SetParent(canvas);

         Steve::UI::Styles styles {};
         styles.SetWidth(width);
         styles.SetHeight(80.0f);
         styles.SetBackgroundColor(
             Steve::UI::StylingSpec::Color::FromHexString("#00ff00"));
         r->UpdateStyles(styles);

         canvas->PushChild(r);
      }
      // Right side
      {
         auto r                = CreateRef<Steve::UI::Container>();
         r->GetProperties().id = "right-side";
         r->SetParent(canvas);

         Steve::UI::Styles styles {};
         styles.SetWidth(width);
         styles.SetHeight(80.0f);
         styles.SetBackgroundColor(
             Steve::UI::StylingSpec::Color::FromHexString("#0000ff"));
         r->UpdateStyles(styles);

         canvas->PushChild(r);
      }
   }

   canvas->CalculateBounds();

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
