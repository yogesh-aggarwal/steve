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
#include <Steve/Objects/ApplicationWindow.hpp>

namespace Application
{
   void
   OnInit()
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
   OnRender()
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
         std::array<Vertex, 4> q1 =
             Steve::Draw::DrawQuad(0.0f, 0.0f, 1.0f, 1.0f, glm::vec4(0.0f));
         Renderer::DrawVertices({ q1.begin(), q1.end() });
      }

      // End scene
      _ = Renderer::EndScene().WithErrorHandler([](Ref<Error> error) {
         error->Push({ STEVE_APPLICATION_RENDER_FAILED,
                       "Failed to end rendering scene." });
      });
   }

   void
   OnTerminate()
   {
   }

   void
   OnKey(int key)
   {
   }
}

STEVE_MAIN("Steve Woss", 800, 600, Application)
