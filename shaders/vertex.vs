#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
uniform vec4 ourColour;
out vec4 vertexColour;

void main()
{
    gl_Position = vec4(aPos.x * ourColour.x, -aPos.y * ourColour.y, aPos.z* ourColour.y, 0.8);
    vertexColour = vec4(aColour , 1.0);
}