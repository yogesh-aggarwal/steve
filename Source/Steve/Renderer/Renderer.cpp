#include "Renderer.hpp"

Renderer::Renderer(ShaderProgram shaderProgram)
    : m_Vertices(MAX_VERTICES), m_HasBegunScene(false), m_VertexArray(),
      m_VertexBuffer(), m_IndexBuffer(), m_ShaderProgram(shaderProgram)
{
}

Renderer::~Renderer()
{
   if (!m_HasBegunScene) return;

   auto _ = EndScene();
}

Result<bool>
Renderer::Initialize()
{
   auto _ = Result<bool> { false };

   _ = m_ShaderProgram.Allocate();
   if (!_) return _;
   _ = m_VertexArray.AllocateAndBind();
   if (!_) return _;
   _ = m_VertexBuffer.BindAndAllocate();
   if (!_) return _;
   _ = m_IndexBuffer.BindAndPopulate();
   if (!_) return _;

   VertexBufferLayout positionLayout(0, 3, 0);
   _ = positionLayout.Apply();
   if (!_) return _;

   VertexBufferLayout colorLayout(1, 4, 3);
   _ = colorLayout.Apply();
   if (!_) return _;

   m_HasInitialized = true;

   return true;
}

Result<bool>
Renderer::BeginScene()
{
   if (!m_HasInitialized)
   {
      return { false,
               new Error({ STEVE_RENDERER_NOT_INITIALIZED,
                           "Renderer not initialized" }) };
   }
   if (m_HasBegunScene)
   {
      return { false,
               new Error({ STEVE_RENDERER_SCENE_ALREADY_BEGUN,
                           "Renderer scene already begun" }) };
   }

   m_HasBegunScene = true;
   m_Vertices.clear();

   return true;
}

Result<bool>
Renderer::EndScene()
{
   if (!m_HasInitialized)
   {
      return { false,
               new Error({ STEVE_RENDERER_NOT_INITIALIZED,
                           "Renderer not initialized" }) };
   }
   if (!m_HasBegunScene)
   {
      return { false,
               new Error({ STEVE_RENDERER_SCENE_HAS_NOT_BEGUN,
                           "Renderer scene has not begun" }) };
   }
   if (m_Vertices.empty()) { return true; }

   for (auto &v : m_Vertices)
      v.Print();

   auto _ = Result<bool> { false };

   _ = m_VertexBuffer.BindAndUploadData(m_Vertices);
   _ = m_ShaderProgram.Use();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

   Flush();

   return true;
}

void
Renderer::Flush()
{
   m_HasBegunScene = false;
   m_Vertices.clear();

   m_VertexArray.Flush();
   m_VertexBuffer.Flush();
}

Result<bool>
Renderer::DrawVertices(const std::vector<Vertex> &vertices)
{
   if (vertices.size() > MAX_VERTICES)
   {
      std::cerr << "Too many vertices" << std::endl;
      return false;
   }

   m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());

   return true;
}
