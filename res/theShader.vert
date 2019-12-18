// Shader-ul de varfuri  
 #version 400


in vec4 in_Position;
in vec4 in_Color;

out vec4 gl_Position; 
out vec4 ex_Color;
 
uniform int trigOrNah;
uniform mat4 normalisation;
uniform mat4 farLeft, farRight;

void main(void)
{
    if (trigOrNah == 1) {
        gl_Position = farLeft * normalisation * farRight * in_Position;
        
    }
    else {
        gl_Position = farLeft * normalisation * farRight * in_Position;
    }
    ex_Color = in_Color;
} 
 