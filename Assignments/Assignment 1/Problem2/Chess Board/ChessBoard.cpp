#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLuint vbo, vao;
int main()
{
    float points[] = {
        -0.4f,0.4f,
        -0.3f,0.4f,
        -0.3f,0.3f,
        -0.4f,0.4f,
        -0.4f,0.3f,
        -0.3f,0.3f

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
    int j;
    Shader chessShader("C:/Users/Ramesh/Desktop/Shaders/chessVertexShader.txt","C:/Users/Ramesh/Desktop/Shaders/chessFragmentShader.txt");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /*Another approach: I commented the above two commands and print a square for
          each iteration of the while loop (so that the square made by the last while loop 
          remains on the screen). However, the resulting chess board flickered a lot..not
          sure why*/
        for (j = 0;j < 64;j++)
        {
            chessShader.setInt("times", j);
            chessShader.use();
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

