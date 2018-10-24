#include "IntroScene.h"


IntroScene::IntroScene(glm::vec3 position, glm::vec3 forward, glm::vec3 scale)
{
	this->position = position;
	this->forward = forward;
	this->scale = scale;
	SetUpMVP();
}

void IntroScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>());
}

void IntroScene::TearDownScene()
{
}