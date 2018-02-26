> Learning OpenGL on Linux

    g++ XXXXX.cpp glad.c -lglfw -lGL -lX11 -lpthread -ldl -lXrandr -lXi -Iinclude -o main -Wall

https://learnopengl.com/Introduction

### Dependencies (ubuntu 17.10)

    libglfw3-dev libassimp-dev


#### Model loading notes

    g++ model-loading.cpp glad.c -lglfw -lGL -lX11 -lpthread -ldl -lXrandr -lXi -lassimp -Iinclude -o main -Wall -g

In blender
* Include Normals: makes sure the normal vectors are included within the wavefront file (used for lighting).
* Include UVs: makes sure the texture coordinates are included if any (UV = texture coordinate).
* Write Materials: also exports a .mtl file that contains all the textures used and/or colors of the model.
* Triangulate Faces: this option makes sure that all shapes are first transformed to triangles before exporting. This is important, because Blender by default uses quads as their primitive shapes and OpenGL prefers triangles as its input. By enabling this option, Blender automatically transforms all their shapes to triangles first so you can directly draw the model (then you don't have to take this into account when importing your model).

![I know OpenGL](https://i.imgur.com/Zf1O1RM.jpg)
