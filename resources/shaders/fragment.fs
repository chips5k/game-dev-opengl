#version 330 core
out vec4 fragColour;
in vec4 vertexColour;
in vec2 texCoord;
uniform vec4 ourColour;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alphaMix;

void main()
{
    fragColour = mix(texture(texture1, texCoord), texture(texture2, vec2(-texCoord.x, texCoord.y)), alphaMix);
}