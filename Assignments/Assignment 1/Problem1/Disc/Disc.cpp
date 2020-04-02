#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLuint vbo, vao, shaderprogram, vs, fs;
//const float PI = 3.14159265358979f;
const char* vertexShaderSource = "#version 430 core\n"
"layout (location = 0) in vec2 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 430 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



int main()
{
    float points[204];
    int j = 0;
    points[0] = 0.0f;
    points[1] = 0.0f;
    for (int i = 2;i <= 200;i += 2)
    {
        points[i] = cos(3.6 * M_PI * j / 180.0) / 2;
        points[i + 1] = sin(3.6 * M_PI * j / 180.0) / 2;
        j++;
    }
    points[202] = points[2];
    points[203] = points[3];
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
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    glCompileShader(vs);
    glCompileShader(fs);
    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vs);
    glAttachShader(shaderprogram, fs);
    glLinkProgram(shaderprogram);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.96f, 0.929f, 0.0275f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderprogram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 102);
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

