#pragma once

#include "Scene.h"

using namespace std;

class GameScene : public Scene
{
public:
	GameScene(glm::vec3 position, glm::vec3 forward, glm::vec3 scale);
	void InitializeScene() override;
	void TearDownScene() override;
};

