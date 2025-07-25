#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor; //向片段着色器输出一个颜色
uniform float xOffset;

void main()
{
    gl_Position  = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0); //将ourColor设置为我们从顶点数据那里得到的输入颜色
    ourColor    = aColor;
}