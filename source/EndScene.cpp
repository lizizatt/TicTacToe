#include "EndScene.h"

EndScene::EndScene(Vector3 position, Vector3 forward, Vector3 scale)
{
	this->position = position;
	this->forward = forward;
	this->scale = scale;
	mvp = Mat16(position, forward, scale);
}

void EndScene::InitializeScene()
{
}

void EndScene::TearDownScene()
{
}