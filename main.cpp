#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    //Display loop, iterate until instructed to close
    while (!glfwWindowShouldClose(window))
    {

        //process input
        processInput(window);

        glClearColor(0.5f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Swap back buffer to front output buffer
        glfwSwapBuffers(window);

        //poll for input events
        glfwPollEvents();
    }

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