
// Shader-ul de fragment / Fragment shader  
 
 #version 400

in vec4 ex_Color;
out vec4 out_Color;

uniform int my_color;
uniform vec3 custom_color;

void main(void)
{

    if (my_color == 1) {
    out_Color.r = custom_color.r / 255;
    out_Color.g = custom_color.g / 255;
    out_Color.b = custom_color.b / 255;

    }
    else {   
    out_Color.r = ex_Color.r / 255;
    out_Color.g = ex_Color.g / 255;
    out_Color.b = ex_Color.b / 255;
    }
}
 