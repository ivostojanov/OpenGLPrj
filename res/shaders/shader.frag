#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

vec4 white_square = vec4(1.0f, 1.0f, 1.0f, 1.0f);
vec4 black_square = vec4(0.0f, 0.0f, 0.0f, 0.0f);

int grid = 4;

void main()
{
    float offset = 1.0f/grid;
    for(int i=0; i<grid; i+=1){
        for(int f=0; f<grid; f+=1){
            if(TexCoord.y>=i*offset && TexCoord.y<=((i+1)*offset) && i%2==0){
                if(TexCoord.x>=f*offset && TexCoord.x<=((f+1)*offset) && f%2==0){
                    FragColor=white_square;
                    break;
                }else if(TexCoord.x>=f*offset && TexCoord.x<=((f+1)*offset) && f%2!=0){
                    FragColor=black_square;  
                    break;
                }
            }else if(TexCoord.y>=i*offset && TexCoord.y<=((i+1)*offset) && i%2!=0){
                if(TexCoord.x>=f*offset && TexCoord.x<=((f+1)*offset) && f%2==0){
                    FragColor=black_square;
                    break;
                }else if(TexCoord.x>=f*offset && TexCoord.x<=((f+1)*offset) && f%2!=0){
                    FragColor=white_square;  
                    break;
                }
            }
        }
    }
    /*
    if(TexCoord.x>=i*offset && TexCoord.x<=((i+1)*offset) && i%2==0){
                    FragColor=black_square;
                    break;
                }else{
                    FragColor=white_square;
                }
                */

    /*if(TexCoord.x<=0.5f){
        if(TexCoord.y<=0.5f){
            FragColor=white_square;
        }else{
            FragColor=black_square;
        }
    }else if(TexCoord.x>=0.5f){
        if(TexCoord.y<=0.5f){
            FragColor=black_square;
        }else{
            FragColor=white_square;
        }
    }*/

    //FragColor = texture(texture1, TexCoord);
}
