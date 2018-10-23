#pragma once

#include <glad/glad.h>
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

	void setup();
	void draw();
	void teardown();

private:
	Vector3 pos;
	Vector3 forward;
	Vector3 scale;
	Vector3 baseColor;
	string textureFileName;
};

