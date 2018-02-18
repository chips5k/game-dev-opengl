#version 330 core
out vec4 fragColour;
in vec4 vertexColour;
in vec2 texCoord;
uniform vec4 ourColour;
uniform sampler2D ourTexture;

void main()
{
    fragColour = texture(ourTexture, texCoord) * vec4(vertexColour);
    //fragColour = vertexColour;
    //fragColour = vec4(vertexColour.x * ourColour.x, vertexColour.y * ourColour.y, vertexColour.z * ourColour.z, 1.0);
}