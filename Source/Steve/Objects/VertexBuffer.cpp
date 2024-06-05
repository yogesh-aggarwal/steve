#include "VertexBuffer.hpp"

Result<bool>
VertexBuffer::BindAndAllocate()
{
   // TODO: Check for errors

   if (!m_HasInitialized)
   {
      glGenBuffers(1, &m_ID);
      m_HasInitialized = true;
   }

   glBindBuffer(GL_ARRAY_BUFFER, m_ID);
   glBufferData(GL_ARRAY_BUFFER,
                MAX_VERTICES * sizeof(Vertex),
                nullptr,
                GL_DYNAMIC_DRAW);

   return true;
}

Result<bool>
VertexBuffer::BindAndUploadData(const std::vector<Vertex> &data)
{
   if (!m_HasInitialized)
   {
      return { false,
               new Error({ STEVE_OBJECTS_VERTEX_BUFFER_NOT_INITIALIZED,
                           "Vertex buffer not initialized" }) };
   }

   if (data.size() > MAX_VERTICES)
   {
      return { false,
               new Error({ STEVE_OBJECTS_VERTEX_BUFFER_TOO_MANY_VERTICES,
                           "Too many vertices" }) };
   }

   glBindBuffer(GL_ARRAY_BUFFER, m_ID);
   glBufferSubData(GL_ARRAY_BUFFER,
                   0,
                   data.size() * sizeof(Vertex),
                   data.data());

   return true;
}

Result<bool>
VertexBuffer::Bind()
{
   // TODO: Check for errors

   if (!m_HasInitialized)
   {
      return { false,
               new Error({ STEVE_OBJECTS_VERTEX_BUFFER_NOT_INITIALIZED,
                           "Vertex buffer not initialized" }) };
   }

   glBindBuffer(GL_ARRAY_BUFFER, m_ID);

   return true;
}

Result<bool>
VertexBuffer::Unbind()
{
   // TODO: Check for errors

   if (!m_HasInitialized)
   {
      return { false,
               new Error({ STEVE_OBJECTS_VERTEX_BUFFER_NOT_INITIALIZED,
                           "Vertex buffer not initialized" }) };
   }

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   return true;
}
