#version 450 core

layout (location = 0) in vec2 positionXY;
layout (location = 1) in vec2 textureCoordinates_vert;

out vec2 textureCoordinates_frag;

void main ()
{
    textureCoordinates_frag = textureCoordinates_vert;
    gl_Position = vec4 (positionXY, 0, 1);
}
