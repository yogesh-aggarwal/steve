#include <iostream>
#include <fstream>
#include <string>

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
   VertexBuffer vbo {};

   void
   OnInit()
   {
      auto _ = Result<bool> { false };

      VertexArray vao {};
      _ = vao.AllocateAndBind();

      _ = vbo.BindAndAllocate();

      IndexBuffer ibo {};
      _ = ibo.BindAndPopulate();

      VertexBufferLayout positionLayout(0, 3, 0);
      VertexBufferLayout colorLayout(1, 4, 3);
      _ = positionLayout.Apply();
      _ = colorLayout.Apply();

      ShaderProgram shaderProgram =
          ShaderProgram::FromFiles(
              "/home/yogesh/Downloads/learn-opengl/Shaders/vertex.vs",
              "/home/yogesh/Downloads/learn-opengl/Shaders/fragment.fs")
              .value;
      _ = shaderProgram.Allocate();
      glUseProgram(shaderProgram.GetID());
   }

   void
   OnRender()
   {
      // Render commands here
      int glError = glGetError();
      if (glError) std::cout << glError << std::endl;

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Begin scene
      {
      }

      // Draw a quad
      std::vector<Vertex> vertices = {};
      {
         std::array<Vertex, 4> q1 =
             Steve::Draw::DrawQuad(0.0f, 0.0f, 1.0f, 1.0f, glm::vec4(0.0f));
         for (auto &v : q1)
         {
            vertices.push_back(v);
            v.Print();
         }
      }

      // End scene
      {
         auto _ = vbo.BindAndUploadData(vertices);
         if (!_) { _.error->Print("Vertex buffer"); }
         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
      }
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

int
main()
{
   system("clear");

   ApplicationWindow::Callbacks callbacks {};
   callbacks.OnInit      = Application::OnInit;
   callbacks.OnRender    = Application::OnRender;
   callbacks.OnTerminate = Application::OnTerminate;
   callbacks.OnKey       = Application::OnKey;

   ApplicationWindow window(callbacks);
   window.Initialize();
   window.Run();
   window.Terminate();

   return EXIT_SUCCESS;
}
