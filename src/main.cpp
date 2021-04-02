#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <cstring>

#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <vector>
#include <iostream>


const std::string program_name = ("GLSL Shader class example");

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, program_name.c_str(), nullptr, nullptr);
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
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("../res/shaders/shader.vert",
                     "../res/shaders/shader.frag"
                     );


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    std::vector<float> vertices;
    std::vector<float> letter_o;
    std::vector<float> letter_o_inside;

    float letter_i[] = {
        // positions         // colors
        -0.60f,  0.5f, 0.0f,  // top left
        -0.60f, -0.5f, 0.0f, // bottom left
        -0.40f, 0.5f, 0.0f,  // top right
        -0.40f,-0.5f, 0.0f    // bottom right
    };

    for (auto i = 0; i < 4 * 3; i++) {
        vertices.push_back(letter_i[i]);
    }

    float PI = glm::pi<float>();
    float base_angle = PI / 2 / 9 / 2;
    float angle = 0;
    float number_of_vertices = (PI * 2)/base_angle;//using a 5 degrees angle
    float scaling = 0.55f;
    float offsetx = 0.3f;
    float offsety = 0.0f;

    for (auto i = 0; i < 3; i++) {
        if(i==0)
            letter_o.push_back(0.0f+offsetx);
        else
            letter_o.push_back(0.0f);
    }

    for (auto i = 0; i < number_of_vertices+1; i++) {
        float x = cos(angle) * scaling + offsetx;
        float y = sin(angle) * scaling + offsety;
        float z = 0.0f;

        letter_o.push_back(x);
        letter_o.push_back(y);
        letter_o.push_back(z);

        angle += base_angle;
    }

    angle = 0;
    scaling = 0.35f;
    for (auto i = 0; i < number_of_vertices+1; i++) {
        float x = cos(angle) * scaling + offsetx;
        float y = sin(angle) * scaling + offsety;
        float z = 0.0f;

        letter_o_inside.push_back(x);
        letter_o_inside.push_back(y);
        letter_o_inside.push_back(z);

        angle += base_angle;
    }

    //transfering all the vertices to the vertices list
    for (auto i = 0; i < letter_o.size(); i++) {
        vertices.push_back(letter_o[i]);
    }

    for (auto i = 0; i < letter_o_inside.size(); i++) {
        vertices.push_back(letter_o_inside[i]);
    }

    //transfering all

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(VAO);

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
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //setting the uniform color via code
        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "uniformColor");//setting the global uniform value of the fragment shader
        ourShader.use();
        glBindVertexArray(VAO);

        glUniform4f(vertexColorLocation, 18.8f/255.0f, 15.7f/255.0f, 55.6f/255.0f, 1.0f);//setting the color of our logo to red        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //drawing the blue part of the letter o        
        glUniform4f(vertexColorLocation, 8.0f / 255.0f, 59.4f / 255.0f, 91.9f / 255.0f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 4, (letter_o.size()) / 3);

        //drawing a white circle inside of our blue circle
        glUniform4f(vertexColorLocation, 1.0f, 1.0f , 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 4+(letter_o.size()/3), (letter_o_inside.size()) / 3);


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

