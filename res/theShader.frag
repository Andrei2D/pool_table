
// Shader-ul de fragment / Fragment shader  
 
 #version 400

in vec4 ex_Color;
out vec4 out_Color;

vec4 rgb_to_ogl = ex_Color;

void main(void)
{
    rgb_to_ogl.r = rgb_to_ogl.r / 255;
    rgb_to_ogl.g = rgb_to_ogl.g / 255;
    rgb_to_ogl.b = rgb_to_ogl.b / 255;
    out_Color = rgb_to_ogl;
}
 