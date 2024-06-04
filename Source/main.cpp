#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string
ReadFileContent(const std::string &path)
{
   std::ifstream file(path);
   if (!file.is_open())
   {
      std::cerr << "Failed to open file: " << path << std::endl;
      return "";
   }

   std::string content;
   std::string line;
   while (std::getline(file, line))
      content += line + "\n";

   return content;
}

void
ProcessInput(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
}

uint32_t
LoadShaderProgram()
{
   uint32_t shaderProgram;
   {
      auto vsSourceString     = ReadFileContent("../Shaders/vertex.vs");
      auto vertexShaderSource = vsSourceString.c_str();

      uint32_t vertexShader;
      vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
      glCompileShader(vertexShader);

      int success_vs;
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vs);
      if (!success_vs)
      {
         char infoLog[512];
         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                   << infoLog << std::endl;
      }

      auto     fsSourceString       = ReadFileContent("../Shaders/fragment.fs");
      auto     fragmentShaderSource = fsSourceString.c_str();
      uint32_t fragmentShader;
      fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
      glCompileShader(fragmentShader);

      int success_fs;
      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fs);
      if (!success_fs)
      {
         char infoLog[512];
         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                   << infoLog << std::endl;
      }

      shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertexShader);
      glAttachShader(shaderProgram, fragmentShader);
   }

   glLinkProgram(shaderProgram);

   return shaderProgram;
}

void
Setup()
{
   // clang-format off
   float vertices[] = {
   // Vertices              // Color
      -0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
       0.5f, -0.5f,  0.0f,     0.0f, 1.0f, 0.0f, 1.0f,
       0.5f,  0.5f,  0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
      -0.5f, -0.5f,  0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
   };
   uint32_t indices[] = {
      0, 1, 2,
      2, 3, 0,
   };
   // clang-format on

   uint32_t vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   uint32_t vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   uint32_t ebo;
   glGenBuffers(1, &ebo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                sizeof(indices),
                indices,
                GL_STATIC_DRAW);

   glVertexAttribPointer(0,
                         2,
                         GL_FLOAT,
                         GL_FALSE,
                         6 * sizeof(float),
                         (void *)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1,
                         4,
                         GL_FLOAT,
                         GL_FALSE,
                         6 * sizeof(float),
                         (void *)(2 * sizeof(float)));
   glEnableVertexAttribArray(1);
}

void
Render(uint32_t shaderProgram)
{
   // Render commands here
   int glError = glGetError();
   if (glError) std::cout << glError << std::endl;

   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   glUseProgram(shaderProgram);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

int
main()
{
   system("clear");

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
