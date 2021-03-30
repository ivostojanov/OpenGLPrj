#version 330 core
out vec4 FragColor;

in vec3 ourColor;

uniform vec4 uniformColor; // we set this variable in the OpenGL code

void main()
{       
    FragColor = uniformColor;
}
