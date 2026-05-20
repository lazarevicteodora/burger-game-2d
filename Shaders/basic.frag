#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec4 uColor;
uniform vec3 uTint;
uniform int uUseTexture;
uniform float uAlpha;

void main()
{
    if (uUseTexture == 1) {
        vec4 texColor = texture(uTexture, TexCoord);
        FragColor = texColor * vec4(uTint, 1.0);
        FragColor.a *= uAlpha;
    } else {
        FragColor = uColor;
        FragColor.a *= uAlpha;
    }
}