#include "Steve.hpp"

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
      std::array<Vertex, 4> q =
          Steve::Draw::DrawQuad(0.0f,
                                0.0f,
                                ApplicationWindow::GetWidth(),
                                40.0f,
                                glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
      Renderer::DrawVertices({ q.begin(), q.end() });

      q = Steve::Draw::DrawQuad(4.0f,
                                4.0f,
                                32.0f,
                                32.0f,
                                glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
      Renderer::DrawVertices({ q.begin(), q.end() });
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
