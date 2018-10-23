#include "IntroScene.h"


IntroScene::IntroScene(Vector3 position, Vector3 forward, Vector3 scale)
{
	mvp = Mat16(position, forward, scale);
}

void IntroScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(Vector3::z(), Vector3::zero(), Vector3::one(), ""));
}

void IntroScene::TearDownScene()
{
}