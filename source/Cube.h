#pragma once

#include <glad/glad.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>

using namespace std;

class Cube
{
public:
	enum Face
	{
		logo,
		startGame,
		X,
		lose,
		win,
		O
	};

public:
	Cube();
	Cube(Cube &c);
	Cube(glm::vec3 pos, glm::vec3 scale);
	~Cube();

	void draw(glm::mat4 mvp);
	void setup();

	static void SetUpCube();
	static void TearDownCube();

	Face getFace() { return face; }
	void setFace(Face face);

private:
	glm::vec3 pos;
	glm::vec3 scale;

	Face face;

	glm::mat4 mvp;
	
	static string textureFileName;
	static unsigned int texWidth;
	static unsigned int texHeight;
	static std::vector<unsigned char> texBuffer;
	static GLuint textureID;
	static GLuint VertexArrayID;
	static GLuint vertexbuffer;
	static GLuint uvbuffer;
	static GLuint texSampler;

	bool once = false;
};

