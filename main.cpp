#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main()
{

    //Setup our window via glfw
    glfwInit();
    //Targetting opengl 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Support for mac os x
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //Create the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Make the opengl context current for this window on the calling thread
    glfwMakeContextCurrent(window);

    //Load function pointers for opengl via glad (glfw provides the address of opengl functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Configure on window resize callback to update the gl viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    float vertices[] = {
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    //Setup a variables to hold the id of our VBO and VAOs
    unsigned int VBO, VAO, EBO;

    //Generate our VAO and VBO items
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind the VAO, so we can set/bind the vertex buffer to it
    glBindVertexArray(VAO);

    //Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //copy our vertex data into the buffer (note we are rendering a still image,
    //so we specify render type of static (since it wont change much)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Set up a pointer to our vertex attribute (the position data?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Set up a pointer to our vertex attribute (the position data?
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Now that our buffers are bound to the VAO (the vertex attribPointer call) we can unbind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Note, do NOT unbind the EBO buffer, as the VAO does keep track of the
    // EBO itself (unlike the VBO which grabs a pointer to the data and can work without the vbo)
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Additionally we can unbind the VAO to avoid accidently using it unintentionally
    glBindVertexArray(0);

    ShaderProgram shaderProgram("./shaders/vertex.vs", "./shaders/fragment.fs");


    while (!glfwWindowShouldClose(window))
    {

        //process input
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float v = (sin(timeValue) / 2.0f) + 0.5f;

        //Set all shader/rendering calls to now use the shader program
        shaderProgram.use();
        shaderProgram.setVector4f("ourColour", v, v, v, 1.0f);

        //Bind the VAO to handle the input data
        glBindVertexArray(VAO);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Swap back buffer to front output buffer
        glfwSwapBuffers(window);

        //poll for input events
        glfwPollEvents();
    }

    //free up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //Free up all resources
    glfwTerminate();
    return 0;
}

//processes input events against the window
void processInput(GLFWwindow *window)
{
    //If escape key pressed, flag the window for closure
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

//Callback for updating the gl viewport to match window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Tell opengl via glad the size of our viewport so it knows how to display data and coords
    glViewport(0, 0, width, height);
}

