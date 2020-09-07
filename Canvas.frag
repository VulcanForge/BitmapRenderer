#version 450 core

in vec2 textureCoordinates_frag;

out vec4 colour;

uniform sampler2D canvasTexture;

void main ()
{
    colour = texture (canvasTexture, textureCoordinates_frag);
}