// Sabin Bhandari

#define _USE_PATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

float x_pos = 0.0;
float y_pos = 0.0;
float z_pos = 0.0;
float theta = M_PI/6.0;
float phi = M_PI/2.0;
float R = 9.f;
float SRE = 50.0, SRC = 0.0, light0 = 0.0, light1 = 0.0, light2 = 0.0, AMB = 0.2, DIFF = 0.8, SHADE = 0.0;


/***********************************************************************************************/
/* Initialize OpenGL Graphics */

void initGL() {
	//to prevent faces rendering to the front while they're behind other faces.
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
   	glClearDepth(1.0f);                   // Set background depth to farthest
   	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   	glShadeModel(GL_SMOOTH);   // Enable smooth SHADE
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
	glMatrixMode(GL_PROJECTION); // Reset the coordinate system before moDIFFying: on the frame of reference of world
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

		//SHADE control to make smooth or flat

	    if (SHADE==0){
	        glShadeModel(GL_SMOOTH);
	    }
	    else{
	        glShadeModel(GL_FLAT);
	    }
	    
	    
	    //light control : enabling and disabling on another
	    if (light0==1){
	        glEnable(GL_LIGHT0);
	    }else{
	        glDisable(GL_LIGHT0);
	    }
	    if (light1==1){
	        glEnable(GL_LIGHT1);
	    }else{
	        glDisable(GL_LIGHT1);
	    }
	    if (light2==1){
	        glEnable(GL_LIGHT2);
	    }else{
	        glDisable(GL_LIGHT2);
	    }
	    
	    
	    
	    //setting up the light source
	    

	    //LIGHT SOURCE 1
	    GLfloat light_ambient_0[]={1, 1, 1, 1};
	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_0);
	    
	    GLfloat light_position_0[]={2,8,10,0};
	    glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
	    
	    GLfloat green_light_0[]={0 ,1 ,0 ,1};
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, green_light_0);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, green_light_0);

	    //LIGHT SOURCE 2

	    GLfloat light_ambient_1[]={1, 1, 1, 1};
	    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient_1);
	    
	    GLfloat light_position_1[]={4,-3,7,0};
	    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
	    
	    GLfloat red_light_1[]={1 ,0 ,0 ,1};
	    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light_1);
	    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light_1);

	    //LIGHT SOUCE 3

	    GLfloat light_ambient_2[]={1, 1, 1, 1};
	    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient_2);
	    
	    GLfloat light_position_2[]={12,3,5,0};
	    glLightfv(GL_LIGHT2, GL_POSITION, light_position_2);
	    
	    GLfloat blue_light_2[]={0.0 ,0 ,1 ,1};
	    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light_2);
	    glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light_2);

	    
	    //setting material properties here
	    
	    GLfloat mat_shini[]={SRE};
	    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shini);
	    
	    
	    GLfloat mat_specular[]={SRC, SRC,SRC,1};
	    glMaterialfv(GL_FRONT, GL_SPECULAR  ,mat_specular);
	    
	    
	    GLfloat black[]={AMB,AMB,AMB,1};
	    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	    
	    
	    GLfloat DIFFf[]={DIFF,DIFF,DIFF,1};
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, DIFFf);

		//Draw the sphere
		glPushMatrix();
			glColor3f(1.0, 0.0, 0.0);
			glTranslatef(0, 0, -8);
			glutSolidSphere(3, 50, 50);
		glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void processKeys(unsigned char key, int x, int y) {
	switch (key) {

		case 'w': theta += 0.1; glutPostRedisplay();break;
		case 'z': theta -= 0.1; glutPostRedisplay();break;
		case 'a': phi += 0.1; glutPostRedisplay();break;
		case 's': phi -= 0.1; glutPostRedisplay();break;
		case 'd': if(R>=2) R -= 0.5f; glutPostRedisplay();break;
		case 'f': if(R<100) R += 0.5f;glutPostRedisplay(); break;
		case '0':{ if (light0 == 0){
					light0 = 1;
					glutPostRedisplay(); 
					}
					else{
						light0 = 0;
						glutPostRedisplay(); 
					}
					break;
				}
		case '1': { if (light1 == 0) {	
						light1 = 1;
						glutPostRedisplay(); 
					}
					else {
						light1= 0;
						glutPostRedisplay();
					}
					break;
				}
		case '2': { if (light2 == 0) {
						light2 = 1;
						glutPostRedisplay();
					}
					else {
						light2 = 0; 
						glutPostRedisplay();
					}
					break;
				}	
		case '3': {	if (SHADE == 0) {
						SHADE = 1; 
						glutPostRedisplay(); 
					}
					else{
						SHADE = 0;
						glutPostRedisplay();
					}
					break;
				} 
		case '4': SRC += 0.1; if(SRC > 1) SRC = 1; glutPostRedisplay(); break;
		case '5': DIFF += 0.1; if(DIFF > 1) DIFF = 1; glutPostRedisplay(); break;
		case '6': SRE += 5.0; if(SRE > 150) SRE = 150; glutPostRedisplay(); break;
		case '7': AMB += 0.05; if(AMB > 1) AMB = 1; glutPostRedisplay(); break;
		case '8': SRC -= 0.1; if(SRC < 0) SRC = 0; glutPostRedisplay(); break;
		case '9': DIFF -= 0.1; if(DIFF < 0) DIFF = 0; glutPostRedisplay(); break;
		case 'o': SRE -= 5.0; if(SRE < 0) SRE = 0; glutPostRedisplay(); break;
		case 'p': AMB -= 0.05; if(AMB < 0) AMB = 0; glutPostRedisplay(); break;

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
