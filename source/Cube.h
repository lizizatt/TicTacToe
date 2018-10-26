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
	Cube();
	Cube(Cube &c);
	Cube(glm::vec3 pos, glm::mat3 rotation, glm::vec3 scale, string textureFileName = "");
	~Cube();

	void draw(glm::mat4 mvp);
	void setup();

	static void SetUpCube();
	static void TearDownCube();

private:
	glm::vec3 pos;
	glm::mat3 rotation;
	glm::vec3 scale;
	string textureFileName;

	glm::mat4 mvp;
	GLuint textureID;
	unsigned int texWidth;
	unsigned int texHeight;
	int texNum;
	std::vector<unsigned char> texBuffer;
	
	static unordered_map<string, GLuint> textures;
	static unordered_map<string, int> textureNums;
	static GLuint VertexArrayID;
	static GLuint vertexbuffer;
	static GLuint uvbuffer;
	static GLuint texSampler;
	static int texNumCounter;
	static GLuint layerLocation;

	bool once = false;
};

