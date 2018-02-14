#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColour;\n"
    "void main()\n"
    "{\n"
    "   FragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


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

    //setup our vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Load in the vertex shader source code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR - failed to compile vertex shader -> " << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR - failed to compile fragment shader -> " << infoLog << std::endl;
    }

    //Setup our shader program attach the compiled shaders and link it together
    unsigned int shaderProgram  = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error - failed to link shaders -> " << infoLog << std::endl;
    }

    //Note, we can now free the actual shaders since they are bundled in to the shaderProgram
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    //Setup a variables to hold the id of our VBO and VAOs
    unsigned int VBO, VAO;

    //Generate our VAO and VBO items
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Bind the VAO, so we can set/bind the vertex buffer to it
    glBindVertexArray(VAO);

    //Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //copy our vertex data into the buffer (note we are rendering a still image,
    //so we specify render type of static (since it wont change much)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set up a pointer to our vertex attribute (the position data?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //enable it ?
    glEnableVertexAttribArray(0);

    //Now that our buffers are bound to the VAO (the vertex attribPointer call) we can unbind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Additionally we can unbind the VAO to avoid accidently using it unintentionally
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {

        //process input
        processInput(window);

        glClearColor(0.5f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //Set all shader/rendering calls to now use the shader program
        glUseProgram(shaderProgram);
        //Bind the VAO to handle the input data
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Swap back buffer to front output buffer
        glfwSwapBuffers(window);

        //poll for input events
        glfwPollEvents();
    }

    //free up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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