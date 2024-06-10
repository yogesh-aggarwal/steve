/* --------------------------------------------------------------------------------- */
/* THIS FILE IS GENERATED USING A GENERATOR SCRIPT. DO NOT MODIFY THIS FILE DIRECTLY */
/* --------------------------------------------------------------------------------- */

#pragma once

// Shaders/fragment.fs
const char* SHADER_FRAGMENT = R"(#version 330 core

in vec4  outColor;
out vec4 FragColor;

void
main()
{
   FragColor = outColor;
}
)";

// Shaders/vertex.vs
const char* SHADER_VERTEX = R"(#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec4 outColor;

// orthographic projection matrix
uniform mat4 u_Projection;

void
main()
{
   gl_Position = vec4(aPos.xyz, 1.0f) * u_Projection;
   outColor    = aColor;
}
)";
