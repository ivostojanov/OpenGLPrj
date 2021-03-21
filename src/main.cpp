#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <vector>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
static const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(233.0f/255.0f, 192.0f/255.0f, 35.0f/255.0f, 1.0f);\n"
    "}\n\0";
static const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    //second fragment shader
    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);
    glCompileShader(fragmentShader2);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //Creating the second shader program
    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    std::vector<float> yellowvertices;
    std::vector<float> blackvertices;
    std::vector<float> yellowsmallvertices;
    std::vector<float> blacksmallvertices;
    std::vector<float> vertices;

    float const PI_OVER_4 = glm::quarter_pi<float>();
    float const PI = glm::pi<float>();

    // Starting angle is not 0, but PI/8
    float baseangle = 0; // 180/2=90/9=10/2=5 degrees
    float angle = 0; // we are starting at 0 degrees
    //int numberOfVertices = round((2 * PI) / baseangle) + 2;//number of vertices, 2 is added for the central vertex and the ending vertex duplicate
    // we are basically only tweaking the base angle

    //value for the scaling of the circle
    float scaling = 1.0f;

    //first adding the central vertex in coordinates(0,0,0)
    for (auto i = 0; i < 3; i++) {
        blackvertices.push_back(0.0f);
        yellowvertices.push_back(0.0f);
        yellowsmallvertices.push_back(0.0f);        
        blacksmallvertices.push_back(0.0f);        
    }

    //define the angles
    baseangle = PI/3;
    angle = baseangle;
    scaling = 0.80f;

    //yellow triangles
    for (auto i = 0; i < 3; i++) {              
        //calculating the first vertex
        float x = cos(angle)*scaling; //projection on the X axis
        float y = sin(angle)*scaling; //projection on the Y axis
        float z = 0.0f; //we are still dealing with 2D
                
        yellowvertices.push_back(x);//x
        yellowvertices.push_back(y);//y
        yellowvertices.push_back(z);//z  

        angle += baseangle;

        x = cos(angle)*scaling;
        y = sin(angle)*scaling;
        z = 0.0f;

        yellowvertices.push_back(x);
        yellowvertices.push_back(y);
        yellowvertices.push_back(z);

        yellowvertices.push_back(0.0f);
        yellowvertices.push_back(0.0f);
        yellowvertices.push_back(0.0f);

        angle += baseangle;
    }

    baseangle = PI / 2 / 9 / 2;
    angle = 0;
    scaling = 0.65f;

    //large black circle
    for (auto i = 0; i <= 2 * PI / baseangle; i++) {
        float x = cos(angle)*scaling;
        float y = sin(angle)*scaling;
        float z = 0.0f;

        blackvertices.push_back(x);
        blackvertices.push_back(y);
        blackvertices.push_back(z);

        angle += baseangle;
    }

    scaling = 0.20f;

    //yellow small circle 
    for (auto i = 0; i <= 2 * PI / baseangle; i++) {
        float x = cos(angle) * scaling;
        float y = sin(angle) * scaling;
        float z = 0.0f;

        yellowsmallvertices.push_back(x);
        yellowsmallvertices.push_back(y);
        yellowsmallvertices.push_back(z);

        angle += baseangle;
    }

    scaling = 0.13f;

    //yellow small circle 
    for (auto i = 0; i <= 2 * PI / baseangle; i++) {
        float x = cos(angle) * scaling;
        float y = sin(angle) * scaling;
        float z = 0.0f;

        blacksmallvertices.push_back(x);
        blacksmallvertices.push_back(y);
        blacksmallvertices.push_back(z);

        angle += baseangle;
    }

    //combining both inside and outside vertices    
    for (auto i = 0; i < blackvertices.size(); i++) {
        vertices.push_back(blackvertices[i]);
    }

    for (auto i = 0; i < yellowvertices.size(); i++) {
        vertices.push_back(yellowvertices[i]);
    }

    for (auto i = 0; i < yellowsmallvertices.size(); i++) {
        vertices.push_back(yellowsmallvertices[i]);
    }

    for (auto i = 0; i < blacksmallvertices.size(); i++) {
        vertices.push_back(blacksmallvertices[i]);
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_a), vertices_a, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(233.0f / 255.0f, 192.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLE_FAN, 0, blackvertices.size()/3);//0, outsidevertices.size()/3

        //white triangles        
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLE_FAN, blackvertices.size()/3, yellowvertices.size()/3);
        glDrawArrays(GL_TRIANGLE_FAN, (blackvertices.size()/3)+(yellowvertices.size()/3), yellowsmallvertices.size() / 3);

        glUseProgram(shaderProgram2);
        glDrawArrays(GL_TRIANGLE_FAN, (blackvertices.size() / 3) + (yellowvertices.size() / 3) + (yellowsmallvertices.size() / 3), (blacksmallvertices.size() / 3));

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

