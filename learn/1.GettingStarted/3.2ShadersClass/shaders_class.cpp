#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.h"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
    // 位置              // 颜色
     -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右上
     0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左上
     0.0f,  -0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};



static constexpr int  WINDOW_WITH = 800;
static constexpr int WINDOW_HEGHT  = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WITH, WINDOW_HEGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
         std::cout << "Failed to initialize GLAD" << std::endl;
         return -1;
    }

    Shader our_sharder("shaders.vs", "shaders.fs");

    // 1. 绑定VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    // 3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

   
    // 渲染循环
    while(!glfwWindowShouldClose(window))
    {
         // 输入
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      
        glClear(GL_COLOR_BUFFER_BIT);

        

        float timeValue = glfwGetTime();
        float value = sin(timeValue);
        float absValue = std::abs(value);


        vertices[8] = absValue;
        vertices[15] = absValue;
        vertices[3] = absValue;
        vertices[10] = absValue;
        vertices[17] = absValue;
        
        our_sharder.use();
        glBindVertexArray(VAO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW ); 
        our_sharder.setFloat("xOffset", value);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        

       
        // 检查并调用事件，交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
    return 0;
}