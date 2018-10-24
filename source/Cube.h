#pragma once

#include <glad/glad.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace std;

class Cube
{
public:
	Cube();
	Cube(Cube &c);
	Cube(glm::vec3 pos, glm::mat3 rotation, glm::vec3 scale, string textureFileName = "");
	~Cube();

	void draw(glm::mat4 mvp);

	static void SetUpCube();
	static void TearDownCube();

private:
	glm::vec3 pos;
	glm::mat3 rotation;
	glm::vec3 scale;
	string textureFileName;

	glm::mat4 mvp;
	
	static GLuint VertexArrayID;
	static GLuint vertexbuffer;
	static GLuint colorbuffer;

	bool once = false;
};

