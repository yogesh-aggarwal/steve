#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec4 outColor;

uniform mat4 u_Projection;

void
main()
{
   gl_Position = u_Projection * vec4(aPos.xyz, 1.0f);
   outColor    = aColor;
}
