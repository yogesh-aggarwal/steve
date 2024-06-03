#include <iostream>

#include <GLFW/glfw3.h>

void
ProcessInput(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
}

void
Render()
{
   // Render commands here
}

int
main()
{
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

   while (!glfwWindowShouldClose(window))
   {
      ProcessInput(window);

      Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwTerminate();

   return EXIT_SUCCESS;

   return 0;
}
