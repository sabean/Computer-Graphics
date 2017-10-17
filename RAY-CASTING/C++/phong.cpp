/*
			
				COMPUTER GRAPHICS

			Homework Practical - 07
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
#include <utility>
#include "sphereHead.h"
#include <cctype>

using namespace std;

//CLASS DECLARATIONS

/****************************************************************************************************/

//material properties
float matAmbient[4] = {1.0,1.0,1.0,1.0};
float matDiffuse[4] = {0.8,0.8,0.8,1.0};
float matSpecular[4] = {0.5,0.5,0.5,1.0};
float SRE = 10;


//Colour class
class ColorRGB {
	public:
		float R, G, B, AM; // correspondingly Red, Green and blue.
		ColorRGB(){}
		void setRGBA(float red, float green, float blue, float amb) {
				R = red;
				G = green;
				B = blue;
				AM = amb;
		}
};

// NOTE THAT WE HAVE T COMPONENT THAT IS GIVEN TO EACH POINT WHICH REPRESENTS :
// P = Po + tV WHERE T IS USED TO FIND THE INTERSECTION POINTS
//Class representing the point
// Point3D specifications

class Point3D : public ColorRGB {
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
		Point3D(const Point3D &obj) {
   			x = obj.x;
   			y = obj.y;
   			z = obj.z;
   			n_x = obj.n_x;
   			n_y = obj.n_y;
   			n_z = obj.n_z;

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

//Triangle class with VERTICES and NORMAL
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
		Triangle(const Triangle &obj) {
   			A = obj.A;
   			B = obj.B;
   			C = obj.C;
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
//Light class which has specification on the ambience and diffusion
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
/****************************************************************************************************************/
// Add points
Point3D addPoints(Point3D a, Point3D b){
	Point3D res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}

//scalar point multiplication
Point3D scalarPoint(float a, Point3D n){
	Point3D res;
	res.x = a * n.x;
	res.y = a * n.y;
	res.z = a * n.z;

	return res;

}

 //calculating crossproduct
 Point3D crossproduct(Point3D& p1, Point3D& p2){
	Point3D newP;
    newP.x = p1.y*p2.z - p2.y*p1.z;
    newP.y = p2.x*p1.z - p1.x*p2.z;
    newP.z = p1.x*p2.y - p2.x*p1.y;
      
    return newP;
 }
// Normalize the vector
float Norm(Point3D v){
	float rval = 0.0;
	rval = sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
	return rval;

}
//convert two points into vector
Point3D vectorize(Point3D M, Point3D N){
	Point3D MN;
	MN.x = N.x - M.x;
	MN.y = N.y - M.y;
	MN.z = N.z - M.z;
	return MN;

}
//for dot product
float dotProduct(Point3D& p1, Point3D& p2) {
      float scalar = p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
      return scalar;
 }
// Calculating the H factor of the point
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
// Calculate N by the help of barycenter and the normals of the each side of the triangle
Point3D calcN(Point3D A, Point3D B, Point3D C, Point3D bary){
	Point3D normal;

	normal = addPoints(addPoints(scalarPoint(bary.x, A), scalarPoint(bary.y, B)), scalarPoint(bary.z, C));

	float len = Norm(normal);
	normal.x = normal.x / len;
	normal.y = normal.y / len;
	normal.z = normal.z / len;

	return normal;

}
//calculating distance
float dist(float x, float y, float z) {
    return sqrt(x*x + y*y + z*z);
}

//calculating determinant
float determinant(Point3D& p1, Point3D& p2, Point3D& p3){
	float val = (p1.x*(p2.y*p3.z - p2.z*p3.y)) - (p2.x*(p1.y*p3.z - p3.y*p1.z)) + (p3.x*(p1.y*p2.z - p1.z*p2.y));
	return val;
}


 //Barycentric coordinates calculation
int Barycenter(Point3D& p1, Point3D& p2, Point3D& p3, Point3D& q, Point3D& bary){
	float x1, x2, x3;
	x1 = determinant(q, p2, p3)/determinant(p1, p2, p3);
	x2 = determinant(p1, q, p3)/determinant(p1, p2, p3);
	x3 = determinant(p1, p2, q)/determinant(p1, p2, p3);

	if((x1 >=0.0 && x1 <=1.0) && (x2 >=0.0 && x2 <=1.0) && (x3 >=0.0 && x3<=1.0)){
		bary.setxyz(x1, x2, x3);
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
// Calculating the L component
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
// Calculating the V component
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


// Bling Phong illumination Model

float blinn_phong(vector<Light>& LS, Point3D& IP, Point3D& vp, Point3D& Normal, int RGBA){

	float phongAmbient = LS[0].ambient[RGBA] * matAmbient[RGBA];
	float phongSpecular = 0;

	for(unsigned int i = 0 ; i < LS.size() ; i++){

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
	float valTotal = phongAmbient + phongSpecular;
	return valTotal;
}


void checkIntersection(Point3D& pC, Point3D& vP, Triangle* &Tri, int num, vector<Light>& LS){	
	float Tval;
	
	bool check = false;
	vector<double> TT;
	vector<pair<float, Triangle> > Tpair; 		// inorder to know the t associated to the triangle

	Point3D bary;
	for(int i=0; i< num; i++){
		// Three vertices of the triangle
		Point3D Tp1 = Tri[i].A;
		Point3D Tp2 = Tri[i].B;
		Point3D Tp3 = Tri[i].C;

		// Creating Normal
		Point3D Nt;
		Nt = calcNormal(Tp1, Tp2, Tp3);
		
		float TvalNum = -(Nt.x*(vP.x - Tp1.x) + Nt.y*(vP.y - Tp1.y) + Nt.z*(vP.z - Tp1.z));
		float TvalDen = Nt.x*(pC.x - vP.x) + Nt.y*(pC.y - vP.y) + Nt.z*(pC.z - vP.z);

		if(TvalDen == 0){
			pC.setRGBA(0.0, 0.0, 0.0, 0.0);
			return;
		}
		//calculation of the values of t
		Tval = (TvalNum/TvalDen);
		
		//	intersection points
		Point3D P_intersect;
		P_intersect = calcIntersect(vP, pC, Tval);

		//res stores 1 if it is in the barycenter else 0
		int res;
		
		res = Barycenter(Tp1, Tp2, Tp3, P_intersect, bary);
		
		// pushing the value of t in a vector
		if(res == 1 && Tval>=0){
			TT.push_back(Tval);
			Tpair.push_back(make_pair(Tval, Tri[i]));
			check = true;
		}
		
	}
	// if not intersected, the value -111.0 is given to the t component of the point
	if(check == false){
		pC.setRGBA(0.0, 0.0, 0.0, 0.0);
		return;
	}
	// if intersected t is given to the point which can be later used to find intersection point
	Triangle TRI;
	double t = 0.0;
	// Calculating the min t-----DEPTH TEST
	t = calcminT(TT);
	// finding the triangle associated to the given t value
	for(unsigned int i = 0; i < Tpair.size(); i++){
		if(t == Tpair[i].first){
			TRI = Tpair[i].second;
		}
	}
	// Calculation of the intersection point
	Point3D IP;
	IP = calcIntersect(vP, pC, t);
	// Calculation of the Normal by considering the triangle vertices and the barycenter
	Point3D Normal;
	Normal = calcN(TRI.A, TRI.B, TRI.C, bary);
	//Phongs illumination model for different RGB value
	float Rval = blinn_phong(LS, IP, vP, Normal, 0);
	if(Rval > 1) Rval = 1;
	float Gval = blinn_phong(LS, IP, vP, Normal, 1);
	if(Gval > 1) Gval = 1;
	float Bval = blinn_phong(LS, IP, vP, Normal, 2);
	if(Bval > 1) Bval = 1;
	float Aval = blinn_phong(LS, IP, vP, Normal, 3);
	if(Aval > 1) Aval = 1;
	//Setting the RGB value
	pC.setRGBA(Rval, Gval, Bval, Aval);
	//Deallocating the memory for effecient programming
	TT.clear();
	Tpair.clear();

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
	vector <glm::vec3> normal;
    bool res = loadOBJ("suzanne.obj", vertices, normal);
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
	std::vector<float> vec1x;	//all the x coordinates of normals
	std::vector<float> vec1y;	//all the y coordinates of normals
	std::vector<float> vec1z;	//all the z coordinates of normals

    for(int i=0; i < numTri; i++){

    	vecx.push_back(-vertices[3*i].x);
    	vecy.push_back(vertices[3*i].y);
    	vecz.push_back(-vertices[3*i].z);

    	vecx.push_back(-vertices[3*i+1].x);
    	vecy.push_back(vertices[3*i+1].y);
    	vecz.push_back(-vertices[3*i+1].z);

    	vecx.push_back(-vertices[3*i+2].x);
    	vecy.push_back(vertices[3*i+2].y);
    	vecz.push_back(-vertices[3*i+2].z);

    	vec1x.push_back(-normal[3*i].x);
    	vec1y.push_back(normal[3*i].y);
    	vec1z.push_back(-normal[3*i].z);

    	vec1x.push_back(-normal[3*i+1].x);
    	vec1y.push_back(normal[3*i+1].y);
    	vec1z.push_back(-normal[3*i+1].z);

    	vec1x.push_back(-normal[3*i+2].x);
    	vec1y.push_back(normal[3*i+2].y);
    	vec1z.push_back(-normal[3*i+2].z);


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

   		mapPoint[i].x = mX*vecx[i] + cX;
   		mapPoint[i].y = mY*vecy[i] + cY;
   		mapPoint[i].z = mZ*vecz[i] + cZ;
    	mapPoint[i].n_x = vec1x[i]/mX;		//NORMAL ALSO CHANGES SO ADJUSTING THE NORMAL
    	mapPoint[i].n_y = vec1y[i]/mY;
    	mapPoint[i].n_z = vec1z[i]/mZ;
    }
    vecx.clear();vecy.clear();vecz.clear();
    vec1x.clear();vec1y.clear();vec1z.clear();
    // storing mapped points to the triangle
 
    for(int i=0; i < numTri; i++){

    	tri[i].setVertex(mapPoint[3*i], mapPoint[3*i+1], mapPoint[3*i+2]);
    	tri[i].setNormal(mapPoint[3*i], mapPoint[3*i+1], mapPoint[3*i+2]);

    }

    // Definations for light sources

	Point3D lightsource1;
	Point3D lightsource2;
	Point3D lightsource3;

	// Setting up the position of the light
	lightsource1.setxyz(2.0, 3, 3);
	lightsource2.setxyz(-3.0, -1.8, 3);
	lightsource3.setxyz(0.0, -3.0, 3);

	//lightsource4.setxyz(-5.0, -5.0, -1);
	//Ambient
	float amb[4] = {0,0,0,1};

	//Lights and their properties
	float diff1[4] = {0.0,0.0,1,1};
	Light Light0(amb, diff1, lightsource1);		// BLUE LIGHT

	float diff2[4] = {1,0.0,0.0,1};
	Light Light1(amb, diff2, lightsource2);		//RED LIGHT

	float diff3[4] = {0.0,1,0.0,1};
	Light Light2(amb, diff3, lightsource3);		//GREEN LIGHT

	// vector of lights
	vector<Light> vecLights;
	vecLights.push_back(Light0);
	vecLights.push_back(Light1);
	vecLights.push_back(Light2);


    // center of each pixels
    Point3D **Pixel_center;

    //Setting up the pixel center
	Pixel_center = new Point3D*[length];
	for(int y = 0; y < length; y++){
		Pixel_center[y] = new Point3D[width];
	}
	//calculating the centers
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


	// Calculating T by intersection checking
	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
				checkIntersection(Pixel_center[x1][y1], viewPoint, tri, numTri, vecLights);
			}
	}

	// Obtaining 3d image by utilizing the ppm program
	FILE *fp = fopen("suzanne.ppm", "wb"); // b - binary mode 

	(void) fprintf(fp, "P6\n%d %d\n255\n", length, width);
		for (int j = 0; j < length; j++){
		    for (int i = 0; i < length; i++){
		    	static unsigned char color[3];
		    	color[0] = (unsigned char) floor(Pixel_center[j][i].AM * Pixel_center[j][i].R * 255);  // red 
		    	color[1] = (unsigned char) floor(Pixel_center[j][i].AM * Pixel_center[j][i].G * 255);  // green
		    	color[2] = (unsigned char) floor(Pixel_center[j][i].AM * Pixel_center[j][i].B * 255);  // blue 
			    (void) fwrite(color, 1, 3, fp);
		    }
		 }
	  (void) fclose(fp); 



	 // Deallocating the pixel 
	for(int i = 0; i < length; i++){
		delete [] Pixel_center[i];
	}
	delete [] Pixel_center;

	delete [] tri;
	delete [] mapPoint;
	
  return EXIT_SUCCESS;

}





