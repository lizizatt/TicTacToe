#include "GameScene.h"

GameScene::GameScene(Vector3 position, Vector3 forward, Vector3 scale)
{
	this->position = position;
	this->forward = forward;
	this->scale = scale;
	mvp.Update(position, forward, scale);
}

void GameScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(Vector3::zero(), Vector3::z(), Vector3::one(), ""));
}

void GameScene::TearDownScene()
{
}