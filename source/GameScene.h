#pragma once

#include "Scene.h"

using namespace std;

class GameScene : public Scene, public Cube::Listener
{
public:
	GameScene(glm::vec3 position, glm::mat3 rotation, glm::vec3 scale);
	void InitializeScene() override;
	void TearDownScene() override;
	void OnClick(Cube *c) override;
	void RenderBoard(string boardString);
};

