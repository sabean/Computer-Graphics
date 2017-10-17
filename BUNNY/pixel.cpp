/*
			
				COMPUTER GRAPHICS

			Homework Practical - 03
			  Name: Sabin Bhandari


*/

/*
	PROGRAM PROCEDURE: ONLY THEORITICAL ANALYSIS
	1. FINDING THE INDIVIDUAL EQUATION BY SOLVING THE RAY EQUATION AND IMPLICIT REPRESENTATION OF THE TRIANGLE
	2. ANALYZE THE DEPTH BY COMPARING T */


#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <iostream>
#include <algorithm> 
#include "cg.h"
#include <cctype>

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

// NOTE THAT WE HAVE T COMPONENT THAT IS GIVEN TO EACH POINT WHICH REPRESENTS :
// P = Po + tV WHERE T IS USED TO FIND THE INTERSECTION POINTS
//Class representing the point
class Point3D : public ColorRGB{
	public:
		float x, y, z; // x, y, z-cordinates of point
		double tv;
		Point3D() {
			x = 0.0;
			y = 0.0;
			z = 0.0;
			tv = 0.0;
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
		void settv(double t){
			tv = t;
		}
		double gettv(){
			return tv;
		}
		void print(){
			cout << x << "," << y << "," << z << endl;
		}
};

//Triangle class
class Triangle : public Point3D{
	public:
		Point3D A;
		Point3D B;
		Point3D C;
		Triangle(){
			A.x = 0.0;
			A.y = 0.0;
			A.z = 0.0;

			B.x = 0.0;
			B.y = 0.0;
			B.z = 0.0;

			C.x = 0.0;
			C.y = 0.0;
			C.z = 0.0;

		}
		Triangle(Point3D x1, Point3D x2, Point3D x3){
			A.x = x1.x;
			A.y = x1.y;
			A.z = x1.z;

			B.x = x2.x;
			B.y = x2.y;
			B.z = x2.z;

			C.x = x3.x;
			C.y = x3.y;
			C.z = x3.z;
		}
		void setVertex(Point3D x1, Point3D x2, Point3D x3){
			A.x = x1.x;
			A.y = x1.y;
			A.z = x1.z;

			B.x = x2.x;
			B.y = x2.y;
			B.z = x2.z;

			C.x = x3.x;
			C.y = x3.y;
			C.z = x3.z;
		}
		void tprint(){
			cout << "(" << A.x << ", " << A.y << ", " << A.z << ") ";
			cout << "(" << B.x << ", " << B.y << ", " << B.z << ") ";
			cout << "(" << C.x << ", " << C.y << ", " << C.z << ") \n";
		}
};

//METHOD DECLARATIONS
/****************************************************************************************************************/

//calculating distance
float dist(float x, float y, float z) {
    return sqrt(x*x + y*y + z*z);
}

//calculating distance
float determinant(Point3D& p1, Point3D& p2, Point3D& p3){
	float val = (p1.x*(p2.y*p3.z - p2.z*p3.y)) - (p2.x*(p1.y*p3.z - p3.y*p1.z)) + (p3.x*(p1.y*p2.z - p1.z*p2.y));
	return val;
}

//for dot product
float dotproduct(Point3D& p1, Point3D& p2) {
      float scalar = p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
      return scalar;
 }

 //calculating crossproduct
 Point3D crossproduct(Point3D& p1, Point3D& p2){
	Point3D newP;
    newP.x = p1.y*p2.z - p2.y*p1.z;
    newP.y = p2.x*p1.z - p1.x*p2.z;
    newP.z = p1.x*p2.y - p2.x*p1.y;
      
    return newP;
 }

 //Barycentric coordinates calculation
int Barycenter(Point3D& p1, Point3D& p2, Point3D& p3, Point3D& q){
	float x1, x2, x3;
	if(determinant(p1, p2, p3)==0.0)
		return 0;

	x1 = determinant(q, p2, p3)/determinant(p1, p2, p3);
	x2 = determinant(p1, q, p3)/determinant(p1, p2, p3);
	x3 = determinant(p1, p2, q)/determinant(p1, p2, p3);

	if((x1 >=0.0 && x1 <=1.0) && (x2 >=0.0 && x2 <=1.0) && (x3 >=0.0 && x3<=1.0)){
		return 1;
	}
	
	return 0;
}

//Calculate the intersection
Point3D calcIntersect(Point3D& vP, Point3D &pC, double t){

	Point3D Intersect;
	Intersect.x = vP.x + t*(pC.x - vP.x);
	Intersect.y = vP.y + t*(pC.y - vP.y);
	Intersect.z = vP.z + t*(pC.z - vP.z);

	return Intersect;

}

//calculate the minimum t value
double calcminT(vector<double>& Tval){
	double Tmin = Tval[0];
	for(unsigned int i = 1; i<Tval.size(); i++){
			if(Tval[0] > Tval[i]){
				Tmin = Tval[i];
			}
	}
	return Tmin;
}

//calculating the normal
Point3D calcNormal(Point3D& Tp1, Point3D& Tp2, Point3D& Tp3){
		

		Point3D vecAB;
    	Point3D vecAC;

    	vecAB.x = Tp2.x - Tp1.x;
    	vecAB.y = Tp2.y - Tp1.y;
    	vecAB.z = Tp2.z - Tp1.z;

    	vecAC.x = Tp3.x- Tp1.x;
    	vecAC.y = Tp3.y - Tp1.y;
    	vecAC.z = Tp3.z - Tp1.z;

    	Point3D Nt;

    	Nt = crossproduct(vecAB, vecAC);
    	return Nt;
}


void checkIntersection(Point3D& pC, Point3D& vP, Triangle* &Tri, int num){	
	float Tval;
	
	bool check = false;
	vector<double> TT;
	for(int i=0; i< num; i++){

		Point3D Tp1 = Tri[i].A;
		Point3D Tp2 = Tri[i].B;
		Point3D Tp3 = Tri[i].C;

		// Creating Normal
		Point3D Nt;
		Nt = calcNormal(Tp1, Tp2, Tp3);


		
		float TvalNum = -(Nt.x*(vP.x - Tp1.x) + Nt.y*(vP.y - Tp1.y) + Nt.z*(vP.z - Tp1.z));
		float TvalDen = Nt.x*(pC.x - vP.x) + Nt.y*(pC.y - vP.y) + Nt.z*(pC.z - vP.z);

		if(TvalDen == 0){
			return;
		}

		//calculation of the values of t
		Tval = (TvalNum/TvalDen);
		
		//	intersection points
		Point3D P_intersect;
		P_intersect = calcIntersect(vP, pC, Tval);

		//res stores 1 if it is in the barycenter else 0
		int res;
		res = Barycenter(Tp1, Tp2, Tp3, P_intersect);
		
		// pushing the value of t in a vector
		if(res == 1 && Tval>0){
			TT.push_back(Tval);
			check = true;
		}
		
	}
	// if not intersected, the value -111.0 is given to the t component of the point
	if(check == false){
		pC.settv(-111.0);
		return;
	}
	// if intersected t is given to the point which can be later used to find intersection point
	double t = 0.0;
	//for(unsigned int i = 0; i<TT.size(); i++)
	//	cout << TT[i] << "    ";
	cout << endl;
	t = calcminT(TT);
	cout << t << endl;
	pC.settv(t);

}



//MAIN PROGRAM
/*********************************************************************************************************************/

int main(void)
{

	//Input specifications
	int length = 0, width = 0;

	cout << "Enter desired Resolution: " << endl;
	cin >> length >> width;

	if(length != width){
		cout << "Unsymmetrical division of pixel!!!!!" << endl;
		return 0;
	}

	// Loading bunny from the header file
	vector <glm::vec3> vertices;
    bool res = loadOBJ("bunny.obj", vertices);
    if(res == false){
    	return 0;
    }

    // size of the vertices
    cout << vertices.size() << endl;;


    // Triangle construction 
    int sizeT = vertices.size();
    int numTri = sizeT/3;

    Triangle *tri;
	tri = new Triangle[numTri];

	//vector specifications
	std::vector<float> vecx;	//all the x coordinates 
	std::vector<float> vecy;	//all the y coordinates
	std::vector<float> vecz;	//all the z coordinates

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


    }
    
    //Mapping mechanism


    // filding maximum and minimum x, y, and z.
    float Xmax, Xmin, Ymax, Ymin, Zmax, Zmin;

    Xmin = *min_element(vecx.begin(), vecx.end());
    Xmax = *max_element(vecx.begin(), vecx.end());

    Ymin = *min_element(vecy.begin(), vecy.end());
    Ymax = *max_element(vecy.begin(), vecy.end());

    Zmin = *min_element(vecz.begin(), vecz.end());
    Zmax = *max_element(vecz.begin(), vecz.end());

    //finding the slopes
    float mX, mY, mZ;

    //finding the y intercepts
    float cX, cY, cZ;

    mX = -2.0/(Xmin-Xmax);
    cX = 1 - mX*Xmax;

    mY = 2.0/(Ymax - Ymin);
    cY = 1 - mY*Ymax;

    mZ = -2.0/(Zmin-Zmax);
    cZ = -mZ*Zmin;

    //map points that map our point to the range of the frustum 
    // for x and y it's -1 to 1
    // for z its 0 to 6
    Point3D *mapPoint;
	mapPoint = new Point3D[sizeT];

    for(int i = 0; i < sizeT; i++){
    	if(mapPoint[i].x >= -1.0 && mapPoint[i].x <= 1.0)
    		mapPoint[i].x = mX*vecx[i] + cX;
    	if(mapPoint[i].y >= -1.0 && mapPoint[i].y <= 1.0)
    		mapPoint[i].y = mY*vecy[i] + cY;
    	if(mapPoint[i].z >= 0.0 && mapPoint[i].z <= 2.0)
    		mapPoint[i].z = mZ*vecz[i] + cZ;
    }

    // storing mapped points to the triangle
 
    for(int i=0; i < numTri; i++){

    	tri[i].setVertex(mapPoint[3*i], mapPoint[3*i+1], mapPoint[3*i+2]);

    }

    // center of each pixels

    Point3D **Pixel_center;

	Pixel_center = new Point3D*[length];
	for(int y = 0; y < length; y++){
		Pixel_center[y] = new Point3D[width];
	}

    int c1 = 0, c2 = 0;
	for (float a = (1.0-(1.0/length)); a >= -1.0; a-=(2.0/length)) {
		for(float b = (-1.0+(1.0/width)); b <= 1.0; b+=(2.0/width)){
			Pixel_center[c1][c2].setxyz(b, a, 0);
			c2++;
		}
		c2 = 0;
		c1++;	
	}
	// setting viewpoints
    Point3D viewPoint;    
	viewPoint.setxyz(0,0,-2);


	// Calculating T
	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
				checkIntersection(Pixel_center[x1][y1], viewPoint, tri, numTri);
			}
	}

	// Resulting points where we store the color RGB
	Point3D **result;

	result = new Point3D*[length];
	for(int y = 0; y < length; y++){
		result[y] = new Point3D[width];
	}
	
	// main function to calcuate the intersection point where we get t, it will set black if no valid value of t i.e. -111.0
	//else it will find intersection point as per it's t value and then color it.
	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
			if(Pixel_center[x1][y1].tv == -111.0)
				result[x1][y1].setRGB(0.0, 0.0, 0.0);
			else{
				result[x1][y1] = calcIntersect(viewPoint, Pixel_center[x1][y1], Pixel_center[x1][y1].tv); 
				result[x1][y1].setRGB(((6.0+result[x1][y1].x)/12.0), ((6.0+result[x1][y1].y)/12.0), ((10.0-result[x1][y1].z)/10.0));
			}
		}
	}

		// Obtaining 3d image by utilizing the ppm program



	  FILE *fp = fopen("second.ppm", "wb"); // b - binary mode 

	  (void) fprintf(fp, "P6\n%d %d\n255\n", length, width);
		for (int j = 0; j < length; j++){
		    for (int i = 0; i < length; i++){
		    	static unsigned char color[3];
			    color[0] = result[j][i].R * 255;  // red 
			    color[1] = result[j][i].G * 255;  // green
			    color[2] = result[j][i].B * 255;  // blue 
			    (void) fwrite(color, 1, 3, fp);
		    }
		 }
	  (void) fclose(fp); 



	 // Deallocating the pixel 
	for(int i = 0; i < length; i++){
		delete [] Pixel_center[i];
	}
	delete [] Pixel_center;

	for(int i = 0; i < length; i++){
		delete [] result[i];
	}
	delete [] result;

	delete [] tri;
	delete [] mapPoint;
	
  return EXIT_SUCCESS;

}





