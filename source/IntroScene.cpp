#include "IntroScene.h"
#include "main.h"


IntroScene::IntroScene(glm::vec3 position, glm::mat3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	SetUpMVP();
}

void IntroScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, .5, 0), glm::vec3(.6, .6, .6), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, -.2, 0), glm::vec3(.1, .1, .1), position, scale));

	cubes[0]->setFace(Cube::Face::logo);
	cubes[1]->setFace(Cube::Face::startGame);

	cubes[1]->addListener(this);
}

void IntroScene::TearDownScene()
{
}

void IntroScene::OnClick(Cube *c)
{
	if (c == cubes[1].get()) {
		MainRunner::getInstance()->StartGame();
	}
}