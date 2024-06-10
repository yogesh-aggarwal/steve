#include <iostream>
#include <fstream>
#include <string>

#include <Steve/Steve.hpp>
#include <Steve/Shader/Shader.hpp>
#include <Steve/Shader/ShaderProgram.hpp>
#include <Steve/Objects/Vertex.hpp>
#include <Steve/Objects/IndexBuffer.hpp>
#include <Steve/Objects/VertexArray.hpp>
#include <Steve/Objects/VertexBuffer.hpp>
#include <Steve/Objects/VertexBufferLayout.hpp>
#include <Steve/Draw/Draw.hpp>
#include <Steve/Renderer/Renderer.hpp>
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
             Steve::Draw::DrawQuad(0.0f, 0.0f, 1920.0f, 40.0f, glm::vec4(0.0f));
         Renderer::DrawVertices({ q.begin(), q.end() });

         q = Steve::Draw::DrawQuad(1.0f, 1.0f, 1918.0f, 38.0f, glm::vec4(1.0f));
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
