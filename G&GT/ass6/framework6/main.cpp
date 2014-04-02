/* Computer Graphics and Game Technology, Assignment Box2D game
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <cstdio>

#include <GL/gl.h>
#include <GL/glut.h>
#include <Box2D/Box2D.h>

#include "levels.h"

unsigned int reso_x = 800, reso_y = 600; // Window size in pixels
const float world_x = 8.f, world_y = 6.f; // Level (world) size in meters
double twoPI = 2.0 * 3.14159; // Two PI.
int last_time, frame_count;

int reset = 0;
int player_index = 0;
int circle_triangles = 32; // Number of triangles in the ball.

b2Vec2 *player_poly = new b2Vec2[4]; // Create array for player interaction.


// Information about the levels loaded from files will be available in these.
unsigned int num_levels, level_num;
level_t *levels;
const b2Vec2 gravity(0, -9.81);
b2World *world;
b2Body *body, *ball;

/*
 * Load a given world, i.e. read the world from the `levels' data structure and
 * convert it into a Box2D world.
 */
void load_world(unsigned int level)
{
    if (level >= num_levels){
        // Note that level is unsigned but we still use %d so -1 is shown as
        // such.
        printf("Warning: level %u does not exist.\n", level);
        return;
    }

    /*
     * Create Ball with ball shape and ball fixture contained in body.
     */

    b2BodyDef ballBody;
    b2CircleShape ballShape;
    b2FixtureDef ballFixture;

    ballBody.type = b2_dynamicBody;
    ballBody.position.Set(levels[level].start.x, levels[level].start.y);
    ballBody.angle = 0;

    ballShape.m_p.Set(0, 0);
    ballShape.m_radius = 0.1;

    ballFixture.shape = &ballShape;
    ballFixture.density = 1;

    ball = world->CreateBody(&ballBody);
    ball->CreateFixture(&ballFixture);

    // Create a Box2D world and populate it with all bodies for this level
    // (including the ball).
    unsigned int poly_index, vert_index, verts;
    b2PolygonShape *polygonShapes = new b2PolygonShape[levels[level].num_polygons];
    b2BodyDef *polyBodyDefs = new b2BodyDef[levels[level].num_polygons];
    b2FixtureDef *fixtureDefs = new b2FixtureDef[levels[level].num_polygons];

    for(poly_index = 0; poly_index < levels[level].num_polygons; poly_index++){
        verts = levels[level].polygons[poly_index].num_verts;
        b2Vec2 *vertices = new b2Vec2[verts];
        for(vert_index = 0; vert_index < verts; vert_index++){
            vertices[vert_index] = b2Vec2(levels[level].polygons[poly_index].verts[vert_index].x,
                                          levels[level].polygons[poly_index].verts[vert_index].y);
        }
        polygonShapes[poly_index].Set(vertices, verts);
        if(levels[level].polygons[poly_index].is_dynamic){
            polyBodyDefs[poly_index].type = b2_dynamicBody;
        }else{
            polyBodyDefs[poly_index].type = b2_staticBody;
        }
        polyBodyDefs[poly_index].position.Set(levels[level].polygons[poly_index].position.x,
                                          levels[level].polygons[poly_index].position.y);
        polyBodyDefs[poly_index].angle = 0;
        
        fixtureDefs[poly_index].shape = &polygonShapes[poly_index];
        fixtureDefs[poly_index].density = 1;
        body = world->CreateBody(&polyBodyDefs[poly_index]);
        body->CreateFixture(&fixtureDefs[poly_index]);
    }
}


/*
 * Called when we should redraw the scene (i.e. every frame).
 * It will show the current framerate in the window title.
 */
void draw(void)
{
    int time, frametime, i;
    double  x, y, r;
    time = glutGet(GLUT_ELAPSED_TIME);
    frametime = time - last_time;

    b2Body *poly = world->GetBodyList();
    b2Fixture *fixture;
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // Do any logic and drawing here.
    //
    world->Step(1/60.0, 1, 1);

    if(reset > 0){
        ball->SetLinearVelocity(b2Vec2(0, 0));
        ball->SetTransform(b2Vec2(levels[level_num].start.x,
                                  levels[level_num].start.y),body->GetAngle());
        reset = 0;
    }

    if(b2Distance(ball->GetPosition(), b2Vec2(levels[level_num].end.x,
                                              levels[level_num].end.y)) <= r + 0.1){
        world = new b2World(gravity);
        load_world(++level_num);
    }
    
    while(poly){
        fixture = poly->GetFixtureList();
        /* Circle, this is the ball only. */
        if(fixture->GetShape()->GetType() == 0){
            x = poly->GetPosition().x;
            y = poly->GetPosition().y;
            r = poly->GetFixtureList()[0].GetShape()->m_radius;

            glColor3f(1, 1, 1);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y);
            for (i = 0; i <= circle_triangles; i++) {
                glVertex2f(x + r * cos(i * twoPI / circle_triangles),
                           y + r * sin(i * twoPI / circle_triangles));
            }
            glEnd();
        }
        /* Polygon */
        else if(fixture->GetShape()->GetType() == 2){
            b2PolygonShape *shape = (b2PolygonShape*) fixture->GetShape();

            /* set basic color: Red. */
            glColor3f(1, 0, 0);

            /* Make room for vertices, max 8 vertices per polygon. */
            GLfloat glverts[16];

            //tell OpenGL where to find vertices
            glVertexPointer(2, GL_FLOAT, 0, glverts);
            glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays
            
            //fill in vertex positions as directed by Box2D
            for (i = 0; i < shape->GetVertexCount(); i++) {
                glverts[i*2]   = poly->GetWorldPoint(shape->GetVertex(i)).x;
                glverts[i*2+1] = poly->GetWorldPoint(shape->GetVertex(i)).y;
            }
            
            glDrawArrays(GL_TRIANGLE_FAN, 0, shape->GetVertexCount());
        }

        poly = poly->GetNext();
    }

    /* Draw end. */
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(levels[level_num].end.x, levels[level_num].end.y);
    for (i = 0; i <= circle_triangles; i++) {
        glVertex2f(levels[level_num].end.x + 0.1 * cos(i * twoPI / circle_triangles),
                   levels[level_num].end.y + 0.1 * sin(i * twoPI / circle_triangles));
    }

    glEnd();

    frame_count++;

    // Show rendered frame
    glutSwapBuffers();

    // Display fps in window title.
    if (frametime >= 1000)
    {
        char window_title[128];
        snprintf(window_title, 128,
                "Box2D: %f fps, level %d/%d",
                frame_count / (frametime / 1000.f), -1, num_levels);
        glutSetWindowTitle(window_title);
        last_time = time;
        frame_count = 0;
    }
}

/*
 * Called when window is resized. We inform OpenGL about this, and save this
 * for future reference.
 */
void resize_window(int width, int height)
{
    glViewport(0, 0, width, height);
    reso_x = width;
    reso_y = height;
}

/*
 * Called when the user presses a key.
 */
void key_pressed(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // Esc
        case 'q':
            exit(0);
            break;
        // Add any keys you want to use, either for debugging or gameplay.
        case 'n':
            reset = 1;
        default:
            break;
    }
}

/*
 * Called when the user clicked (or released) a mouse buttons inside the window.
 */
void mouse_clicked(int button, int state, int x, int y)
{
    float x_fixed = (float)x / reso_x * world_x;
    float y_fixed = (float)abs(y - reso_y) / reso_y * world_y;

    if (state) {
        player_poly[player_index] = b2Vec2(x_fixed, y_fixed);
        player_index ++;

        if(player_index == 4){
            b2FixtureDef *playerFixture = new b2FixtureDef();
            b2PolygonShape *playerShape = new b2PolygonShape();
            b2BodyDef *playerBodyDef = new b2BodyDef();

            playerShape->Set(player_poly, 4);

            playerBodyDef->type = b2_dynamicBody;
            playerBodyDef->angle = 0;

            playerFixture->shape = playerShape;
            playerFixture->density = 1.0f;

            body = world->CreateBody(playerBodyDef);
            body->CreateFixture(playerFixture);

            player_index = 0;
        }
    }

}

/*
 * Called when the mouse is moved to a certain given position.
 */
void mouse_moved(int x, int y)
{

}


int main(int argc, char **argv)
{
    // Create an OpenGL context and a GLUT window.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(reso_x, reso_y);
    glutCreateWindow("Box2D");

    // Bind all GLUT events do callback function.
    glutDisplayFunc(&draw);
    glutIdleFunc(&draw);
    glutReshapeFunc(&resize_window);
    glutKeyboardFunc(&key_pressed);
    glutMouseFunc(&mouse_clicked);
    glutMotionFunc(&mouse_moved);
    glutPassiveMotionFunc(&mouse_moved);

    // Initialise the matrices so we have an orthogonal world with the same size
    // as the levels, and no other transformations.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, world_x, 0, world_y, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Read the levels into a bunch of structs.
    num_levels = load_levels(&levels);
    printf("Loaded %d levels.\n", num_levels);

    // Load the first level (i.e. create all Box2D stuff).
    world = new b2World(gravity);
    level_num = 0;
    load_world(level_num);

    last_time = glutGet(GLUT_ELAPSED_TIME);
    frame_count = 0;
    glutMainLoop();   

    return 0;
}
