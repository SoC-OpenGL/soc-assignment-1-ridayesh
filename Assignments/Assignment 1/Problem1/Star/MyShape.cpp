#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLuint vbo,vao;

int main()
{
    float points[] = {
        0.0f,0.0f,
        0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,
        -0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,
        0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,
        -0.6f/3.0,0.6 / tan(M_PI * 36.0 / 180.0)/3.0,
        0.0f,(0.6 / tan(M_PI * 36.0 / 180.0) / 3.0)+(0.6*tan(M_PI*72.0/180.0)/3.0)
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
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    int j = 0;
    Shader starShader("C:/Users/Ramesh/Desktop/Shaders/StarShaderVs.txt", "C:/Users/Ramesh/Desktop/Shaders/StarShaderFs.txt");
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        for (j = 0;j <= 4;j++)
        {
            starShader.setInt("times", j);
            starShader.use();
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

