#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <string>

const std::string program_name = ("Pac-Man Movement");

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

glm::mat4 transform = glm::mat4(1.0f);

std::string pacman_direction = "right";
float speed = 0.5f;
float rotation_angle = 0.0f;

float delta_time = 0.0f;
float previous_frame = glfwGetTime();


int main() {
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
    Shader ourShader("../res/shaders/shader.vert","../res/shaders/shader.frag");

  // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

  std::vector<float> vertices;

  float const PI_OVER_4 = glm::quarter_pi<float>();
  float const PI = glm::pi<float>();

  // Starting angle is not 0, but PI/8
  float base_angle = PI/2.0f/9.0f/2.0f;
  float angle = 3*base_angle;


  for (auto i = 0; i < 3; i++)
      vertices.push_back(0.0f);

  float scale = 0.25f;
  for (auto i = 0; i < (2*PI/base_angle)-5; i++) {
      vertices.push_back(glm::cos(angle)*scale);
      vertices.push_back(glm::sin(angle)*scale);
      vertices.push_back(0.0f);
      angle += base_angle;
  }

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

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
  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render container
    ourShader.use();
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLE_FAN, 0, (vertices.size()/3)-1);
        
    //calculating delta time
    float current_time = glfwGetTime();
    delta_time = current_time - previous_frame;
    previous_frame = current_time; 

    // create transformations    
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
    //rotation transformation to our pacman character
    if (pacman_direction == "right") {
        rotation_angle = 0.0f;
        direction = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else if (pacman_direction == "left") {        
        rotation_angle = 180.0f;
        direction = glm::vec3(-1.0f, 0.0f, 0.0f);
    }
    else if (pacman_direction == "down") {
        rotation_angle = -90.0f;
        direction = glm::vec3(0.0f, -1.0f, 0.0f);
    }
    else if (pacman_direction == "up") {        
        rotation_angle = 90.0f;
        direction = glm::vec3(0.0f, 1.0f, 0.0f);
    }   

    // calculate the model matrix for each object and pass it to shader before drawing        
    transform = glm::translate(transform, direction*delta_time*speed);    
        
    //then applying the rotation            
    glm::mat4 model = glm::rotate(transform, glm::radians(rotation_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    
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

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  //inputs for the pacman character movement
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      pacman_direction = "up";
  else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      pacman_direction = "down";
  else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      pacman_direction = "left";
  else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      pacman_direction = "right";
  else
      pacman_direction = "none";
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
