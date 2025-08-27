#include <iostream>
using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    // Verde chillón / neón
    FragColor = vec4(0.0, 1.0, 0.2, 1.0);
}
)";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "This parcial.com", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 800);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float size = 0.1f;
    GLfloat vertices[] = {
        -size,  size + 0.5f, 0.0f,
         size,  size + 0.5f, 0.0f,
        -size, -size + 0.5f, 0.0f,

         size,  size + 0.5f, 0.0f,
         size, -size + 0.5f, 0.0f,
        -size, -size + 0.5f, 0.0f,

        -size - 0.5f,  size - 0.5f, 0.0f,
         size - 0.5f,  size - 0.5f, 0.0f,
        -size - 0.5f, -size - 0.5f, 0.0f,

         size - 0.5f,  size - 0.5f, 0.0f,
         size - 0.5f, -size - 0.5f, 0.0f,
        -size - 0.5f, -size - 0.5f, 0.0f,

        -size + 0.5f,  size - 0.5f, 0.0f,
         size + 0.5f,  size - 0.5f, 0.0f,
        -size + 0.5f, -size - 0.5f, 0.0f,

         size + 0.5f,  size - 0.5f, 0.0f,
         size + 0.5f, -size - 0.5f, 0.0f,
        -size + 0.5f, -size - 0.5f, 0.0f,
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 18);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Liberar memoria
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}