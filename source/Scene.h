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
	virtual void TearDownScene() = 0;

	virtual inline void drawScene(Mat16 parentMVP)
	{
		Mat16 targetMVP = mvp * parentMVP;
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i]->draw(targetMVP);
		}
	}

	virtual inline Vector3 Position()
	{
		return position;
	}

	virtual inline Vector3 Forward()
	{
		return forward;
	}

protected:
	vector<shared_ptr<Cube>> cubes;
	Vector3 position;
	Vector3 forward;
	Vector3 scale;

	Mat16 mvp;
};