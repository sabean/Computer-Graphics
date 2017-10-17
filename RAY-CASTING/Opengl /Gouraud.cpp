#define _USE_PATH_DEFINES
#include "sphereHead.h"
#include <cctype>

using namespace std;

float x_pos = 0.0;
float y_pos = 0.0;
float z_pos = 0.0;
float theta = M_PI/6.0;
float phi = M_PI/2.0;
float R = 9.f;
float SRE = 10.0, SRC = 0.0, light0 = 0.0, light1 = 0.0, light2 = 0.0, light3 =0.0, AMB = 0.2, DIFF = 0.8, SHADE = 0.0;


/***********************************************************************************************/
// Point3D specifications
class Point3D{
	public:
		float x, y, z; // x, y, z-cordinates of point
		float n_x, n_y, n_z; // x, y, z-cordinates of normals

		Point3D() {
			x = 0.0; y = 0.0; z = 0.0;
			n_x = 0.0; n_y = 0.0; n_z = 0.0;
		}

		Point3D(float a, float b, float c, float a1, float b1, float c1){
			x = a; y = b; z = c;
			n_x = a1; n_y = b1; n_z = c1;
		}
		void setxyz(float a, float b, float c){
			x = a; y = b; z = c;
		}
		void setNormxyz(float a1, float b1, float c1){
			n_x = a1; n_y = b1; n_z = c1;
		}
		void print(){
			cout << "Vertices:  " << x << "," << y << "," << z << endl;
			cout << "Normals:  " << n_x << "," << n_y << "," << n_z << endl;

		}
};

//Triangle class
class Triangle : public Point3D{
	public:
		Point3D A;
		Point3D B;
		Point3D C;
		Triangle(){
			A.x = 0.0; A.y = 0.0; A.z = 0.0;
			B.x = 0.0; B.y = 0.0; B.z = 0.0;
			C.x = 0.0; C.y = 0.0; C.z = 0.0;

			A.n_x = 0.0; A.n_y = 0.0; A.n_z = 0.0;
			B.n_x = 0.0; B.n_y = 0.0; B.n_z = 0.0;
			C.n_x = 0.0; C.n_y = 0.0; C.n_z = 0.0;

		}
		Triangle(Point3D x1, Point3D x2, Point3D x3){
			A.x = x1.x;	A.y = x1.y;	A.z = x1.z;
			B.x = x2.x;	B.y = x2.y;	B.z = x2.z;
			C.x = x3.x;	C.y = x3.y;	C.z = x3.z;

			A.n_x = x1.n_x;	A.n_y = x1.n_y;	A.n_z = x1.n_z;
			B.n_x = x2.n_x;	B.n_y = x2.n_y;	B.n_z = x2.n_z;
			C.n_x = x3.n_x;	C.n_y = x3.n_y;	C.n_z = x3.n_z;
		}
		void setVertex(Point3D x1, Point3D x2, Point3D x3){
			A.x = x1.x;	A.y = x1.y;	A.z = x1.z;
			B.x = x2.x; B.y = x2.y;	B.z = x2.z;
			C.x = x3.x;	C.y = x3.y;	C.z = x3.z;
		}
		void setNormal(Point3D x1, Point3D x2, Point3D x3){
			A.n_x = x1.n_x;	A.n_y = x1.n_y;	A.n_z = x1.n_z;
			B.n_x = x2.n_x;	B.n_y = x2.n_y;	B.n_z = x2.n_z;
			C.n_x = x3.n_x;	C.n_y = x3.n_y;	C.n_z = x3.n_z;
		}

		void tprint(){
			cout << "Vertices" << endl;
			cout << "(" << A.x << ", " << A.y << ", " << A.z << ") ";
			cout << "(" << B.x << ", " << B.y << ", " << B.z << ") ";
			cout << "(" << C.x << ", " << C.y << ", " << C.z << ") \n";
			cout << "Normal" << endl;
			cout << "(" << A.n_x << ", " << A.n_y << ", " << A.n_z << ") ";
			cout << "(" << B.n_x << ", " << B.n_y << ", " << B.n_z << ") ";
			cout << "(" << C.n_x << ", " << C.n_y << ", " << C.n_z << ") \n";
		}
};


/* Initialize OpenGL Graphics */
int numTri;
Triangle *mySoup;

void initGL() {
	vector <glm::vec3> vertices;
	vector <glm::vec3> normal;
    bool res = loadOBJ("suzanne.obj", vertices, normal);
    if(res == false){
    	return;
    }
    int sizeT = vertices.size();
    numTri = sizeT/3;
    cout << "Checkpoint ............................(0)" << endl;

    std::vector<float> vecx;	//all the x coordinates 
	std::vector<float> vecy;	//all the y coordinates
	std::vector<float> vecz;	//all the z coordinates
	std::vector<float> vec1x;	//all the x coordinates normal
	std::vector<float> vec1y;	//all the y coordinates normal
	std::vector<float> vec1z;	//all the z coordinates normal

    for(int i=0; i < numTri; i++){

    	vecx.push_back(vertices[3*i].x);
    	vecy.push_back(vertices[3*i].y);
    	vecz.push_back(vertices[3*i].z);

    	vecx.push_back(vertices[3*i+1].x);
    	vecy.push_back(vertices[3*i+1].y);
    	vecz.push_back(vertices[3*i+1].z);

    	vecx.push_back(vertices[3*i+2].x);
    	vecy.push_back(vertices[3*i+2].y);
    	vecz.push_back(vertices[3*i+2].z);

    	vec1x.push_back(normal[3*i].x);
    	vec1y.push_back(normal[3*i].y);
    	vec1z.push_back(normal[3*i].z);

    	vec1x.push_back(normal[3*i+1].x);
    	vec1y.push_back(normal[3*i+1].y);
    	vec1z.push_back(normal[3*i+1].z);

    	vec1x.push_back(normal[3*i+2].x);
    	vec1y.push_back(normal[3*i+2].y);
    	vec1z.push_back(normal[3*i+2].z);


    }

    Point3D *mapPoint;
	mapPoint = new Point3D[sizeT];


    for(int i = 0; i < sizeT; i++){
    	mapPoint[i].x = vecx[i];
    	mapPoint[i].y = vecy[i];
    	mapPoint[i].z = vecz[i];
    	mapPoint[i].n_x = vec1x[i];
    	mapPoint[i].n_y = vec1y[i];
    	mapPoint[i].n_z = vec1z[i];
    	//mapPoint[i].print();
    	//cout << i << endl;
    }
    vecx.clear();
    vecy.clear();
    vecz.clear();
    vec1x.clear();
    vec1y.clear();
    vec1z.clear();

    //cout << "Checkpoint ............................(1)" << endl;
    //Triangle *mySoup;
	mySoup = new Triangle[numTri];

     for(int i=0; i < numTri; i++){

    	mySoup[i].setVertex(mapPoint[3*i], mapPoint[3*i+1], mapPoint[3*i+2]);
    	mySoup[i].setNormal(mapPoint[3*i], mapPoint[3*i+1], mapPoint[3*i+2]);

    }
    //cout << "Checkpoint ............................(2)" << endl;
	delete [] mapPoint;
	//cout << "Checkpoint ............................(3)" << endl;
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

		//SHADE control
	    if (SHADE==0){
	        glShadeModel(GL_SMOOTH);
	    }
	    else{
	        glShadeModel(GL_FLAT);
	    }
	    
	    
	    //light control
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
	    if (light3==1){
	        glEnable(GL_LIGHT3);
	    }else{
	        glDisable(GL_LIGHT3);
	    }
	    
	    
	    
	    //setting up the light source

	    //	GREEN LIGHT
	    
	    GLfloat light_ambient_0[]={1, 1, 1, 1};
	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_0);
	    
	    GLfloat light_position_0[]={2,8,10,0};
	    glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
	    
	    GLfloat green_light_0[]={0 ,1 ,0 ,1};
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, green_light_0);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, green_light_0);

	    //	RED LIGHT

	    GLfloat light_ambient_1[]={1, 1, 1, 1};
	    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient_1);
	    
	    GLfloat light_position_1[]={4,-3,7,0};
	    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
	    
	    GLfloat red_light_1[]={1 ,0 ,0 ,1};
	    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light_1);
	    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light_1);

	    // BLUE LIGHT

	    GLfloat light_ambient_2[]={1, 1, 1, 1};
	    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient_2);
	    
	    GLfloat light_position_2[]={12,3,5,0};
	    glLightfv(GL_LIGHT2, GL_POSITION, light_position_2);
	    
	    GLfloat blue_light_2[]={0.0 ,0 ,1 ,1};
	    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light_2);
	    glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light_2);

	    //	WHITE LIGHT

	    GLfloat light_ambient_3[]={1, 1, 1, 1};
	    glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient_3);
	    
	    GLfloat light_position_3[]={12,3,5,0};
	    glLightfv(GL_LIGHT3, GL_POSITION, light_position_3);
	    
	    GLfloat white_light_3[]={1 ,1 ,1 ,1};
	    glLightfv(GL_LIGHT3, GL_DIFFUSE, white_light_3);
	    glLightfv(GL_LIGHT3, GL_SPECULAR, white_light_3);

	    
	    //set material here
	    
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
			
			for(int i= 0; i < numTri; i++){

				glBegin(GL_TRIANGLES);

				glVertex3f(mySoup[i].A.x, mySoup[i].A.y, mySoup[i].A.z);
				glNormal3f(mySoup[i].A.n_x, mySoup[i].A.n_y, mySoup[i].A.n_z);

				glVertex3f(mySoup[i].B.x, mySoup[i].B.y, mySoup[i].B.z);
				glNormal3f(mySoup[i].B.n_x, mySoup[i].B.n_y, mySoup[i].B.n_z);

				glVertex3f(mySoup[i].C.x, mySoup[i].C.y, mySoup[i].C.z);
				glNormal3f(mySoup[i].C.n_x, mySoup[i].C.n_y, mySoup[i].C.n_z);


				glEnd();
			}

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
		case ' ': { if (light3 == 0) {
						light3 = 1;
						glutPostRedisplay();
					}
					else {
						light3 = 0; 
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
        glutCreateWindow("MESH LOADING...");

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
