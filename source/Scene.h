#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include "Cube.h"
#include <vector>

using namespace std;

class Scene
{
public:
	virtual void InitializeScene() = 0;
	virtual void TearDownScene() = 0;

	virtual inline void drawScene(glm::mat4 parentMVP)
	{
		glm::mat4 targetMVP = parentMVP * mvp;
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i]->draw(targetMVP);
		}
	}

	virtual inline glm::vec3 Position()
	{
		return position;
	}

	virtual inline glm::mat3 Rotation()
	{
		return rotation;
	}

	inline void SetUpMVP()
	{
		mvp = glm::mat4(1.0f);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mvp[i][j] = rotation[i][j];
			}
		}
		mvp = glm::translate(mvp, position);
		mvp = glm::scale(mvp, scale);
	}

protected:
	vector<shared_ptr<Cube>> cubes;
	glm::vec3 position;
	glm::mat3 rotation;
	glm::vec3 scale;

	glm::mat4 mvp;
};