
#ifndef IMAGE_H
#define IMAGE_H

#include "window.h"
#include "shader.h"
#include "camera.h"
#include "soil/SOIL.h"
#include <linmath.h>
#include <time.h>

typedef struct {
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	int size;

	int width,height;
	unsigned char* image;
	
	GLuint diffuseMap;
	GLuint specularMap;
	GLuint normalMap;

	float x,y,z;
	float w,h,d;
	float rx,ry,rz;
	float scale;
} Image;

void cgl_InitImage(Image*, const char*, const char*, vec3, vec3);
void cgl_DrawImage(Image*, ShaderProgram*, Camera*);
void cgl_FreeImage(Image*);

#endif
