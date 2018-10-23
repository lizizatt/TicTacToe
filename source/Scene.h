#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include "Vector3.h"
#include "Cube.h"
#include <vector>

using namespace std;

class Scene
{
public:
	virtual void InitializeScene() = 0;
	virtual void TearDownScene() {}

	virtual inline void drawScene()
	{
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i]->draw();
		}
	}

	virtual inline Vector3 Position()
	{
		return pos;
	}

	virtual inline Vector3 Forward()
	{
		return forward;
	}

protected:
	vector<shared_ptr<Cube>> cubes;
	Vector3 pos;
	Vector3 forward;
};