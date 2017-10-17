// SABIN BHANDARI

#include <iostream>
#include <vector>
#include <algorithm>
#include "points.h"


using namespace std;

//CLASS DECLARATIONS

/*******************************************************************************************************************/
//material properties
double c0 = 1.0, c1 = 0.0, c2 = 0.0;
float IN = 10000000; 

//METHOD DECLARATIONS
/********************************************************************************************************************/
// The calculation of l, v, h and n.

Point3D negatize(Point3D A){
	Point3D res;
	res.x = (-1.0) * A.x;
	res.y = (-1.0) * A.y;
	res.z = (-1.0) * A.z;
	return res;
}

/**************************************************************************************************************/
 //calculating crossproduct
 Point3D crossproduct(Point3D& p1, Point3D& p2){
	Point3D newP;
    newP.x = (p1.y*p2.z) - (p2.y*p1.z);
    newP.y = (p2.x*p1.z) - (p1.x*p2.z);
    newP.z = (p1.x*p2.y) - (p2.x*p1.y);      
    return newP;
 }
 
float distanceL(Light A, Point3D IP){
	float dist = 0.0;
	float p1 = pow((A.getLx()-IP.x),2);
	float p2 = pow((A.getLy()-IP.y),2);
	float p3 = pow((A.getLz()-IP.z),2);
	dist = sqrt(p1 + p2 + p3);
	return dist;
}

// Bling Phong illumination Model
double attenuation(double r, double c0, double c1, double c2){
    return min(1.0, 1.0/(c0 + c1* r + c2*r*r));
}

ColorRGB rayTracer(Point3D& vp, Point3D& dir, int depth, vector<Sphere>& object, Light& LS){
	
    const Sphere* S = NULL; 
    ColorRGB res;
    Point3D Normal;
    Point3D IP;
    Point3D Normalmin;
    Point3D IPmin;
    
    float tmin = IN;
    float t = IN;

     for(unsigned int i = 0; i< object.size(); i++){
     	if(object[i].Intersection(vp, t, IP, Normal, dir)){
		     if(t < tmin){
				tmin = t;
				S = &object[i];
				Normalmin = Normal;
				IPmin = IP;
			}
		}
	}


    if (!S){
	   	res.setRGBA(0.0, 0.0, 0.0, 1.0);
		return res;
	
}    Normalmin.normalize();
	
	ColorRGB cl;
	ColorRGB cm;
	ColorRGB cr;

	vector<float> colors;
	Point3D lightvec;

	// Bling fong model used inside this rey tracing program
	for(int RGBA = 0 ; RGBA < 4; RGBA++){
		float phongAmbient = LS.ambient[0] * S->matAmbient[0];
		double dist = distanceL(LS, IPmin);
		float att = attenuation(dist, c0, c1, c2);

	    Point3D val_L;
	    val_L = LS.position - IPmin;
	    val_L.normalize();

	    Point3D I2V;
	    I2V = IPmin - vp;
	    lightvec = I2V;
	    I2V.normalize();

	    Point3D val_H;
		val_H = val_L + I2V; 
		val_H.normalize();
			
		float phongSpecular = LS.diffuse[RGBA]*att*(S->matDiffuse[RGBA]*max(Normalmin.dot(val_L),(float)0.0)+S->matSpecular[RGBA]*
				pow(max(val_H.dot(Normalmin),(float) 0),S->SRE));
		float sum = phongAmbient + phongSpecular;

		colors.push_back(sum);
	}

	cl.setRGBA(colors[0], colors[1], colors[2], colors[3]);
	colors.clear();
	// Mirroring/ reflection
	if(S->a_rf > 0 && depth < 2){
		float correction = 1;
		Point3D Rf;
		Rf = dir - Normalmin*2*dir.dot(Normalmin); 
        Rf.normalize();
        Point3D final;
		final = IPmin + Normalmin*correction;
		//https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf

		cm = rayTracer(final, Rf, depth+1, object, LS);
	}
	bool inside = false; 
	if (dir.dot(Normalmin) > 0) inside = true; 
	if(S->b_tr > 0 && depth < 3){		//Refraction 
		float correction = 1e-1;
		float beta, alpha;
		// calculating alpha .. 
		float val0 = 0.0;
		Point3D adj_dir;
		adj_dir = negatize(dir);
		val0 = adj_dir.dot(Normalmin);
		alpha = acos(val0);
	
		float eta = (inside) ? S->n_index : (1.0/ S->n_index); // are we inside or outside the surface? 

		beta = asin(sin(alpha)/eta);

		Point3D val1;
		float inv_n = (1/eta);
		Point3D comp1;
		Point3D comp2;
		comp1 = dir*inv_n;

		float const1 = inv_n*cos(alpha);
		float const2 = cos(beta);
		float valConst = const1-const2;
		comp2 = Normalmin*valConst;
		Point3D refdir;
		refdir = comp1 + comp2; 

		Point3D final;
		final = IPmin - Normalmin*correction;
		cr = rayTracer(final, refdir, depth+1, object, LS);
	}

	float v1 = (1.0 - S->a_rf - S->b_tr);

	return ((cl*v1) + (cm*S->a_rf) + (cr*S->b_tr));
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

	Sphere sphere1(0.8, 0.6, 1.5, 4.5);
	Sphere sphere2(0.8, 0.3, -0.2, 3.5);
	Sphere sphere3(0.9, 0.6, -0.8, 2.0);

	sphere1.a_rf = 0.6;	//mirror
	sphere1.b_tr= 0.0;	//transparent
	sphere1.n_index = 1.0;

	sphere2.a_rf = 0.4;
	sphere2.b_tr= 0.0;
	sphere2.n_index = 5.0;

	sphere3.a_rf = 0.0;
	sphere3.b_tr= 0.2;
	sphere3.n_index = 1.5;

	sphere1.setMatAmbient(1.0,1.0,1.0,1.0);
	sphere1.setMatDiffuse(1.0,1.0,1.0,1.0);
	sphere1.setMatSpecular(0.5,0.5,0.5,1.0);
	sphere1.setSRE(60);

	sphere2.setMatAmbient(0.9,0.9,0.9,1.0);
	sphere2.setMatDiffuse(1.0,0.0,0.0,1.0);
	sphere2.setMatSpecular(0.5,0.5,0.5,1.0);
	sphere2.setSRE(60);

	sphere3.setMatAmbient(0.7,0.7,0.7, 1.0);
	sphere3.setMatDiffuse(0.9,0.0,0.0,1.0);
	sphere3.setMatSpecular(0.5,0.5,0.5,1.0);
	sphere3.setSRE(60);

	// Definations for light sources
	Point3D lightsource1;
	
	lightsource1.setxyz(1.0, -2.0, -1.0);

	//Ambienence
	float amb1[4] = {1.0,1.0,1.0,1};

	//Lights and their properties
	float diff1[4] = {1.0,1.0,1.0,1};
	Light Light0(amb1, diff1, lightsource1);

	vector<Sphere> object;
	//object.push_back(sphere1);
	object.push_back(sphere2);
	object.push_back(sphere3);
	// Implementing the shooting of rays
	for(int x1 = 0; x1 < length; x1++){
		for(int y1 = 0; y1 < length; y1++){
			Point3D dir;
			ColorRGB retColor;
			dir = viewPoint - Pixel_center[x1][y1];
			dir.normalize();
			retColor = rayTracer(viewPoint, dir, 0, object, Light0);
			Pixel_center[x1][y1].setRGBA(retColor.R, retColor.G, retColor.B, retColor.A);
		}
	}

	// Obtaining 3d image by utilizing the ppm program
  	FILE *fp = fopen("sp.ppm", "wb"); // b - binary mode 

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





