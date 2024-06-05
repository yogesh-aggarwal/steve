#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Steve/Shader/Shader.hpp>
#include <Steve/Shader/ShaderProgram.hpp>
#include <Steve/Objects/Vertex.hpp>
#include <Steve/Objects/IndexBuffer.hpp>
#include <Steve/Objects/VertexArray.hpp>
#include <Steve/Objects/VertexBuffer.hpp>
#include <Steve/Objects/VertexBufferLayout.hpp>
#include <Steve/Draw/Draw.hpp>
#include <Steve/Renderer/Renderer.hpp>

void
ProcessInput(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
}

ShaderProgram
LoadShaderProgram()
{
   Result<bool> res { false };

   ShaderProgram shaderProgram =
       ShaderProgram::FromFiles(
           "/home/yogesh/Downloads/learn-opengl/Shaders/vertex.vs",
           "/home/yogesh/Downloads/learn-opengl/Shaders/fragment.fs")
           .value;

   res = shaderProgram.Allocate();
   if (!res) { res.error->Print("Shader program"); }

   return shaderProgram;
}

VertexBuffer vbo {};

void
Setup()
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
}

void
Render(ShaderProgram shaderProgram)
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

      glUseProgram(shaderProgram.GetID());
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
   }
}

int
main()
{
   system("clear");

   std::cout << "--------------" << std::endl;
   std::cout << "Starting Steve" << std::endl;
   std::cout << "--------------" << std::endl;

   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // MacOS only
#endif

   GLFWwindow *window =
       glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
   if (!window)
   {
      std::cerr << "Failed to create window" << std::endl;
      glfwTerminate();

      return EXIT_FAILURE;
   }

   glfwMakeContextCurrent(window);
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }

   auto shaderProgram = LoadShaderProgram();
   int  glError       = glGetError();
   if (glError)
   {
      std::cout << glError << std::endl;
      goto terminate;
   }

   // goto terminate;

   Setup();

   while (!glfwWindowShouldClose(window))
   {
      ProcessInput(window);

      Render(shaderProgram);

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

terminate:

   glfwTerminate();

   return EXIT_SUCCESS;
}
