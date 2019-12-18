#include "billiard_game.hpp"

auto out_vert = [](int offset) {
    float* point = vertices + 3 * offset;
    std :: cout << "(" << point[0] << " " << point[1] << " "
            << point[2] << ")\n";
};

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

    // Get ball data
    pthread_mutex_lock (&ball_mtx);
    Ball localBall[2];
    localBall[0] = ball[0];
    localBall[1] = ball[1];
    pthread_mutex_unlock (&ball_mtx);

    glm::mat4 aftNorm(1.f), b4Norm(1.f);
    sendIntToShader (0, "my_color");
    sendVec3ToShader (white_color, "custom_color");

    // Draw background
    sendMat4ToShader (aftNorm, "farLeft");
    sendMat4ToShader (b4Norm, "farRight");
    glDrawArrays (GL_POINTS, 0, 12);
    glDrawArrays (GL_TRIANGLES, 0, 12);


    for (int ind = 0; ind < nr_of_balls; ind ++) {
        // Set balls colors
        sendIntToShader (1, "my_color");
        if (ind == curr_ball) {
            sendVec3ToShader (blue_color, "custom_color");
        }
        else {
            sendVec3ToShader (yellow_color, "custom_color");
        }

        // Balls
        b4Norm = glm::translate (glm::mat4(1.f), 
            glm::vec3(localBall[ind].x, localBall[ind].y, 0));
        sendMat4ToShader (b4Norm, "farRight");
        glDrawArrays (GL_POLYGON, c_qual_offs, c_qual_size);
    }

    glFlush ();
}

void program_init () {
    // Creations
    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
    create_vbo ();
    create_shaders ();

    // Points creation
    init_background_p ();
    init_circle (c_cen_offs, c_qual_size, BALL_RADIUS);
    
    // Normalisation matrix sending
    axis_mat = glm::translate (axis_mat, glm::vec3 (-1, 1, 0));
    axis_mat = glm::scale (axis_mat, 
        glm::vec3(2/float(X_MAX - X_MIN), -2/float(Y_MAX - Y_MIN), 2/float(Z_MAX - Z_MIN)));
    axis_mat = glm::translate (axis_mat, glm::vec3 (1,1,0));
    sendMat4ToShader (axis_mat, "normalisation");

    // Timer
    update_clock = std::clock ();

    // Update thread
    pthread_create (&ball_th, NULL, ball_update_th, NULL);
    
}

void normal_keyb_handler (u_char key, int xx, int yy) {
    
    switch (key) {
        case '0': {
            pthread_mutex_lock (&ball_mtx);
            ball[curr_ball].act_on (2.5);
            pthread_mutex_unlock (&ball_mtx);
            break;
        }
        case '.': {
            curr_ball = (curr_ball + 1) % 2; 
            break;
        }
        case '7': {
            pthread_mutex_lock (&ball_mtx);
            ball[curr_ball].rotate_ccw ();
            std :: cout << (ball[0].alfa / (2 * PI)) * 360 << "\t" << std::flush;
            std :: cout << (ball[1].alfa / (2 * PI)) * 360 << "\n" << std::flush;
            pthread_mutex_unlock (&ball_mtx);
            break;
        }
        case '9': {
            pthread_mutex_lock (&ball_mtx);
            ball[curr_ball].rotate_cw ();
            std :: cout << (ball[0].alfa / (2 * PI)) * 360 << "\t" << std::flush;
            std :: cout << (ball[1].alfa / (2 * PI)) * 360 << "\n" << std::flush;
            pthread_mutex_unlock (&ball_mtx);
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

void init_circle (int offset, int quality, float radius) {

    double measure = (2*PI) / quality, angle = 0;
    float* vertex = vertices + (3 * offset);
    vertex[0] = 0;
    vertex[1] = 0;
    vertex[2] = Z_FG;
    vertex += 3;
    
    for (int ind = 0; ind < quality; ind ++) {
        vertex[0] = cos (angle) * radius;
        vertex[1] = sin (angle) * radius;
        vertex[2] = Z_FG;

        vertex += 3;
        angle += measure;
    }
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
}


void set_color_at_offs (uint offset, glm::vec3 color) {
    offset *= 3;

    colors[offset +0] = color.x;
    colors[offset +1] = color.y;
    colors[offset +2] = color.z;
}

void move_point (int pointOffs, int x, int y) {
    pointOffs *= 3;
    vertices[pointOffs] += x;
    vertices[pointOffs + 1] += y;
}


bool timer (clock_t& last_clock, uint durr_msec) {
    clock_t curr_clk = std::clock ();
    uint time_passed = (curr_clk - last_clock) / float(CLOCKS_PER_SEC);
    time_passed *= 1000;

    // Passed more that it should have waited
    if (time_passed >= durr_msec) {
        last_clock = curr_clk;
        return true;
    }
    return false;
}

void* ball_update_th(void* nothing) {

    // Ball
    glm::vec3 board_top = get_point_at_offs (bg_i_offs);
    glm::vec3 board_bot = board_top;

    board_bot.x += TABL_I_WIDTH;
    board_bot.y += TABL_I_HEIGHT;
    
    glm::vec3 board_mid ((board_top.x + board_bot.x) / 2, 
        (board_top.y + board_bot.y) / 2, Z_FG);
    
    ball[0].set (board_mid.x,board_mid.y, BALL_RADIUS);
    ball[1].set (board_mid.x, board_mid.y, BALL_RADIUS);
    ball[0].set_limits (board_top.x, board_top.y, board_bot.x, board_bot.y);
    ball[1].set_limits (board_top.x, board_top.y, board_bot.x, board_bot.y);

    while (true) {
        usleep (Ball::update_rate_ms * 1000);
        pthread_mutex_lock (&ball_mtx);
        ball[0].update ();
        ball[1].update ();
        pthread_mutex_unlock (&ball_mtx);
    }

}