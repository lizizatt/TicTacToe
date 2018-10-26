#include "IntroScene.h"


IntroScene::IntroScene(glm::vec3 position, glm::mat3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	SetUpMVP();
}

void IntroScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, .5, 0), glm::mat3(1.0f), glm::vec3(.6, .6, .6), "test.png"));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, -.2, 0), glm::mat3(1.0f), glm::vec3(.1, .1, .1), "TTTMainMenu.png"));
}

void IntroScene::TearDownScene()
{
}