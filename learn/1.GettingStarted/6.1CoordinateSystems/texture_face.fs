#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTextureCoord;



uniform sampler2D texture_container;
uniform sampler2D texture_face;

void main()
{
    FragColor = mix(texture(texture_container, ourTextureCoord), texture(texture_face, vec2(ourTextureCoord.x, ourTextureCoord.y)), 0.2);
}
