#include "EndScene.h"

EndScene::EndScene(glm::vec3 position, glm::mat3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	SetUpMVP();
}

void EndScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(glm::vec3(-1, 0, 0), glm::vec3(.1, .1, .1), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1), position, scale));

	cubes[0]->setFace(Cube::Face::logo);
	cubes[1]->setFace(Cube::Face::startGame);
}

void EndScene::TearDownScene()
{
}