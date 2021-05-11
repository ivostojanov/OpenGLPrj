#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

vec4 checkers(vec2 uv){
    float xOffset = step(fract(uv.y), 0.5) * 0.5;
    float color = step(fract(uv.x + xOffset), 0.5);
    return vec4(color, color, color, 1.0f);
}

void main()
{
    float grid = 4.0f;
    vec2 uv = TexCoord.xy / vec2(1.0f, 1.0f)*(grid/2.0f);
    FragColor = checkers(uv);
}
