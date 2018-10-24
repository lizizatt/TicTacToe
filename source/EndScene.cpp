#include "EndScene.h"

EndScene::EndScene(Vector3 position, Vector3 forward, Vector3 scale)
{
	this->position = position;
	this->forward = forward;
	this->scale = scale;
	mvp.Update(position, forward, scale);
}

void EndScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(Vector3::z(), Vector3::zero(), Vector3::one(), ""));
}

void EndScene::TearDownScene()
{
}