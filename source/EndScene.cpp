#include "EndScene.h"

EndScene::EndScene(glm::vec3 position, glm::vec3 forward, glm::vec3 scale)
{
	this->position = position;
	this->forward = forward;
	this->scale = scale;
	SetUpMVP();
}

void EndScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>());
}

void EndScene::TearDownScene()
{
}