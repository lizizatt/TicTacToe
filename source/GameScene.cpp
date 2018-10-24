#include "GameScene.h"

GameScene::GameScene(glm::vec3 position, glm::vec3 forward, glm::vec3 scale)
{
	this->position = position;
	this->forward = forward;
	this->scale = scale;
	SetUpMVP();
}

void GameScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>());
}

void GameScene::TearDownScene()
{
}