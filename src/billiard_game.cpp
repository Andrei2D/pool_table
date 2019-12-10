#include "billiard_game.hpp"

int main(int argc, char** argv)
{
    // Glut init function
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (250, 0);
    glutInitWindowSize (WIND_WIDTH, WIND_HEIGHT);
    glutCreateWindow (WIND_TITLE);

    //Init funtions. Glew's and program's own
    glewInit ();
    program_init ();

    // Render related initialisations
    glutDisplayFunc (render_function);
    glutIdleFunc (render_function);

    // Keboard related initialisation
    glutKeyboardFunc (normal_keyb_handler);
    glutSpecialFunc (special_keyb_handler);

    //Clean up and main loop
    glutCloseFunc (clean_up);
    glutMainLoop ();

    return 0;
}

// ~~~~~~~~~~ Main functioons ~~~~~~~~~~

void render_function () {
    // Reload points and colors 
    create_vbo ();

    // Reset canvas
    glClear (GL_COLOR_BUFFER_BIT);
    glPointSize (10.f);

    // Draw stuff
    // @TODO
    
    glDrawArrays (GL_POINTS, 0, 12);
    glDrawArrays (GL_TRIANGLES, 0, 12);
    glDrawArrays (GL_POLYGON, c_qual_offs, c_qual_size);

    glFlush ();
}

void program_init () {
    // Creations
    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
    create_vbo ();
    create_shaders ();

    // Points creation
    init_background_p ();
    
    // Normalisation matrix sending
    axis_mat = glm::translate (axis_mat, glm::vec3 (-1, 1, 0));
    axis_mat = glm::scale (axis_mat, 
        glm::vec3(2/float(X_MAX - X_MIN), -2/float(Y_MAX - Y_MIN), 2/float(Z_MAX - Z_MIN)));
    axis_mat = glm::translate (axis_mat, glm::vec3 (1,1,0));
    sendMat4ToShader (axis_mat, "normalisation");

    // Ball
    ball.set (vertices + 3 * c_cen_offs, BALL_RADIUS);
    ball.draw (vertices + 3 * c_cen_offs, c_qual_size, 5);

    for (int ind = c_cen_offs; ind < c_cen_offs + c_cen_size + c_qual_size; ind ++) {
        float* point = vertices + 3 * ind;
        if ((ulong)point > (ulong)(vertices + sizeof(vertices))) {
            std::cout<< "wtf\n";
            continue;
        }
        std :: cout << point[0] << " " << point[1] << " "
            << point[2] << "\n"; 
    }
    
}

void normal_keyb_handler (u_char key, int xx, int yy) {
    
    switch (key) {
        case '5': {
            int offset = 0;
            move_point (offset, 0, 10);
            break;
        }
        case '2': {
            int offset = 0;
            move_point (offset, 0, -10);
            break;
        }
        case '1': {
            int offset = 0;
            move_point (offset, -10, 0);
            break;
        }
        case '3': {
            int offset = 0;
            move_point (offset, 10, 0);
            break;
        }

    }
}

void special_keyb_handler (int key, int xx, int yy) {

}

void clean_up () {
    destroy_vbo ();
}

// ~~~~~~~~~ Other functions ~~~~~~~~~~~

void create_vbo () {
    // Vertex buffer
    glGenBuffers (1, &VBO_ID);
    glBindBuffer (GL_ARRAY_BUFFER, VBO_ID);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Color buffer
    glGenBuffers (1, &COL_BUF_ID);
    glBindBuffer (GL_ARRAY_BUFFER, COL_BUF_ID);
    glBufferData (GL_ARRAY_BUFFER, sizeof (colors), colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 3, GL_SHORT, GL_FALSE, 0, 0);
}

void destroy_vbo () {
    glDisableVertexAttribArray (1);
    glDisableVertexAttribArray (0);

    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glDeleteBuffers (1, &COL_BUF_ID);
    glDeleteBuffers (1, &VBO_ID);

}

void create_shaders () {
    PROG_ID = LoadShaders("./res/theShader.vert", "./res/theShader.frag");
    glUseProgram(PROG_ID);
}

void init_background_p () {

    set_point_at_offs (bg_o_offs + 0, 
        glm::vec3 (TABL_X_OFFS, TABL_Y_OFFS, 1));
    set_point_at_offs (bg_o_offs + 1, 
        glm::vec3 (TABL_X_OFFS, TABL_Y_OFFS + TABL_O_HEIGHT, 1));
    set_point_at_offs (bg_o_offs + 2, 
        glm::vec3 (TABL_X_OFFS + TABL_O_WIDTH, TABL_Y_OFFS + TABL_O_HEIGHT, 1));

    set_point_at_offs (bg_o_offs + 3, 
        glm::vec3 (TABL_X_OFFS, TABL_Y_OFFS, 1));
    set_point_at_offs (bg_o_offs + 4, 
        glm::vec3 (TABL_X_OFFS + TABL_O_WIDTH, TABL_Y_OFFS + TABL_O_HEIGHT, 1));
    set_point_at_offs (bg_o_offs + 5, 
        glm::vec3 (TABL_X_OFFS + TABL_O_WIDTH, TABL_Y_OFFS, 1));
    
    int xoffs = TABL_X_OFFS + TABL_MARG, yoffs = TABL_Y_OFFS + TABL_MARG;
    set_point_at_offs (bg_i_offs + 0, 
        glm::vec3 (xoffs, 
        yoffs, 2));
    set_point_at_offs (bg_i_offs + 1, 
        glm::vec3 (xoffs, 
        yoffs + TABL_I_HEIGHT, 2));
    set_point_at_offs (bg_i_offs + 2, 
        glm::vec3 (xoffs + TABL_I_WIDTH, 
        yoffs + TABL_I_HEIGHT, 2));

    set_point_at_offs (bg_i_offs + 3, 
        glm::vec3 (xoffs, 
        yoffs, 2));
    set_point_at_offs (bg_i_offs + 4, 
        glm::vec3 (xoffs + TABL_I_WIDTH, 
        yoffs + TABL_I_HEIGHT, 2));
    set_point_at_offs (bg_i_offs + 5, 
        glm::vec3 (xoffs + TABL_I_WIDTH, 
        yoffs, 2));
}


// ~~~~ Fragment sending functions ~~~~~~

void sendIntToShader (int value, char* varName)
{
    int varLocation = glGetUniformLocation(PROG_ID, varName);
	glUniform1i(varLocation, value);
}

void sendMat4ToShader (glm::mat4 matrix, char* varName)
{
    int varLocation = glGetUniformLocation (PROG_ID, varName);
    glProgramUniformMatrix4fv (PROG_ID, varLocation, 1, 
                                GL_FALSE, glm::value_ptr (matrix));
}


void sendVec3ToShader (glm::vec3 vect, char* varName)
{
    int varLocation = glGetUniformLocation (PROG_ID, varName);
    glUniform3fv (varLocation, 1, glm::value_ptr (vect));
}

void sendVec4ToShader (glm::vec4 vect, char* varName)
{
    int varLocation = glGetUniformLocation (PROG_ID, varName);
    glUniform4fv (varLocation, 1, glm::value_ptr (vect));
}

// ~~~~~~~~~~ Useful functions ~~~~~
glm::vec3 get_point_at_offs (uint offset) {
    offset *= 3;
    glm::vec3 point (vertices[offset], 
        vertices[offset + 1], 
        vertices[offset + 2]);
    return point;
}

void set_point_at_offs (uint offset, glm::vec3 point) {
    offset *= 3;

    vertices[offset] = point.x;
    vertices[offset +1] = point.y;
    vertices[offset +2] = point.z;

    // std :: cout << offset/3 << "\t (" << point.x 
    //     << " " << point.y << " " << point.z << ")\n";
}

void move_point (int pointOffs, int x, int y) {
    pointOffs *= 3;
    vertices[pointOffs] += x;
    vertices[pointOffs + 1] += y;
}