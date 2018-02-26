#ifndef MESH_H
#define MESH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

using namespace glm;
using namespace std;

struct Vertex {
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures){
       this->vertices = vertices;
       this->indices = indices;
       this->textures = textures;
       setupMesh();
   }

   void Draw(Shader shader) {
       unsigned int diffuseNr = 1;
       unsigned int specularNr = 1;
       for(unsigned int i = 0; i < textures.size(); i++) {
           glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
           // retrieve texture number (the N in diffuse_textureN)
           string number;
           string name = textures[i].type;
           if(name == "texture_diffuse")
               number = std::to_string(diffuseNr++);
           else if(name == "texture_specular")
               number = std::to_string(specularNr++);

           shader.setFloat(("material." + name + number).c_str(), i);
           glBindTexture(GL_TEXTURE_2D, textures[i].id);
       }
       glActiveTexture(GL_TEXTURE0);

       // draw mesh
       glBindVertexArray(VAO);
       glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
       glBindVertexArray(0);
   }


private:
    //vertex & element buffer objects
    unsigned int VBO, EBO;
    void setupMesh(){
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        // offsetof macro returns the byte offset of that variable from the start of the struct
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        //WTF ARE THESE TANGENTZ?
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);
    }
};
#endif
