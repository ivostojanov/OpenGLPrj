#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <string>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> combined_vertices;

    int number_of_rectangles = 6;
    float vertices_letter_i[] = {
        // X     Y      Z     R     G     B     T1    T2
        //back
        -0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f,//#1 duplicate
         0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f, 1.0f, 0.0f,
         0.5f,  1.0f, -0.5f, 0.0f, 0.2f, 0.8f, 1.0f, 1.0f,//#2 duplicate
         0.5f,  1.0f, -0.5f, 0.0f, 0.2f, 0.8f, 1.0f, 1.0f,//#2 duplicate
        -0.5f,  1.0f, -0.5f, 0.0f, 0.2f, 0.8f, 0.0f, 1.0f,
        -0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f, 0.0f, 0.0f,//#1 duplicate
        //front
        -0.5f, -1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 0.0f,//#1 duplicate
         0.5f, -1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 0.0f,
         0.5f,  1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 1.0f,//#2 duplicate
         0.5f,  1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 1.0f,//#2 duplicate
        -0.5f,  1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 1.0f,
        -0.5f, -1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 0.0f,//#1 duplicate
        //sides
        -0.5f,  1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 0.0f,//#1 duplicate
        -0.5f,  1.0f, -0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 1.0f,
        -0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 1.0f,//#2 duplicate
        -0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 1.0f,//#2 duplicate
        -0.5f, -1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 0.0f,
        -0.5f,  1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 0.0f,//#1 duplicate

         0.5f,  1.0f,  0.5f, 0.0f, 0.0f, 0.5f,  1.0f, 0.0f,//#1 duplicate
         0.5f,  1.0f, -0.5f, 0.0f, 0.0f, 0.5f,  1.0f, 1.0f,
         0.5f, -1.0f, -0.5f, 0.0f, 0.0f, 0.5f,  0.0f, 1.0f,//#2 duplicate
         0.5f, -1.0f, -0.5f, 0.0f, 0.0f, 0.5f,  0.0f, 1.0f,//#2 duplicate
         0.5f, -1.0f,  0.5f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f,
         0.5f,  1.0f,  0.5f, 0.0f, 0.0f, 0.5f,  1.0f, 0.0f,//#1 duplicate

         //bottom
        -0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 1.0f,//#1 duplicate
         0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 1.0f,
         0.5f, -1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 0.0f,//#2 duplicate
         0.5f, -1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  1.0f, 0.0f,//#2 duplicate
        -0.5f, -1.0f,  0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 0.0f,
        -0.5f, -1.0f, -0.5f, 0.0f, 0.2f, 0.8f,  0.0f, 1.0f,//#1 duplicate
        //top
        -0.5f,  1.0f, -0.5f, 0.0f, 0.0f, 0.8f,  0.0f, 1.0f,//#1 duplicate
         0.5f,  1.0f, -0.5f, 0.0f, 0.0f, 0.8f,  1.0f, 1.0f,
         0.5f,  1.0f,  0.5f, 0.0f, 0.0f, 0.8f,  1.0f, 0.0f,//#2 duplicate
         0.5f,  1.0f,  0.5f, 0.0f, 0.0f, 0.8f,  1.0f, 0.0f,//#2 duplicate
        -0.5f,  1.0f,  0.5f, 0.0f, 0.0f, 0.8f,  0.0f, 0.0f,
        -0.5f,  1.0f, -0.5f, 0.0f, 0.0f, 0.8f,  0.0f, 1.0f //#1 duplicate
    };

    std::vector<float> vertices_letter_o1;    

    float PI = glm::pi<float>();
    float base_angle = PI / 2 / 9;
    float angle = 0;

    //adding the letter o vertices
     
    float R, G, B;
    R = 48.0f/255.0f;
    G = 145.0f/255.0f;
    B = 206.0f/255.0f;

    float scaling = 1.0f;
    float lowerscaling = 0.60f;
     
    //upper part of O
    for (int i = 0; i < 36+1; i++) {
        float x = cos(angle);
        float y = sin(angle);
        float z = 0.1f;        

        vertices_letter_o1.push_back(x*scaling);
        vertices_letter_o1.push_back(y*scaling);
        vertices_letter_o1.push_back(z*scaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        vertices_letter_o1.push_back(x*scaling);
        vertices_letter_o1.push_back(y*scaling);
        vertices_letter_o1.push_back(z*(-1)*scaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        angle += base_angle;
    }
    
    //frontal mid section
    for (int i = 0; i < 36 + 1; i++) {
        float x = cos(angle);
        float y = sin(angle);
        float z = 0.1f;          

        vertices_letter_o1.push_back(x * scaling);
        vertices_letter_o1.push_back(y * scaling);
        vertices_letter_o1.push_back(z * scaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        vertices_letter_o1.push_back(x * lowerscaling);
        vertices_letter_o1.push_back(y * lowerscaling);
        vertices_letter_o1.push_back(z * lowerscaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        angle += base_angle;
    }
    
    //Lower part of the letter O
    for (int i = 0; i < 36 + 1; i++) {
        float x = cos(angle);
        float y = sin(angle);
        float z = 0.1f;        

        vertices_letter_o1.push_back(x * lowerscaling);
        vertices_letter_o1.push_back(y * lowerscaling);
        vertices_letter_o1.push_back(z * lowerscaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        vertices_letter_o1.push_back(x * lowerscaling);
        vertices_letter_o1.push_back(y * lowerscaling);
        vertices_letter_o1.push_back(z * (-1) * lowerscaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        angle += base_angle;
    }

    //back midsection of O
    for (int i = 0; i < 36 + 1; i++) {
        float x = cos(angle);
        float y = sin(angle);
        float z = 0.1f*(-1);

        vertices_letter_o1.push_back(x * scaling);
        vertices_letter_o1.push_back(y * scaling);
        vertices_letter_o1.push_back(z * scaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        vertices_letter_o1.push_back(x * lowerscaling);
        vertices_letter_o1.push_back(y * lowerscaling);
        vertices_letter_o1.push_back(z * lowerscaling);

        vertices_letter_o1.push_back(R);
        vertices_letter_o1.push_back(G);
        vertices_letter_o1.push_back(B);

        vertices_letter_o1.push_back(1.0f);
        vertices_letter_o1.push_back(1.0f);

        angle += base_angle;
    }

    //combining all the vertices together
    for (auto i = 0; i < number_of_rectangles * 6 * 8; i++) {
        combined_vertices.push_back(vertices_letter_i[i]);
    }    

    //adding the vertices from the letter_o
    for (int i = 0; i < vertices_letter_o1.size(); i += 1)
    {
        combined_vertices.push_back(vertices_letter_o1[i]);
    }

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(-2.0f,  0.0f, -7.0f),
        glm::vec3(-2.0f,  0.0f, -5.5f),
        glm::vec3(2.0f,  0.0f, -5.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * combined_vertices.size(), &combined_vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!     

        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // pass transformation matrices to the shader

        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));        

        
        // rendering the letter i
        glBindVertexArray(VAO);
        //for (unsigned int i = 0; i < 10; i++)
        
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[1]);
        float angle = 20.0f * 1;//fomely 1 was i
        model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, number_of_rectangles*6);

        //rendering the letter o
        glBindVertexArray(VAO);

        // calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[3]);
        angle = 20.0f * 1;//fomely 1 was i
        model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLE_STRIP, (number_of_rectangles * 6), vertices_letter_o1.size()/8);//drawing type, starting index, vertices count

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
void processInput(GLFWwindow* window)
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