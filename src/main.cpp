#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <cstring>

#include <vector>


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
    std::vector<float> circle;

    float PI = glm::pi<float>();
    float base_angle = PI / 2 / 9 / 2 / 5;
    float angle = 0;
    float number_of_vertices = (PI * 2) / base_angle;//using a 5 degrees angle
    float scaling = 0.8f;

    for (auto i = 0; i < 3; i++) {
        circle.push_back(0.0f);
    }

    for (auto i = 0; i < 3; i++) {
        circle.push_back(0.0f);
    }

    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;

    float sixty_degrees = (PI / 3);
    float thirty_degrees = sixty_degrees / 2;    

    //calculating vertices for the circle
    for (auto i = 0; i < number_of_vertices + 1; i++) {
        float x = cos(angle) * scaling;
        float y = sin(angle) * scaling;
        float z = 0.0f;

        //positions
        circle.push_back(x);
        circle.push_back(y);
        circle.push_back(z);
                
        if (angle <= sixty_degrees) {            
            red = 1.0f;
            green = angle/sixty_degrees;
            blue = 0.0f;
        }
        else if (angle <= sixty_degrees * 2) {
            red = 1.0f-((angle-sixty_degrees) / sixty_degrees);
            green = 1.0f;
            blue = 0.0f;
        }
        else if (angle <= sixty_degrees * 3) {
            red = 0.0f;
            green = 1.0f;
            blue = (angle-(sixty_degrees*2))/sixty_degrees;
        }
        else if (angle <= sixty_degrees * 4) {
            red = 0.0f;
            green = 1.0f - ((angle - sixty_degrees*3) / sixty_degrees);
            blue = 1.0f;
        }
        else if (angle <= sixty_degrees * 5) {
            red = (angle - (sixty_degrees * 4)) / sixty_degrees;;
            green = 0.0f;
            blue = 1.0f;
        }
        else if (angle <= sixty_degrees * 6) {
            red = 1.0f;
            green = 0.0f;
            blue = 1.0f - ((angle - sixty_degrees*5) / sixty_degrees);
        }

        //colors
        circle.push_back(red);
        circle.push_back(green);
        circle.push_back(blue);

        if (i % 2 == 0) {
            circle.push_back(0.0f);
            circle.push_back(0.0f);
            circle.push_back(0.0f);

            circle.push_back(green);
            circle.push_back(red);
            circle.push_back(blue);
        }

        angle += base_angle;
    }

    //combining all the arrays/lists into vertices
    for (auto i = 0; i < circle.size(); i++) {
        vertices.push_back(circle[i]);
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(VAO);


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

        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size()/6);

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

