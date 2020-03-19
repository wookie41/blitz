#version 330 core

layout(location = 0) in vec2 _bPosition;
layout(location = 1) in vec2 _bTexCoords;

out vec2 TextureCoords;

uniform ivec2 _bViewPortSize;

uniform vec2 _bSpritePosition;
uniform ivec2 _bSpriteSize;
uniform ivec2 _bSpriteTexRegionSize;
uniform ivec2 _bSpriteTexRegionIndex;
uniform ivec3 _bSpriteTexSize;

uniform mat4 _bView;
uniform mat4 _bProjection;
uniform sampler2D _bSpriteTexture;

void main()
{
    vec2 normalizedPos = (_bPosition + 1.0) / 2.0;
    vec2 position = vec2(_bSpritePosition + (_bSpriteSize * normalizedPos)) / vec2(_bViewPortSize);
    position = (position * 2) - 1;

    TextureCoords = (vec2(_bSpriteSize * _bSpriteTexRegionIndex) + vec2(_bTexCoords * _bSpriteTexRegionSize)) / _bSpriteTexSize.xy;
    TextureCoords.xy *= -1;
    gl_Position = vec4(position, 0, 1);
}