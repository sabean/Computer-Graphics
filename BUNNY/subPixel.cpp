/*
			
				COMPUTER GRAPHICS

			Homework Practical - 03
			  Name: Sabin Bhandari


			THE COMMENTS HAS BEEN PLACED IN pixel.cpp

			SO ONLY ADDITIONAL COMMENTS ARE PLCED HERE WHERE NECESSARY

*/



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

//Class that creates a pixel: I CREATED A WHOLE NEW CLASS CALLED PIXEL

class Pixel :public Point3D{
	public:
		float side;
		Point3D center;

		Pixel(){
			side = 0.0;
			center.x = 0.0;
			center.y = 0.0;
			center.z = 0.0;

		}
		void setpix(Point3D val){
			center.x = val.x;
			center.y = val.y;
			center.z = 0.0;
		}
		void setCenter(float vx, float vy, float vz){
			center.x = vx;
			center.y = vy;
			center.z = vz;
		}


		float getx(){
			return center.x;
		}
		float gety(){
			return center.y;
		}
		void printpix(){
			cout << "(" << center.x << ", " << center.y << ", " << center.z << ") \n";
		}

};
//METHOD DECLARATIONS
/****************************************************************************************************************/
float dist(float x, float y, float z) {
    return sqrt(x*x + y*y + z*z);
}



float determinant(Point3D& p1, Point3D& p2, Point3D& p3){
	float val = (p1.x*(p2.y*p3.z - p2.z*p3.y)) - (p2.x*(p1.y*p3.z - p3.y*p1.z)) + (p3.x*(p1.y*p2.z - p1.z*p2.y));
	return val;
}
float dotproduct(Point3D& p1, Point3D& p2) {
      float scalar = p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
      return scalar;
 }

Point3D crossproduct(Point3D& p1, Point3D& p2){
	Point3D newP;
    newP.x = p1.y*p2.z - p2.y*p1.z;
    newP.y = p2.x*p1.z - p1.x*p2.z;
    newP.z = p1.x*p2.y - p2.x*p1.y;
      
    return newP;
 }

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

Point3D calcIntersect(Point3D& vP, Point3D &pC, double t){

	Point3D Intersect;
	Intersect.x = vP.x + t*(pC.x - vP.x);
	Intersect.y = vP.y + t*(pC.y - vP.y);
	Intersect.z = vP.z + t*(pC.z - vP.z);

	return Intersect;

}

double calcminT(vector<double>& Tval){
	double Tmin = Tval[0];
	for(unsigned int i = 1; i<Tval.size(); i++){
			if(Tval[0] > Tval[i]){
				Tmin = Tval[i];
			}
	}
	return Tmin;
}


double calcAVG(double Tval, int num){
	return (Tval/num);
}


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

// This function breaks a pixels on the basis of its center. This takes in 1 pixel and breaks it into
// its own 4 sub pixels and pushes it into a vector of pixels

void computeSub(vector<Pixel>& subPix, float cx, float cy, float l){
		Pixel px1;
		Pixel px2;
		Pixel px3;
		Pixel px4;

		px1.setCenter(cx-(l/2), cy + (l/2), 0.0);
		px2.setCenter(cx+(l/2), cy + (l/2), 0.0);
		px3.setCenter(cx-(l/2), cy - (l/2), 0.0);
		px4.setCenter(cx+(l/2), cy - (l/2), 0.0);

		subPix.push_back(px1);
		subPix.push_back(px2);
		subPix.push_back(px3);
		subPix.push_back(px4);
}

//SIMILAR TO pixel.cpp
void checkIntersection(Pixel& spix, Point3D& vP, Triangle* &Tri, int num){	
	float Tval;
	bool check = false;
	Point3D pC;
	pC.x = spix.center.x;
	pC.y = spix.center.y;
	pC.z =0.0;
	
	vector<double> TT;

	for(int i=0; i< num; i++){

		Point3D Tp1 = Tri[i].A;
		Point3D Tp2 = Tri[i].B;
		Point3D Tp3 = Tri[i].C;

		
		Point3D Nt;
		Nt = calcNormal(Tp1, Tp2, Tp3);

		
		float TvalNum = -(Nt.x*(vP.x - Tp1.x) + Nt.y*(vP.y - Tp1.y) + Nt.z*(vP.z - Tp1.z));
		float TvalDen = Nt.x*(pC.x - vP.x) + Nt.y*(pC.y - vP.y) + Nt.z*(pC.z - vP.z);


		if(TvalDen == 0){
			spix.settv(-111.0);
			return;
		}
		Tval = (TvalNum/TvalDen);

		Point3D P_intersect;
		P_intersect = calcIntersect(vP, pC, Tval);

		int res;
		res = Barycenter(Tp1, Tp2, Tp3, P_intersect);
		
		if(res == 1){
			TT.push_back(Tval);
			check = true;
		}
	}
	
	if(check == false){
		spix.settv(-111.0);
		return;
	}

	double t = 0.0;
	t = calcminT(TT);
	spix.settv(t);
	
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
//bunny1
	vector <glm::vec3> vertices;
	//std::vector< glm::vec2 > uvs;
	//std::vector< glm::vec3 > normals;
    bool res = loadOBJ("bunny.obj", vertices);
    if(res == false){
    	return 0;
    }
    cout << vertices.size() << endl;;

    // Triangle construction 

    int sizeT = vertices.size();
    int numTri = sizeT/3;

    Triangle *tri;
	tri = new Triangle[numTri];

	// colection of x y and z coordinates
	std::vector<float> vecx;
	std::vector<float> vecy;
	std::vector<float> vecz;
	


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
   // Mapping Mechanism
    float Xmax, Xmin, Ymax, Ymin, Zmax, Zmin;

    Xmin = *min_element(vecx.begin(), vecx.end());
    Xmax = *max_element(vecx.begin(), vecx.end());

    Ymin = *min_element(vecy.begin(), vecy.end());
    Ymax = *max_element(vecy.begin(), vecy.end());

    Zmin = *min_element(vecz.begin(), vecz.end());
    Zmax = *max_element(vecz.begin(), vecz.end());


    float mX, mY, mZ;
    float cX, cY, cZ;

    mX = -2.0/(Xmin-Xmax);
    cX = 1 - mX*Xmax;

    mY = 2.0/(Ymax - Ymin);
    cY = 1 - mY*Ymax;

    mZ = -2.0/(Zmin-Zmax);
    cZ = -mZ*Zmin;


    // Mapping points

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
 
    for(int i=0; i < numTri; i++){

    	tri[i].setVertex(mapPoint[3*i], mapPoint[3*i+1], mapPoint[3*i+2]);

    }

    Point3D viewPoint;    
	viewPoint.setxyz(0,0,-2);

	float subLen = (1.0/length);


	//Creating pixels
	Pixel **PIX;

	PIX = new Pixel*[length];
	for(int y = 0; y < length; y++){
		PIX[y] = new Pixel[width];
	}
	 

	int c1 = 0, c2 = 0;
	for (float a = (1.0-(1.0/(length))); a >= -1.0; a-=(2.0/(length))) {
		
		for(float b = (-1.0+(1.0/(length))); b <= 1.0; b+=(2.0/(length))){
			PIX[c1][c2].setCenter(b, a, 0);
			c2++;
			
		}
		c2 = 0;
		c1++;	

	}
	// creating the vector of pixels
	vector<Pixel> subPix;

	for(int i = 0; i < length; i++){
		for(int j = 0; j <length; j++){
			computeSub(subPix, PIX[i][j].getx(), PIX[i][j].gety(), subLen);
		}
	}    


	int count=0;

	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
			for(int k = 0; k < 4; k++){
				checkIntersection(subPix[count], viewPoint, tri, numTri);
				count++;
			}

		}
		
	}



	Point3D **result;

	result = new Point3D*[length];
	for(int y = 0; y < length; y++){
		result[y] = new Point3D[width];
	}

	// Mechanism: inner for loop to traverse in the subpixels calculating the average t
	count = 0;
	int count2 = 0;
	double sumT = 0.0;

// ADDITIONAL FOR LOOP FROM 1 TO 4 IS USED TO TRAVERSE THE SUB PIXELS MAINTED BY THE INDEX: COUNT
//RESULT IS KEPT IN RESULT[I][J]
//COUNT2 COUNTS IF THERE IS PRESENCE OF VALID T OR NOT
// IF COUNT2 IS 0, ITS BLACK
//IF COUNT2 IS 1 ITS 25% COLOR, IF 2 ITS 50% COLOR IF 3 ITS 75% IF 4 ITS 100% COLOR
// SUMT WILL HOLD SUM OF T FOR GETTING AVERAGE T FOR THE WHOLE PIXEL



	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
			for(int k = 0; k < 4; k++){
				if(subPix[count].tv != -111.0){
					sumT += subPix[count].tv;
					count2++;
				}
				count++;
			}
			if(count2 == 0){
				result[x1][y1].setRGB(0.0, 0.0, 0.0);	
			}
			else{
				double AvalT = calcAVG(sumT, count2);
				result[x1][y1] = calcIntersect(viewPoint, PIX[x1][y1], AvalT); 
				if(count2 == 1)
					result[x1][y1].setRGB(0.25*((6.0+result[x1][y1].x)/12.0), 0.25*((6.0+result[x1][y1].y)/12.0), 0.25*((10.0-result[x1][y1].z)/10.0));
				if(count2 == 2)
					result[x1][y1].setRGB(0.5*((6.0+result[x1][y1].x)/12.0), 0.5*((6.0+result[x1][y1].y)/12.0), 0.5*((10.0-result[x1][y1].z)/10.0));
				if(count2 == 3)
					result[x1][y1].setRGB(0.75*((6.0+result[x1][y1].x)/12.0), 0.75*((6.0+result[x1][y1].y)/12.0), 0.75*((10.0-result[x1][y1].z)/10.0));
				if(count2 == 4)
					result[x1][y1].setRGB(((6.0+result[x1][y1].x)/12.0), ((6.0+result[x1][y1].y)/12.0), ((10.0-result[x1][y1].z)/10.0));	
			}
			sumT = 0.0;
			count2 = 0.0;
		}
	}
	


		// Obtaining 3d image by utilizing the ppm program



	  FILE *fp = fopen("first.ppm", "wb"); // b - binary mode 

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
		delete [] PIX[i];
	}
	delete [] PIX;


	for(int i = 0; i < length; i++){
		delete [] result[i];
	}
	delete [] result;

	delete [] tri;
	delete [] mapPoint;
	
  return EXIT_SUCCESS;

}





