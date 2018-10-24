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

	virtual inline void drawScene(glm::mat4 &parentMVP)
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

	virtual inline glm::vec3 Forward()
	{
		return forward;
	}

	inline void SetUpMVP()
	{
		mvp = glm::mat4(1.0f);
		glm::translate(mvp, position);
		//todo rotate
		glm::scale(mvp, scale);
	}

protected:
	vector<shared_ptr<Cube>> cubes;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 scale;

	glm::mat4 mvp;
};