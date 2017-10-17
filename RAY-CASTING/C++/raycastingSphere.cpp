/*
			
				COMPUTER GRAPHICS

			Homework Practical - 07
			  Name: Sabin Bhandari


*/

/*
	PROGRAM PROCEDURE: ONLY THEORITICAL ANALYSIS
	1. FINDING THE INDIVIDUAL EQUATION BY SOLVING THE RAY EQUATION AND IMPLICIT REPRESENTATION OF THE SPHERE
	2. ANALYZE THE DEPTH BY COMPARING Z COORDINATE OF EACH SPHERES AND THEN WITH THE OTHER SPHERE
*/


#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

//CLASS DECLARATIONS

/****************************************************************************************************/
//material properties
float matAmbient[4] = {0.0,0.0,0.0,1.0};
float matDiffuse[4] = {0.8,0.8,0.8,1.0};
float matSpecular[4] = {0.5,0.5,0.5,1.0};
float SRE = 50;

//Colour class
class ColorRGB {
	public:
		float R, G, B, A; // correspondingly Red, Green and blue.
		ColorRGB(){}
		void setRGBA(float red, float green, float blue, float amb) {
				R = red;
				G = green;
				B = blue;
				A = amb;
		}
};

//Class representing the point
class Point3D : public ColorRGB{
	public:
		float x, y, z; // x, y, z-cordinates of point
		Point3D() {
			x = 0.0;
			y = 0.0;
			z = 0.0;
		}


		Point3D(float a, float b, float c){
			x = a;
			y = b;
			z = c;
		}
		void setxyz(float a, float b, float c){
			x = a;
			y = b;
			z = c;
		}
		void print(){
			cout << x << "," << y << "," << z << endl;
		}
};


//Sphere class which has points inherited
class Sphere : public Point3D{
	public:
		float r;	// radius
	    Sphere(){
	    	r = 0.0;	
	    }
	    Sphere(float r1, float cx, float cy, float cz) {
	    	r = r1;
	    	x = cx;
	    	y = cy;
	    	z = cz;
 	    }
};
// New light class
class Light{
	public:
		float ambient[4];
		float diffuse[4];
		Point3D position;
		Light(){}
		Light(float amb[4],float diff[4],Point3D pos){
			for(int i = 0 ; i<4;i++){
				ambient[i] = amb[i];
				diffuse[i] = diff[i];
			}
			position.x = pos.x;
			position.y = pos.y;
			position.z = pos.z;

		}
};


//METHOD DECLARATIONS
/********************************************************************************************************************/
float dotProduct(Point3D a, Point3D b){
	float m1 = a.x * b.x;
	float m2 = a.y * b.y;
	float m3 = a.z * b.z;
	float res = m1+m2+m3;
	return res;
}

float Norm(Point3D v){
	float rval = 0.0;
	rval = sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
	return rval;

} 

// The calculation of l, v, h and n.
Point3D calcL(Point3D IP, Point3D LS1){
	Point3D rvec;
	float a = LS1.x - IP.x;
	float b = LS1.y - IP.y;
	float c = LS1.z - IP.z;
	rvec.setxyz(a, b, c);
	float len = Norm(rvec);
	rvec.x = rvec.x / len;
	rvec.y = rvec.y / len;
	rvec.z = rvec.z / len;
	return rvec;
}

Point3D calcV(Point3D IP, Point3D vp){
	Point3D rvec;
	rvec.x = vp.x - IP.x;
	rvec.y = vp.y - IP.y;
	rvec.z = vp.z - IP.z;
	float len = Norm(rvec);
	rvec.x = rvec.x / len;
	rvec.y = rvec.y / len;
	rvec.z = rvec.z / len;
	return rvec;
}

Point3D calcH(Point3D L, Point3D V){
	Point3D h;
	h.x = L.x + V.x;
	h.y = L.y + V.y;
	h.z = L.z + V.z;
	float len = Norm(h);
	h.x = h.x / len;
	h.y = h.y / len;
	h.z = h.z / len;
	return h;
}

Point3D calcN(Point3D intPoint, Sphere cent){
	Point3D normal;
	normal.x = intPoint.x - cent.x;
	normal.y = intPoint.y - cent.y;
	normal.z = intPoint.z - cent.z;
	float len = Norm(normal);
	normal.x = normal.x / len;
	normal.y = normal.y / len;
	normal.z = normal.z / len;
	return normal;

}
/**************************************************************************************************************/

// Bling Phong illumination Model

float blinn_phong(vector<Light>& LS, Sphere& S, Point3D& IP, Point3D& vp, int RGBA){

	float phongAmbient = LS[0].ambient[RGBA] * matAmbient[RGBA];
	float phongSpecular = 0;
	for(unsigned int i = 0 ; i < LS.size() ; i++){
		// Normal to the plane
			Point3D Normal;
	    	Normal = calcN(IP, S);
	    	//Normal.print();

	    //l vector from intersection point to light source
    		Point3D val_L;
    		val_L = calcL(IP, LS[i].position);
    		//val_L.print();

    	//vector from intersection point to the viewpoint
    		Point3D I2V;
    		I2V = calcV(IP, vp);
    		//I2V.print();

    	//calculate the half vector
    		Point3D val_H;
    		val_H = calcH(val_L, I2V);
    		//val_H.print();
		
		phongSpecular += LS[i].diffuse[RGBA] * (matDiffuse[RGBA] * max(dotProduct(Normal,val_L),(float)0)+matSpecular[RGBA]*
			pow(max(dotProduct(val_H,Normal), (float)0),SRE));
	}
	float sum = phongAmbient + phongSpecular;
	return sum;
}

// A function to check intersection by taking in the view point, center of each pixel and center of sphere.

float checkIntersection(Point3D& vp, Point3D& pC, Sphere& sC1, vector<Light>& LS){  

	// The equation below is found by taking the coefficient of 't' by substituiting the parametric equation of the 
	// ray in the equation of the sphere. 
	// Parametric equation of a ray: P = Po + t*V
	// Implicit equation of the sphere: (x -x0)^2 + (y - yo)^2 + (z - zo)^2 = r^2
	// So, we obtain the coefficients of 't' as a, b, c and observe the discriminants.


	//Analysis for the first sphere
	float a1 = (pC.x*pC.x) + (pC.y*pC.y) + (pC.z* pC.z) + (4.0*pC.z) + 4.0;
	float b1 = (-2.0*sC1.x*pC.x) - (2.0*pC.y*sC1.y) - (4*pC.z) - (2*sC1.z*pC.z) - 8.0 - 4.0*sC1.z;
	float c1 = (sC1.x*sC1.x) + (sC1.y*sC1.y) + (sC1.z*sC1.z) + (4*sC1.z) - (sC1.r*sC1.r) + 4.0;
	
	// Discriminant of quadratic equation
	float discriminant_1 = (b1*b1) - (4.0*a1*c1);


// All Imaginary discriminants as no real points obtained for each sphere.
	if(discriminant_1 < 0.0){
		pC.setRGBA(0.0, 0.0, 0.0, 0.0);
		return 0;
	}
// Intersection with the first sphere
	else if(discriminant_1 >= 0){
		// Calculation of value of t
	    	float t_1 = (-b1 - sqrt(discriminant_1))/(2.0*a1);
	    	
	    //intersection points
	    	float val_x = vp.x +(t_1*(pC.x + 0.0));
    		float val_y = vp.y +(t_1*(pC.y + 0.0));
	    	float val_z = vp.z +(t_1*(pC.z + 2.0));

	   	//Setting up the intersection points
	    	Point3D IP;
	    	IP.setxyz(val_x, val_y, val_z);
	    	
	    	// Setting the blinn phong where RGB value is given
			float Rval = blinn_phong(LS, sC1, IP, vp, 0);
			if(Rval > 1) Rval = 1;
			float Gval = blinn_phong(LS, sC1, IP, vp, 1);
			if(Gval > 1) Gval = 1;
			float Bval = blinn_phong(LS, sC1, IP, vp, 2);
			if(Bval > 1) Bval = 1;
			float Aval = blinn_phong(LS, sC1, IP, vp, 3);
			if(Aval > 1) Aval = 1;
			//cout << Rval << " " << Gval << " " << Bval << " " << Aval << endl;
			pC.setRGBA(Rval, Gval, Bval, Aval);

	    	return 0;
	}
	else{
		pC.setRGBA(0.0, 0.0, 0.0, 0.0);
		return 0;
	}
	
		
}

//MAIN PROGRAM
/*********************************************************************************************************************/

int main(void)
{
	int length = 0, width = 0;

	cout << "Enter desired Resolution: " << endl;
	cin >> length >> width;
	if(length != width){
		cout << "Unsymmetrical division of pixel!!!!!" << endl;
		return 0;
	}

	// Calculating the middle point of the pixel

	//Allocating the pixel to avoid segmentation fault, generally after size 500*500
	Point3D **Pixel_center;

	Pixel_center = new Point3D*[length];
	for(int y = 0; y < length; y++){
		Pixel_center[y] = new Point3D[width];
	}
	 // Calculation of the first center of pixel 
	int cnt1 = 0, cnt2 = 0;
	for (float a = (1.0-(1.0/length)); a >= -1.0; a-=(2.0/length)) {
		for(float b = (-1.0+(1.0/width)); b <= 1.0; b+=(2.0/width)){
			Pixel_center[cnt1][cnt2].setxyz(b, a, 0);
			cnt2++;
		}
		cnt2 = 0;
		cnt1++;	
	}


	Point3D viewPoint;    // setting view point
	viewPoint.setxyz(0,0,-2);

	//Creating the sphere
	Sphere sphere1(1.5, 0.1, 0.1, 4.0);

	// Definations for light sources

	Point3D lightsource1;
	Point3D lightsource2;
	Point3D lightsource3;

	// setting the position of the light sources
	lightsource1.setxyz(3.0, 3.8, -1);

	lightsource2.setxyz(-3.0, 3.8, -1);

	lightsource3.setxyz(0.0, -3.8, -1);


	//Ambienence
	float amb[4] = {0,0,0,1};

	//Lights and their properties

	float diff1[4] = {0.0,0.0,1,1};
	Light Light0(amb, diff1, lightsource1);		//BLUE LIGHT

	float diff2[4] = {1,0.0,0.0,1};
	Light Light1(amb, diff2, lightsource2);		// RED LIGHT

	float diff3[4] = {0.0,1,0.0,1};
	Light Light2(amb, diff3, lightsource3);		// GREEN VALUE

	//vector of the lights
	vector<Light> vecLights;
	vecLights.push_back(Light0);
	vecLights.push_back(Light1);
	vecLights.push_back(Light2);

	// Implementing the shooting of rays
	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
			checkIntersection(viewPoint, Pixel_center[x1][y1], sphere1, vecLights);
		}
	}

	// Obtaining 3d image by utilizing the ppm program
  	FILE *fp = fopen("sphere.ppm", "wb"); // b - binary mode 

  	(void) fprintf(fp, "P6\n%d %d\n255\n", length, width);
	for (int j = 0; j < length; j++){
	    for (int i = 0; i < length; i++){
	    	static unsigned char color[3];
		    color[0] = (unsigned char) floor(Pixel_center[j][i].A * Pixel_center[j][i].R * 255);  // red 
		    color[1] = (unsigned char) floor(Pixel_center[j][i].A * Pixel_center[j][i].G * 255);  // green
		    color[2] = (unsigned char) floor(Pixel_center[j][i].A * Pixel_center[j][i].B * 255);  // blue 
		    (void) fwrite(color, 1, 3, fp);
	    }
	 }
  (void) fclose(fp); 

	 // Deallocating the pixel 
	for(int i = 0; i < length; i++){
		delete [] Pixel_center[i];
	}
	delete [] Pixel_center;

  return EXIT_SUCCESS;

}





