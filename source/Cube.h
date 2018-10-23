#pragma once

#include <glad/glad.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include "Vector3.h"

using namespace std;

class Cube
{
public:
	Cube();
	Cube(Vector3 pos, Vector3 forward, Vector3 scale, Vector3 baseColor, string textureFileName = "");
	~Cube();

	void draw();

	static void SetUpCube();
	static void TearDownCube();

private:
	Vector3 pos;
	Vector3 forward;
	Vector3 scale;
	Vector3 baseColor;
	string textureFileName;

	GLfloat* mvp;
	
	static GLuint VertexArrayID;
	static GLuint vertexbuffer;
	static GLuint colorbuffer;
};

