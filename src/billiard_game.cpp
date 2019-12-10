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

    //Clean up and main loop
    glutCloseFunc (clean_up);
    glutMainLoop ();

    return 0;
}

// ~~~~~~~~~~ Main functioons ~~~~~~~~~~

void render_function () {
    // Reload points and colors 
    // --optional

    // Reset canvas
    glClear (GL_COLOR_BUFFER_BIT);
    glPointSize (5.f);

    // Draw stuff
    // @TODO

    glFlush ();
}

void program_init () {
    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
}

void normal_keyb_handler () {
    
}

void special_keyb_handler () {

}

void clean_up () {

}

// ~~~~~~~~~~ End of main functioons ~~~~~~~~~~
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
    glVertexAttribPointer (0, 3, GL_SHORT, GL_FALSE, 0, 0);
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
