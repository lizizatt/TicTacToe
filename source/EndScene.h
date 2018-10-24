#pragma once

#include "Scene.h"

using namespace std;

class EndScene : public Scene
{
public:
	EndScene(glm::vec3 position, glm::mat3 rotation, glm::vec3 scale);
	void InitializeScene() override;
	void TearDownScene() override;
};

