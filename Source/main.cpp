#include <iostream>
#include <fstream>
#include <string>

#include <Steve/Steve.hpp>
#include <Steve/Graphics/Draw/Draw.hpp>
#include <Steve/Graphics/Renderer/Renderer.hpp>
#include <Steve/Application/ApplicationWindow.hpp>

class Application : public ApplicationWindow::LifeCycle
{
   void
   OnInit() override
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
   OnRender() override
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
                                   ApplicationWindow::GetWidth() / 2 - 4.0f,
                                   32.0f,
                                   glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
         Renderer::DrawVertices({ q.begin(), q.end() });
      }

      // End scene
      _ = Renderer::EndScene().WithErrorHandler([](Ref<Error> error) {
         error->Push({ STEVE_APPLICATION_RENDER_FAILED,
                       "Failed to end rendering scene." });
      });
   }
};

ApplicationWindow::Configuration config {
   .Title        = "Steve",
   .Width        = 800,
   .Height       = 600,
   .LifeCyclePtr = new Application(),
};

STEVE_MAIN(config)
