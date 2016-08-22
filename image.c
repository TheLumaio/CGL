
#include "image.h"

void cgl_InitImage(Image* image, const char* path, float x, float y, float z)
{
	GLfloat vertices[] = {
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	float texcoords[] = {
		0.0, 0.0,
		1.0, 0.0,
		0.5, 1.0
	};
	
	image->x = x;
	image->y = y;
	image->z = z;
	
	image->rx = 0;
	image->ry = 0;
	image->rz = 0;
	image->scale = (float)rand() / (float)RAND_MAX;

	glGenVertexArrays(1, &image->VAO);
	glGenBuffers(1, &image->VBO);

	glBindVertexArray(image->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, image->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	// load image
	glGenTextures(1, &image->texture);
	glBindTexture(GL_TEXTURE_2D, image->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image->image = SOIL_load_image("data/container.jpg", &image->width, &image->height, 0, SOIL_LOAD_RGB);
	if (image->image) {
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image->image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void cgl_DrawImage(Image* image, ShaderProgram* prog, Camera* cam)
{

	cgl_UseProgram(prog);

	mat4x4 model;
	mat4x4_identity(model);
	mat4x4_translate(model, image->x, image->y, image->z);
	mat4x4_rotate(model, model, 1.0, 0.0, 0.0, -image->rx * (M_PI/ 180.0 ));
	mat4x4_rotate(model, model, 0.0, 1.0, 0.0, -image->ry * (M_PI/ 180.0 ));
	mat4x4_rotate(model, model, 0.0, 0.0, 1.0, -image->rz * (M_PI/ 180.0 ));
	mat4x4 view;
	mat4x4_identity(view);
	vec3 front;
	vec3_add(front, cam->pos, cam->front);
	mat4x4_look_at(view, cam->pos, front, cam->up);
	mat4x4 projection;
	mat4x4_identity(projection);
	mat4x4_perspective(projection, 45.0, cam->aspect, 0.01, 100.0);

	GLint modelLoc = glGetUniformLocation(prog->program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (*model));
	GLint viewLoc = glGetUniformLocation(prog->program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (*view));
	GLint projLoc = glGetUniformLocation(prog->program, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, (*projection));

	glBindVertexArray(image->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, image->VBO);
	glBindTexture(GL_TEXTURE_2D, image->texture);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

}
