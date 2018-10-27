#include "GameScene.h"

GameScene::GameScene(glm::vec3 position, glm::mat3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	SetUpMVP();
}

void GameScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(glm::vec3(-1, -1, 0), glm::vec3(.1, .1, .1)));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, -1, 0), glm::vec3(.1, .1, .1)));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(1, -1, 0), glm::vec3(.1, .1, .1)));

	cubes.push_back(std::make_shared<Cube>(glm::vec3(-1, 0, 0), glm::vec3(.1, .1, .1)));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1)));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(1, 0, 0), glm::vec3(.1, .1, .1)));

	cubes.push_back(std::make_shared<Cube>(glm::vec3(-1, 1, 0), glm::vec3(.1, .1, .1)));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, 1, 0), glm::vec3(.1, .1, .1)));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(1, 1, 0), glm::vec3(.1, .1, .1)));

	for (int i = 0; i < cubes.size(); i++) {
		cubes[i]->setFace(Cube::Face::logo);
	}
}

void GameScene::TearDownScene()
{
}