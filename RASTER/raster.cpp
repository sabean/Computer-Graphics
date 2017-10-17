/*
			
				COMPUTER GRAPHICS

			Homework Practical - 02
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

using namespace std;

//CLASS DECLARATIONS

/****************************************************************************************************/
//Colour class
class ColorRGB {
	public:
		float R, G, B; // correspondingly Red, Green and blue.
		void setRGB(float red, float green, float blue) {
				R = red;
				G = green;
				B = blue;
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
	    float area() {return M_PI*r*r;}
	    Sphere(){
	    	r = 0.0;	
	    }
	    Sphere (float r1, float cx, float cy, float cz) {
	    	r = r1;
	    	x = cx;
	    	y = cy;
	    	z = cz;
 	    }
};

//METHOD DECLARATIONS
/****************************************************************************************************************/

/*
Point3D crossproduct(const Point3D& p1, const Point3D& p2){
	Point3D newP;
    newP.x = p1.y*p2.z - p2.y*p1.z;
    newP.y = p2.x*p1.z - p1.x*p2.z;
    newP.z = p1.x*p2.y - p2.x*p1.y;
      
    return newP;
 }

float dotproduct(const Point3D& p1, const Point3D& p2) {
      float scalar = p1.x*p2.x + p1.y*p2.y + p3.z*p3.z;
      return scalar;
 }*/

//Making the screen of the desired sizes
void MakeScreen(int length, int width){
	Point3D Vertex1;
	Point3D Vertex2;
	Point3D Vertex3;
	Point3D Vertex4;

	Vertex1.setxyz(-1,1,0);
	Vertex2.setxyz(1,1,0);
	Vertex3.setxyz(1,-1,0);
	Vertex4.setxyz(-1,-1,0);
}

// for finding the norm of a given sets of points

float Absolute(float x, float y, float z) {
    return sqrt(x*x + y*y + z*z);
};

// A function to check intersection by taking in the view point, center of each pixel and center of sphere.

float checkIntersection(Point3D& pC, Sphere& sC1, Sphere& sC2, Sphere& sC3){  

	// The equation below is found by taking the coefficient of 't' by substituiting the parametric equation of the 
	// ray in the equation of the sphere. 
	// Parametric equation of a ray: P = Po + t*V
	// Implicit equation of the sphere: (x -x0)^2 + (y - yo)^2 + (z - zo)^2 = r^2
	// So, we obtain the coefficients of 't' as a, b, c and observe the discriminants.


	//Analysis for the first sphere
	float a1 = (pC.x*pC.x) + (pC.y*pC.y) + (pC.z* pC.z) + (4.0*pC.z) + 4.0;
	float b1 = (-2.0*sC1.x*pC.x) - (2.0*pC.y*sC1.y) - (4*pC.z) - (2*sC1.z*pC.z) - 8.0 - 4.0*sC1.z;
	float c1 = (sC1.x*sC1.x) + (sC1.y*sC1.y) + (sC1.z*sC1.z) + (4*sC1.z) - (sC1.r*sC1.r) + 4;

	//Analysis for the second sphere
	float a2 = (pC.x*pC.x) + (pC.y*pC.y) + (pC.z* pC.z) + (4.0*pC.z) + 4.0;
	float b2 = (-2.0*sC2.x*pC.x) - (2.0*pC.y*sC2.y) - (4.0*pC.z) - (2*sC2.z*pC.z) - 8.0 - (4.0*sC2.z);
	float c2 = (sC2.x*sC2.x) + (sC2.y*sC2.y) + (sC2.z*sC2.z) + (4.0*sC2.z) - (sC2.r*sC2.r) + 4.0;

	//Analysis for the third sphere
	float a3 = (pC.x*pC.x) + (pC.y*pC.y) + (pC.z* pC.z) + (4.0*pC.z) + 4.0;
	float b3 = (-2.0*sC3.x*pC.x) - (2.0*pC.y*sC3.y) - (4.0*pC.z) - (2.0*sC3.z*pC.z) - 8.0 - (4.0*sC3.z);
	float c3 = (sC3.x*sC3.x) + (sC3.y*sC3.y) + (sC3.z*sC3.z) + (4.0*sC3.z) - (sC3.r*sC3.r) + 4.0;

	// Discriminant of each quadratic equation
	float discriminant_1 = (b1*b1) - (4*a1*c1);
	float discriminant_2 = (b2*b2) - (4*a2*c2);
	float discriminant_3 = (b3*b3) - (4*a3*c3);

// All Imaginary discriminants as no real points obtained for each sphere.
	if(discriminant_1 < 0 && discriminant_2 < 0 && discriminant_3 < 0){
		pC.setRGB(0.0, 0.0, 0.0);
		return 0;
	}
// Intersection with the third sphere 
	else if(discriminant_1 < 0 && discriminant_2 < 0 && discriminant_3 >= 0){
		if(discriminant_3 == 0){					// Easing the compution for the point lying in the tangent of the sphere
		float t_1 = (-b3/(2.0*a3));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point is calculated after getting the 
    		float w = (10.0 - val_z)/10.0;			// value of t, so we substitute in P = Po + t*v
    		pC.setRGB(0.0, 0.0, w);
    		return 0;
		}
			float t_1 = (-b3 + sqrt(discriminant_3))/(2.0*a3);
	    	float t_2 = (-b3 - sqrt(discriminant_3))/(2.0*a3);
	    	float val_z1 = (-2.0)+(t_1*(pC.z + 2.0));   // z- coordinate of the intersection point is found and we choose one that
	    	float val_z2 = (-2.0)+(t_2*(pC.z + 2.0));	// is near from the view point to solve the problem of depth.
	    	if(val_z2 > val_z1){						
	    		float w = (10.0 - val_z1)/10.0;
    			pC.setRGB(0.0, 0.0, w);
	    		return 0;
	    	}
	    	else{
	    		
			float w = (10.0 - val_z2)/10.0;
    			pC.setRGB(0.0, 0.0, w);
	    		return 0;
	    	}
	}
// Intersection with the second sphere
	else if(discriminant_1 < 0 && discriminant_2 >= 0 && discriminant_3 < 0){
		if(discriminant_2 == 0){
			float t_1 = (-b2/(2.0*a2));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(0.0, w, 0.0);
    		return 0;
		}
			float t_1 = (-b2 + sqrt(discriminant_2))/(2.0*a2);
	    	float t_2 = (-b2 - sqrt(discriminant_2))/(2.0*a2);
	    	float val_z1 = (-2.0)+(t_1*(pC.z +2.0));   // z- coordinate of the intersection point
	    	float val_z2 = (-2.0)+(t_2*(pC.z +2.0));
	    	if(val_z2 > val_z1){
				float w = (10.0 - val_z1)/10.0;
    			pC.setRGB(0.0, w, 0.0);
	    		return 0;
	    	}
	    	else{
	    		
				float w = (10.0 - val_z2)/10.0;
    			pC.setRGB(0.0, w, 0.0);
	    		return 0;
	    	}
	}
// Intersection with the first sphere
	else if(discriminant_1 >= 0 && discriminant_2 < 0 && discriminant_3 < 0){
		if(discriminant_1 == 0){
			float t_1 = (-b1/(2.0*a1));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(w, 0.0, 0.0);
    		return 0;
		}
			float t_1 = (-b1 + sqrt(discriminant_1))/(2.0*a1);
	    	float t_2 = (-b1 - sqrt(discriminant_1))/(2.0*a1);
	    	float val_z1 = (-2.0)+(t_1*(pC.z + 2.0));   // z- coordinate of the intersection point
	    	float val_z2 = (-2.0)+(t_2*(pC.z + 2.0));
	    	if(val_z2 > val_z1){
	    		
				float w = (10.0 - val_z1)/10.0;
    			pC.setRGB(w, 0.0, 0.0);
	    		return 0;
	    	}
	    	else{
	    		
				float w = (10.0 - val_z2)/10.0;
    			pC.setRGB(w, 0.0, 0.0);
	    		return 0;
	    	}

	}
	//When there is intersection poins of 1st and 2nd sphere
	else if(discriminant_1 >= 0 && discriminant_2 >= 0 && discriminant_3 < 0){
		if(discriminant_1 == 0){
			float t_1 = (-b1/(2.0*a1));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(w, 0.0, 0.0);
    		return 0;
		}
		if(discriminant_2 == 0){
			float t_1 = (-b2/(2.0*a2));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(0.0, w, 0.0);
    		return 0;
		}
			float t_1 = (-b1 + sqrt(discriminant_1))/(2.0*a1);
	    	float t_2 = (-b1 - sqrt(discriminant_1))/(2.0*a1);

	    	float t_3 = (-b2 + sqrt(discriminant_2))/(2.0*a2);
	    	float t_4 = (-b2 - sqrt(discriminant_2))/(2.0*a2);

	    	float val_z1 = (-2.0)+(t_1*(pC.z + 2.0));   // z- coordinate of the intersection point 1
	    	float val_z2 = (-2.0)+(t_2*(pC.z + 2.0));

	    	float val_z3 = (-2.0)+(t_3*(pC.z + 2.0));   // z- coordinate of the intersection point 2
	    	float val_z4 = (-2.0)+(t_4*(pC.z + 2.0));

	    	float final_val1, final_val2;
// Comparision of the intersection points for each spheres first.	: DEPTH TEST
	    	if(val_z2 > val_z1){
	    		final_val1 = val_z1;
	    	}
	    	else{
	    		final_val1 = val_z2;
	    	}
	    	if(val_z3 > val_z4){
	    		final_val2 = val_z4;
	    	}
	    	else{
	    		final_val2 = val_z3;
	    	}
// Now we again compare against the 2 spheres to find the nearer ones : DEPTH TEST
	    	if(final_val1 > final_val2){
	    		float z_f = final_val2;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(0.0, w, 0.0);
	    	}
	    	else{
	    		float z_f = final_val1;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(w, 0.0, 0.0);
	    	}
	    	
    		return 0;
	}
//When there is intersection poins of 1st and 3rd sphere
	else if(discriminant_1 >= 0 && discriminant_2 < 0 && discriminant_3 >= 0){
		if(discriminant_3 == 0){
			float t_1 = (-b3/(2.0*a3));
	    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
	    		
	    		float w = (10.0 - val_z)/10.0;
	    		pC.setRGB(0.0, 0.0, w);
    		return 0;
		}
		if(discriminant_1 == 0){
			float t_1 = (-b1/(2.0*a1));
	    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
	    		
	    		float w = (10.0 - val_z)/10.0;
	    		pC.setRGB(0.0, w, 0.0);
    		return 0;
		}
			float t_1 = (-b3 + sqrt(discriminant_3))/(2.0*a3);
	    	float t_2 = (-b3 - sqrt(discriminant_3))/(2.0*a3);

	    	float t_3 = (-b1 + sqrt(discriminant_1))/(2.0*a1);
	    	float t_4 = (-b1 - sqrt(discriminant_1))/(2.0*a1);

	    	float val_z1 = (-2.0)+(t_1*(pC.z + 2.0));   // z- coordinate of the intersection point 3
	    	float val_z2 = (-2.0)+(t_2*(pC.z + 2.0));

	    	float val_z3 = (-2.0)+(t_3*(pC.z + 2.0));   // z- coordinate of the intersection point 1
	    	float val_z4 = (-2.0)+(t_4*(pC.z + 2.0));

	    	float final_val1, final_val2;
//: DEPTH TEST
	    	if(val_z2 > val_z1){
	    		final_val1 = val_z1;
	    	}
	    	else{
	    		final_val1 = val_z2;
	    	}
	    	if(val_z3 > val_z4){
	    		final_val2 = val_z4;
	    	}
	    	else{
	    		final_val2 = val_z3;
	    	}
	    	if(final_val1 > final_val2){      //val1 -3 val2 - 2
	    		float z_f = final_val2;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(w, 0.0, 0.0);
	    	}
	    	else{
	    		float z_f = final_val1;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(0.0, 0.0, w);
	    	}
    		return 0;
	}
	//When there is intersection poins of 3rd and 2nd sphere
	else if(discriminant_1 < 0 && discriminant_2 >= 0 && discriminant_3 >= 0){
		if(discriminant_3 == 0){
			float t_1 = (-b3/(2.0*a3));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(0.0, 0.0, w);
    		return 0;
		}
		if(discriminant_2 == 0){
			float t_1 = (-b2/(2.0*a2));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(0.0, w, 0.0);
    		return 0;
		}
			float t_1 = (-b3 + sqrt(discriminant_3))/(2.0*a3);
	    	float t_2 = (-b3 - sqrt(discriminant_3))/(2.0*a3);

	    	float t_3 = (-b2 + sqrt(discriminant_2))/(2.0*a2);
	    	float t_4 = (-b2 - sqrt(discriminant_2))/(2.0*a2);

	    	float val_z1 = (-2.0)+(t_1*(pC.z + 2.0));   // z- coordinate of the intersection point 3
	    	float val_z2 = (-2.0)+(t_2*(pC.z + 2.0));

	    	float val_z3 = (-2.0)+(t_3*(pC.z + 2.0));   // z- coordinate of the intersection point 2
	    	float val_z4 = (-2.0)+(t_4*(pC.z + 2.0));

	    	float final_val1, final_val2;
// : DEPTH TEST
	    	if(val_z2 > val_z1){
	    		final_val1 = val_z1;
	    	}
	    	else{
	    		final_val1 = val_z2;
	    	}
	    	if(val_z3 > val_z4){
	    		final_val2 = val_z4;
	    	}
	    	else{
	    		final_val2 = val_z3;
	    	}
	    	if(final_val1 > final_val2){     
	    		float z_f = final_val2;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(0.0, w, 0.0);
	    	}
	    	else{
	    		float z_f = final_val1;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(0.0, 0.0, w);
	    	}
    		return 0;
	}
//When there is intersection poins of all three spheres. Generally computing z- component of each and analyzing how far is it from the view point.
	else if(discriminant_1 >= 0 && discriminant_2 >= 0 && discriminant_3 >= 0){

		if(discriminant_1 == 0){
			float t_1 = (-b1/(2.0*a1));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(w, 0.0, 0.0);
    		return 0;
		}
		if(discriminant_2 == 0){
			float t_1 = (-b2/(2.0*a2));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(0.0, w, 0.0);
    		return 0;
		}
		if(discriminant_3 == 0){
			float t_1 = (-b3/(2.0*a3));
    		float val_z = (-2.0)+(t_1*(pC.z + 2.0)); // z- coordinate of the intersection point
    		float w = (10.0 - val_z)/10.0;
    		pC.setRGB(0.0, 0.0, w);
    		return 0;
		}
		
			float t_a1 = (-b1 + sqrt(discriminant_1))/(2.0*a1);
	    	float t_b1 = (-b1 - sqrt(discriminant_1))/(2.0*a1);

	    	float t_a2 = (-b2 + sqrt(discriminant_2))/(2.0*a2);
	    	float t_b2 = (-b2 - sqrt(discriminant_2))/(2.0*a2);

	    	float t_a3 = (-b3 + sqrt(discriminant_3))/(2.0*a3);
	    	float t_b3 = (-b3 - sqrt(discriminant_3))/(2.0*a3);

	    	float val_a1 = (-2.0)+(t_a1*(pC.z + 2.0));   // z- coordinate of the intersection point 1
	    	float val_b1 = (-2.0)+(t_b1*(pC.z + 2.0));

	    	float val_a2 = (-2.0)+(t_a2*(pC.z + 2.0));   // z- coordinate of the intersection point 2
	    	float val_b2 = (-2.0)+(t_b2*(pC.z + 2.0));

	    	float val_a3 = (-2.0)+(t_a3*(pC.z + 2.0));   // z- coordinate of the intersection point 3
	    	float val_b3 = (-2.0)+(t_b3*(pC.z + 2.0));

//				: DEPTH TEST
	    	// we have 2 z component for each, which is compared against each other to find the nearest z.
	    	float final_val1, final_val2, final_val3;

	    	if(val_b1 > val_a1){
	    		final_val1 = val_a1;
	    	}
	    	else{
	    		final_val1 = val_b1;
	    	}
	    	if(val_b2 > val_a2){
	    		final_val2 = val_a2;
	    	}
	    	else{
	    		final_val2 = val_b2;
	    	}
	    	if(val_b3 > val_a3){
	    		final_val3 = val_a3;
	    	}
	    	else{
	    		final_val3 = val_b3;
	    	}
//		: DEPTH TEST
	    	// Now After finding near z for all spheres and then we compare them to find the nearest from the viewpoint again
	    	if(final_val1 < final_val2 && final_val1 < final_val3){      
	    		float z_f = final_val1;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(w, 0.0, 0.0);
	    	}
	    	else if(final_val2 < final_val1 && final_val2 < final_val3){      
	    		float z_f = final_val2;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(0.0, w, 0.0);
	    	}
	    	else{
	    		float z_f = final_val3;
	    		float w = (10.0 - z_f)/10.0;
    			pC.setRGB(0.0, 0.0, w);
	    	}
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
	int c1 = 0, c2 = 0;
	for (float a = (1.0-(1.0/length)); a >= -1.0; a-=(2.0/length)) {
		for(float b = (-1.0+(1.0/width)); b <= 1.0; b+=(2.0/width)){
			Pixel_center[c1][c2].setxyz(b, a, 0);
			c2++;
		}
		c2 = 0;
		c1++;	
	}


	MakeScreen(length, width); // Making screen
	Point3D viewPoint;    // setting view point
	viewPoint.setxyz(0,0,-2);

	//Three different spheres
	// specification for the radius can be changed here. The x, y and z coordinates of each sphere must be changed
	// to move the object in required direction 
	Sphere sphere1(2.0, 0.0, 0.0, 6.0); // Bigger sphere  which is red
	Sphere sphere2(1.0, 0.0, -2.0, 6.5); // Blue sphere
	Sphere sphere3(1.0, 0.0, 2.0, 6.0); // Green Sphere


	// Implementing the shooting of rays
	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
			checkIntersection(Pixel_center[x1][y1], sphere1, sphere2, sphere3);
		}
	}

	// Obtaining 3d image by utilizing the ppm program
  	FILE *fp = fopen("first.ppm", "wb"); // b - binary mode 

  	(void) fprintf(fp, "P6\n%d %d\n255\n", length, width);
	for (int j = 0; j < length; j++){
	    for (int i = 0; i < length; i++){
	    	static unsigned char color[3];
		    color[0] = Pixel_center[j][i].R * 255;  // red 
		    color[1] = Pixel_center[j][i].G * 255;  // green
		    color[2] = Pixel_center[j][i].B * 255;  // blue 
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





