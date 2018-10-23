#include "IntroScene.h"

void IntroScene::InitializeScene()
{
	cubes.push_back(std::make_shared<Cube>(Vector3::zero(), Vector3::z(), Vector3::one(), Vector3::one(), ""));
}