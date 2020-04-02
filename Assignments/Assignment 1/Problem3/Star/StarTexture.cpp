#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stb-master\stb_image.h>

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLuint vbo, vao, texture;
int height, width, ColourChannel;

int main()
{
    float points[] = {
        0.0f,0.0f,0.0f,0.5f,
        0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,0.5f,1.0f,
        -0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,0.5f,0.0f,
        0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,0.5f,1.0f,
        -0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,0.5f,0.0f,
        0.0f,(0.6 / tan(M_PI * 36.0 / 180.0) / 3.0)+(0.6*tan(M_PI*72.0/180.0)/3.0),1.0f,0.5f
    };
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "First Success", NULL, NULL);
    if (window == NULL)
    {
        cout << "FAILED TO CREATE WINDOW";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "FAILED TO INITIALIZE GLAD";
    }
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    unsigned char* data = stbi_load("C:/Users/Ramesh/Desktop/Gold.jpg", &width, &height, &ColourChannel, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    int j = 0;
    Shader starShader("C:/Users/Ramesh/Desktop/Shaders/StarTextureVs.txt", "C:/Users/Ramesh/Desktop/Shaders/StarTextureFs.txt");
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        for (j = 0;j <= 4;j++)
        {
            starShader.setInt("times", j);
            starShader.use();
            glBindTexture(GL_TEXTURE_2D,texture);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

