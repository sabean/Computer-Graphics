#define _USE_PATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float x_pos = 0.0;
float y_pos = 0.0;
float z_pos = 0.0;
float theta = M_PI/6.0;
float phi = M_PI/2.0;
float R = 9.f;


/***********************************************************************************************/
/* Initialize OpenGL Graphics */

void initGL() {
	//to prevent faces rendering to the front while they're behind other faces.
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
   	glClearDepth(1.0f);                   // Set background depth to farthest
   	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   	glShadeModel(GL_SMOOTH);   // Enable smooth shading
   	glEnable(GL_LIGHTING);
   	glEnable(GL_LIGHT0);

   	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
   	glMatrixMode(GL_PROJECTION);
   	gluPerspective(90, 1, 1, 1000);
}

void changeSize(int w, int h) {
	if (h == 0)   // Prevent a divide by 0, when window is too short
		h = 1;
	float ratio = 1.0*w/h;
	glMatrixMode(GL_PROJECTION); // Reset the coordinate system before modifying: on the frame of reference of world
	glLoadIdentity();	//Specify the lower left corner of the viewport rectangle, in pixels by first two parameters.
	glViewport(0, 0, w, h); // Set the viewport to the entire window
	gluPerspective(90, ratio, 1, 1000); // Set the correct perspective
}

void display(){

	x_pos = R * cos(phi) * cos(theta);
	y_pos = R * sin(theta);
	z_pos = R * sin(phi) * cos(theta);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();


		if(cos(theta)>=0)
			gluLookAt(x_pos, y_pos, z_pos, 0.0, 0.0, 0.0, 0.0, 1.0 , 0.0);
		else 
			gluLookAt(x_pos, y_pos, z_pos, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);

		//set the ambient light to the previously defined light_ambient
		GLfloat light_ambient[] = {1, 1, 1, 1}; // white ambient
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

		//Set the position of the light source
		GLfloat light_position[] = {0, 5, 7, 0};
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		//Enable the diffusion for specular light
		GLfloat white_light[] = {1, 1, 1, 1};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);

		GLfloat red_light[] = {0.5,0.0, 0.0, 1};
		glLightfv(GL_LIGHT0, GL_SPECULAR, red_light);

		//Setting Material Properties
		GLfloat mat_specular[] = {1, 1, 1, 1};
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

		GLfloat mat_shininess[] = {50};
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		GLfloat mat_ambient[] = {0.0, 0.0, 0.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

		//Draw the sphere
		glPushMatrix();
			glColor3f(0.6, 0.18, 1.2); 
			glTranslatef(0, 0, -8);
			glutSolidSphere(3, 50, 50);
		glPopMatrix();


	glPopMatrix();
	glFlush(); // force execution of GL commands in finite time
	glutSwapBuffers();


}


void processKeys(unsigned char key, int x, int y) {
	switch (key) {

		case 'w' : theta += 0.1; glutPostRedisplay();break;
		case 'z': theta -= 0.1; glutPostRedisplay();break;
		case 'a': phi += 0.1; glutPostRedisplay();break;
		case 's': phi -= 0.1; glutPostRedisplay();break;
		case 'd': if(R>=8) R -= 0.5f; glutPostRedisplay();break;
		case 'f': if(R<100) R += 0.5f;glutPostRedisplay(); break;

		case 27: exit(0); break;

	}
	while (theta > 2*M_PI) theta -= 2*M_PI;
	while (theta < 0) theta += 2*M_PI;
	while (phi > 2*M_PI) phi -=2*M_PI;
	while (phi < 0) phi += 2*M_PI;

	glutPostRedisplay();

}

/**********************************************************************************************/
int main(int argc, char** argv){
        // Initializing Glut

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE); //sets glut display mode for the windows
        glutInitWindowSize(1000, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Spheres");

        // Registering callback functions

        glutDisplayFunc(display); 		//sets the display callback for current window; function as argument is called whenever the windows has to be redrawn
        glutReshapeFunc(changeSize);	//sets the reshape callback for the current window; function as argument is called whenever the windows has to be reshaped
        glutKeyboardFunc(processKeys); // called when a key is pressed .. key is ASCII; x and y mouse keys
        glutPostRedisplay();

        // Our own OpenGL initialization

		initGL();                       

        // Setting up the projection matrix

        glMatrixMode(GL_PROJECTION); //on the frame of reference of world
        gluPerspective(90.0, 1.0, 1.0, 1000.0);

        glutMainLoop();

        return 0;
}
