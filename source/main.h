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
};

int main(int argc, char* argv[]);
