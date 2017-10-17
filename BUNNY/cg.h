#include <iostream>
#include <vector>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec2.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <GL/glew.h> 


#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>


bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices){

    printf("Loading OBJ file %s...\n", path);
    
    std::vector<unsigned int> vertexIndices;
    std::vector<glm::vec3> temp_vertices;
    
    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }
    
    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        if (strcmp(lineHeader, "v") == 0 ){

            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3]/*,uvIndex[3], normalIndex[3]*/;
            int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
            if (matches != 3){
                printf("File can't be read by our simple parser 😞 Try exporting with other options\n");
                fclose(file);
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
        }
        else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
        
    }
    
    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        
        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        
        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[vertexIndex-1];
 
        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        
    }
    fclose(file);
    return true;
}

































