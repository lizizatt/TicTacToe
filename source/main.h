#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "IntroScene.h"
#include "GameScene.h"
#include "EndScene.h"

class MainRunner
{
public:
	MainRunner();
	~MainRunner();

	void SetUpScenes();
	void DrawScenes();
	void TearDownScenes();
	void UpdateCamera();

	void FocusOnScene(Scene* scene);
private:
	vector<shared_ptr<Scene>> scenes;
	Vector3 cameraPos;
	Vector3 cameraForward;
};

int main(int argc, char* argv[]);
