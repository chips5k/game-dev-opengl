#version 330 core
out vec4 fragColour;
in vec4 vertexColour;
uniform vec4 ourColour;
void main()
{
    fragColour = vec4(vertexColour.x * ourColour.x, vertexColour.y * ourColour.y, vertexColour.z * ourColour.z, 1.0);
}