#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <iostream>
#include <algorithm> 
#include <utility>
#include <cctype>

using namespace std;



//Colour class
class ColorRGB {
	public:
		float R, G, B, A; // correspondingly Red, Green and blue.
		ColorRGB(){
			R = 0.0; G = 0.0; B = 0.0; A = 0.0;
		}
		ColorRGB(float a, float b, float c, float d){
			R = a; G = b; B = c; A = d;
		}
		void setRGBA(float red, float green, float blue, float amb) {
			R = red; G = green; B = blue; A = amb;
		}
		bool checkBG(){
			if(R == 0 && G == 0 && B == 0)
				return true;
			else 
				return false;
		}
		ColorRGB operator *(const float &f) const { return  ColorRGB(f*R, f*G, f*B, f*A); } 
		ColorRGB operator +(const ColorRGB &obj)const{
			ColorRGB res;
 	    	res.R = this->R + obj.R; res.G = this->G + obj.G; res.B = this->B + obj.B; res.A = this->A + obj.A;
 	    	return res;
 	    } 
		void printColor(){
			cout << "(" << R << " ," << G << " ," << B << " ," << A  << " )" << endl;
		}

};

class Point3D : public ColorRGB {
	public:
		float x, y, z; // x, y, z-cordinates of point
		float n_x, n_y, n_z; // x, y, z-cordinates of normals

		Point3D() {
			x = 0.0; y = 0.0; z = 0.0;
			n_x = 0.0; n_y = 0.0; n_z = 0.0;
		}

		Point3D(float a, float b, float c){
			x = a; y = b; z = c;
		}

		Point3D(float a, float b, float c, float a1, float b1, float c1){
			x = a; y = b; z = c;
			n_x = a1; n_y = b1; n_z = c1;
		}
		Point3D(const Point3D &obj) {
   			x = obj.x; y = obj.y; z = obj.z;
   			n_x = obj.n_x; n_y = obj.n_y; n_z = obj.n_z;

		}
		Point3D operator +(const Point3D &obj)const{
			Point3D res;
 	    	res.x = this->x + obj.x; res.y = this->y + obj.y; res.z = this->z + obj.z;
 	    	return res;
 	    } 
 	    Point3D operator -(const Point3D &obj)const{
			Point3D res;
 	    	res.x = this->x - obj.x; res.y = this->y - obj.y; res.z = this->z - obj.z;
 	    	return res;
 	    } 
 	     Point3D operator *(const Point3D &obj)const{
			Point3D res;
 	    	res.x = this->x * obj.x; res.y = this->y * obj.y; res.z = this->z * obj.z;
 	    	return res;
 	    } 
 	    float lengthSQ() const { return x * x + y * y + z * z;} 
 	    Point3D normalize(){ 
         	float nor2 = lengthSQ(); 
	        if (nor2 > 0) { 
	            float invNor = 1 / sqrt(nor2); 
	            x *= invNor, y *= invNor, z *= invNor; 
	        } 
        	return *this; 
   		} 

 	    Point3D operator * (const float &f) const { return  Point3D(x * f, y * f, z * f); } 

 	    float dot(const Point3D &v) const { return (x*v.x + y*v.y + z*v.z); }

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
		void printP(){
			cout << "Point:  " << x << "," << y << "," << z << endl;
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
			ambient[i] = amb[i]; diffuse[i] = diff[i];
		}
		position.x = pos.x; position.y = pos.y; position.z = pos.z;
	}
	float getLx(){return position.x;}
	float getLy(){return position.y;}
	float getLz(){return position.z;}
};

class Sphere : public Point3D{
	public:
		float r;	// radius
		float a_rf;
		float b_tr;
		float n_index;
		float matAmbient[4]; float matDiffuse[4]; float matSpecular[4];
		float SRE;
		Point3D center;

	    Sphere(){
	    	r = 0.0;
	    	a_rf = 0.0; b_tr= 0.0;
	    	n_index = 0.0;
	    	center.x = 0.0; center.y = 0.0; center.z = 0.0;	
	    }
	    Sphere(float r1, float cx, float cy, float cz) {
	    	r = r1;
	    	center.x = cx; center.y = cy; center.z = cz;
 	    }
 	    bool checkMirroring(){if(a_rf != 0){return true;}
 	    	return false;
 	    }
 	    bool checkTransparency(){if(b_tr != 0){return true;}
 	    	return false;
 	    }
 	    float getA(){return a_rf;}
 	    float getB(){return b_tr;}
 	    float getN(){return n_index;}
 	    void setMatAmbient(float a, float b, float c, float d){
 	    	matAmbient[0] = a; matAmbient[1] = b; matAmbient[2] = c; matAmbient[3] = d;
 	    }
 	    void setMatDiffuse(float a, float b, float c, float d){
 	    	matDiffuse[0] = a; matDiffuse[1] = b; matDiffuse[2] = c; matDiffuse[3] = d;
 	    }
 	    void setMatSpecular(float a, float b, float c, float d){
 	    	matSpecular[0] = a; matSpecular[1] = b; matSpecular[2] = c; matSpecular[3] = d;
 	    }
 	    void setSRE(float a){SRE = a;}
 	    void printSphere(){
 	    	cout << endl;
 	    	cout << "_____" << a_rf << "_____" << b_tr << endl;
 	    	cout << endl;
 	    }
	 	float Intersection(Point3D &vp, float& t, Point3D& IP, Point3D& Normal, Point3D& vecdir){  
			//Analysis for the first sphere
			Point3D VPC = vp - center;

			float a1 = (vecdir.x * vecdir.x) + (vecdir.y * vecdir.y) + (vecdir.z * vecdir.z);
			float b1 = 2*((vecdir.x * VPC.x) + (vecdir.y * VPC.y) + (vecdir.z * VPC.z));
			float c1 = (vp.x*vp.x) + (vp.y*vp.y) + (vp.z*vp.z) - 2*((vp.x*center.x) + (vp.y*center.y) + (vp.z*center.z)) -(r*r) + (center.x*center.x) + (center.y*center.y) + (center.z*center.z);

			// Discriminant of quadratic equation
			float discriminant_1 = (b1*b1) - (4.0*a1*c1);

			// All Imaginary discriminants as no real points obtained for each sphere.
			if(discriminant_1 < 0.0){
				return 0;
			}
			// Intersection with the first sphere
			else if(discriminant_1 >= 0){
				// Calculation of value of t
			    float t_1 = (-b1 - sqrt(discriminant_1))/(2.0*a1);
			    float t_2 = (-b1 + sqrt(discriminant_1))/(2.0*a1);
			    t = min(t_1, t_2);
			    //intersection points
			    IP = vp + (vecdir*t);
			    Normal = IP - center;
			    	return 1;
			}
			else{return 0;}
		}
};

