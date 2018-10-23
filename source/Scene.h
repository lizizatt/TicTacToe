#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include "Vector3.h"

using namespace std;

class Scene
{
public:
	virtual void drawScene() = 0;
	virtual void setUpScene() = 0;
	virtual void tearDownScene() = 0;
};