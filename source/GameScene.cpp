#include "GameScene.h"
#include "main.h"

GameScene::GameScene(glm::vec3 position, glm::mat3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	SetUpMVP();
}

void GameScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(glm::vec3(-1, -1, 0), glm::vec3(.1, .1, .1), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, -1, 0), glm::vec3(.1, .1, .1), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(1, -1, 0), glm::vec3(.1, .1, .1), position, scale));

	cubes.push_back(std::make_shared<Cube>(glm::vec3(-1, 0, 0), glm::vec3(.1, .1, .1), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(1, 0, 0), glm::vec3(.1, .1, .1), position, scale));

	cubes.push_back(std::make_shared<Cube>(glm::vec3(-1, 1, 0), glm::vec3(.1, .1, .1), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(0, 1, 0), glm::vec3(.1, .1, .1), position, scale));
	cubes.push_back(std::make_shared<Cube>(glm::vec3(1, 1, 0), glm::vec3(.1, .1, .1), position, scale));

	for (int i = 0; i < cubes.size(); i++) {
		cubes[i]->setFace(Cube::Face::logo);
		cubes[i]->addListener(this);
	}
}

void GameScene::TearDownScene()
{
}

void GameScene::OnClick(Cube *c)
{
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i].get() == c) {
			MainRunner::getInstance()->PlacePiece(i);
			break;
		}
	}
}

void GameScene::RenderBoard(string board)
{
	for (int i = 0; i < 9; i++) {
		if (board[i] == 'X') {
			cubes[i]->setFace(Cube::Face::X);
			continue;
		}
		if (board[i] == 'O') {
			cubes[i]->setFace(Cube::Face::O);
			continue;
		}
		cubes[i]->setFace(Cube::Face::logo);
	}
}