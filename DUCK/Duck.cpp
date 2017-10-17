/*

						Computer Graphics
		  				  Homework - 2
						Sabin Bhandari 
*/
/*****************************************************************************************

---------------------------CONTROLS--------------------------------

			W 					W/Z = YAW ROTATION
		A 		S 					
			Z 					A/S = ZOOM IN AND OUT


		    I	 				I = TO REPOSITION
		J 		K 				M = DUNK THE DUCK
		    M    	 			J/K = SPINNING OF THE DUCK		
		
		SPACE = MOVE FORWARD IN LINE OF SIGHT

-------------------------PROGRAM LAYOUT--------------------------

		1. Programmer made initialization.
		2. Change size function.
		3. Drawing funtions.
		4. Display
		5. Process Keys
		6. Main

********************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

/* Global initializations */

double ro = 6.f, phi = 0.01, theta = 0.01, dunk =0.0f; 
int path = 0;
int dir = 0;
float a = 0.0f, b = 0.0f;
#define PI 3.14159265

/*******************************************************************************************/
/* Initialize OpenGL Graphics */

void initGL() {
	//to prevent faces rendering to the front while they're behind other faces.
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
   	glClearDepth(1.0f);                   // Set background depth to farthest
   	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   	glShadeModel(GL_SMOOTH);   // Enable smooth shading
   	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

}

void changeSize(int w, int h) {
	if (h == 0)   // Prevent a divide by 0, when window is too short
		h = 1;
	float ratio = 1.0*w/h;
	//specify which matrix is the current matrix and applies subsequent matrix operations to the projection matrix stack.
	glMatrixMode(GL_PROJECTION); // Reset the coordinate system before modifying: on the frame of reference of world
	//replace the current matrix with the identity matrix
	glLoadIdentity();
	//Specify the lower left corner of the viewport rectangle, in pixels by first two parameters.
	glViewport(0, 0, w, h); // Set the viewport to the entire window
	//void gluPerspective(GLdouble fovy,GLdouble aspect,GLdouble zNear,GLdouble zFar);
 	//fovy = Specifies the field of view angle, in degrees, in the y direction.
	//aspect = specifies the aspect ratio that determines the field of view in the x direction. x(width) to y(height)
	// znear-zFar = distance from the view to near and far clipping plane
	gluPerspective(90, ratio, 1, 1000); // Set the correct perspective
}
/**********************************************************************************************/

void drawSurface(){
	glPushMatrix();
		glColor4f(0.196078f, 0.6f, 0.8f, 1.0f);
		glLineWidth(1.5f);

		glTranslatef(0.0f, 0.0f, 0.0f);
		glScalef(10.0f, 10.0f, 2.0f);
		glutSolidCube(4.0);
	glPopMatrix();

}

void drawBody(){
	glPushMatrix();
		glColor3f(0.208824, 0.208824, 0.545294);
		glLineWidth(1.5f);

		glTranslatef(0.0f, 0.0f, -4.0f);
		glScalef(2.5f, 1.6f, 1.6f);
		glutSolidSphere(1,20,20);
	glPopMatrix();
}


void drawHead(){
	glPushMatrix();
		glColor3f(0.73, 0.208, 1.45); 
		glLineWidth(1.5f);

		glTranslatef(2.0f, 0.0f, -5.8f);
		glScalef(2.2f, 1.7f, 1.7f);
		glutSolidSphere(0.5,20,20);
	glPopMatrix();
}


void drawTail(){

	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0); 
		glLineWidth(0.5f);
		glTranslatef(-2.0f, 0.0f, -4.6f);
		glRotatef(-130, 0.0, 1.0, 0.0);
		glScalef(1.0, 1.8, 1.0);
		glutSolidCone(0.5, 1.0, 20.0, 20.0);
	glPopMatrix();

}

void drawBeak(){
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0); 
		glLineWidth(0.5f);
		glTranslatef(3.0f, 0.0f, -5.6f);

		glRotatef(500, 1.0, 0.0, 0.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		glRotatef(200, 0.0, 0.0, 1.0);

		glScalef(0.8f, 0.8f, 0.8f);
		glutSolidCone(0.38, 1.8, 20.0, 20.0);
	glPopMatrix();
}

void drawEyeLeft(){

	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0); 
		glLineWidth(1.5f);
		glTranslatef(2.4f, 0.6f, -5.8f);
		glScalef(2.0f, 1.0f, 2.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0); 
		glLineWidth(1.5f);
		glTranslatef(2.6f, 0.65f, -5.8f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();
}

void drawEyeRight(){
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0); 
		glLineWidth(1.5f);

		glTranslatef(2.4f, -0.6f, -5.8f);
		glScalef(2.0f, 1.0f, 2.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0); 
		glLineWidth(1.5f);

		glTranslatef(2.6f, -0.65f, -5.8f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();


}
void drawHair(){
	glPushMatrix();
		glColor3f(0.6, 0.18, 1.2); 
		glLineWidth(1.5f);

		glTranslatef(2.0f, 0.0f, -6.4f);
		glScalef(3.4f, 2.0f, 1.7f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();
}
void drawWings(){
	glPushMatrix();
		glColor3f(0.73, 0.208, 1.45); 
		glLineWidth(1.5f);
		glTranslatef(0.0f, 1.6f, -4.0f);
		glScalef(2.6f, 0.6f, 1.6f);
		glutSolidSphere(0.4,20,20);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.6, 0.18, 1.2); 
		glLineWidth(1.5f);
		glTranslatef(0.0f, 1.6f, -4.0f);
		glScalef(2.6f, 0.6f, 1.6f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.73, 0.208, 1.45); 
		glLineWidth(1.5f);
		glTranslatef(0.0f, -1.6f, -4.0f);
		glScalef(2.6f, 0.6f, 1.6f);
		glutSolidSphere(0.4,20,20);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.6, 0.18, 1.2); 
		glLineWidth(1.5f);
		glTranslatef(0.0f, -1.6f, -4.0f);
		glScalef(2.6f, 0.6f, 1.6f);
		glutSolidSphere(0.35,20,20);
	glPopMatrix();

}

void drawFlowers(float p, float q){
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glLineWidth(1.5f);
		glTranslatef(3.0f+p, 2.0f+q, -4.0f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.3,20,20);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(1.5f);
		glTranslatef(3.0f+p, 2.2f+q, -4.0f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(1.5f);
		glTranslatef(3.0f+p, 1.8f+q, -4.0f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(1.5f);
		glTranslatef(3.2f+p, 2.0f+q, -4.0f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(1.5f);
		glTranslatef(2.8f+p, 2.0f+q, -4.0f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();

}


void drawDuck(){
	drawBody();
	drawHead();
	drawHair();
	drawTail();
	drawBeak();
	drawEyeRight();
	drawEyeLeft();
	drawWings();
}
/***********************************************************/
void display(){

	double x = 0.f, y = 0.f, z = 0.f;
	//clear buffers to preset values
	//Indicates the buffers currently enabled for color writing.
	//Indicates the depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotated OpenGL coordinate sySstem
	// Cartesian coordinates may be retrieved from the spherical coordinates 
	z = ro * cos(phi) * sin(theta); // y
	x = ro * sin(phi) * sin(theta); // x
	y = ro * cos(theta); // z
// theta for x-axis rotation phi for y-axis rotation ro zoom in zoom out

// Initializing the modelview matrix with the identity: on the frame of reference of object
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

// Looking from (x,y,z) to the origin of the coordinate system
// Constructing the matrix and multiplying it by the current modelview matrix
//void gluLookAt(GLdouble eyeX,GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,
//GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ);
//eyeX, eyeY, eyeZ sets the position of the eye point
//centerX, centerY, centerZ specifies the position of the reference point.
//upX, upY, upZ specifies the direction of the up vector.

	glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glLineWidth(1.5f);
		glTranslatef(4.5f, -2.0f, -8.0f);
		glScalef(1.0f, 1.0f, 1.0f);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();

	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0 * sin(theta), 0.0);
/*OpenGL keeps a stack of matrices to quickly apply and remove transformations.
 glPushMatrix copies the top matrix and pushes it onto the stack, while glPopMatrix
  pops the top matrix off the stack. All transformation functions (glScaled, etc.) 
  function on the top matrix, and the top matrix is what all rendering commands use
  to transform their data. By pushing and popping matrices, you can control what 
  transformations apply to which objects, as well as apply transformations to groups 
  of objects, and easily reverse the transformations so that they don't affect other objects. */


// Primary function to create the surface and Jacobs Duck in it.
    glPushMatrix();
       	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
       	glRotatef(dir, 0.0f, 0.0f, 1.0f);

	//Drawing the surface of water

		drawSurface(); 
	//Drawing flowers
		drawFlowers(9.0, 5.0);
		drawFlowers(5.0, 4.0);
		drawFlowers(-5.0, 4.0);
		drawFlowers(-9.0, 5.0);
		drawFlowers(9.0, -5.0);
		drawFlowers(5.0, -4.0);
		drawFlowers(-6.0, -4.0);
		drawFlowers(-9.0, -5.0);


		glPushMatrix();
			glTranslatef(a, b, 0.0f);
			glRotatef(path+90, 0, 0,-1); 
			glRotatef(dunk * 180 / PI, 0.0, 1.0, 0.0); // conversion into radians
			if(dunk >0.45){					//Constraint for dunking
				dunk = -0.1;
			}
			glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	//Primary funtion to draw Jacobs Duck        
			drawDuck();
		glPopMatrix();
   	glPopMatrix();
   	glFlush(); // force execution of GL commands in finite time
	glutSwapBuffers(); //swaps the buffers of the current window if double buffered
}

/***********************************************************************************************/

void processKeys(unsigned char key, int x, int y) {
	switch (key) {

		case 'w': {				//Yaw rotation
			dir += 4;
			break;
		}
		case 'z': {
			dir -= 4;
			break;
		}
		case 'a': ro += 0.3f; break;	// zooming options
		case 's': ro -= 0.3f; break;
		case 'k': {						// Spinning Options
			path +=2.0f;
			glutPostRedisplay();
			break;
		}
		case 'j': {
			path -=2.0f;
			glutPostRedisplay();
			break;
		}
		case ' ': {						// Forward Movement 
			a += sin((PI/180) * path) * 1.0f;	 // coversion into degrees ...explanation on the trigonometric basis
    		b += cos((PI/180)* path) * 1.0f;
			glutPostRedisplay();
			break;
		} 
		case 'm': {						// Dunking of the duck
			dunk += 0.1f;
			glutPostRedisplay();
			break;
		}
		case 'i': dunk = -0.1f; glutPostRedisplay(); break;		// Correcting the relative position of the duck
		case 't': theta += 1.0;glutPostRedisplay(); break;	
		case 'r': theta -=1.0;glutPostRedisplay(); break;
		case 27: exit(0);
	}

	while (theta > 2*M_PI) theta -= 2*M_PI;
	while (theta < 0) theta += 2*M_PI;
	while (phi > 2*M_PI) phi -=2*M_PI;
	while (phi < 0) phi += 2*M_PI;

	glutPostRedisplay();
}

/******************************************************************/
int main(int argc, char** argv){
        // Initializing Glut

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE); //sets glut display mode for the windows
        //the parameters inside the glutDisplayMode are bitmasks
        //bitmask for RGBA mode window
        //bitmask for duble buffered window
        //...depth buffer
        //... multisampling - samples each pixels multiple times
        glutInitWindowSize(1000, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Duck");

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
	   	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
        glutMainLoop();

        return 0;
}
