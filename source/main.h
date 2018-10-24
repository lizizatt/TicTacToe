
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "IntroScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class MainRunner
{
public:
	const bool RUN_TESTS = true;

public:
	static inline MainRunner* getInstance()
	{
		return instance;
	}

public:
	inline Scene* getScene(int i) {
		return scenes[i];
	}

	inline int getNumScenes() {
		return scenes.size();
	}
	inline int getMVPLocation() { return mvp_location; }
	inline glm::mat4 getPMatrix() { return cameraP; }

public:
	MainRunner();
	~MainRunner();

	void SetUpShaders();
	void SetUpScenes();
	void DrawScenes();
	void TearDownScenes();
	void UpdateCamera();
	bool RunTests();

	void FocusOnScene(Scene* scene);

private:
	vector<Scene*> scenes;
	glm::vec3 cameraPos;
	glm::vec3 cameraForward;
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

private:
	string ExePath();
	static MainRunner* instance;
	glm::mat4 cameraP;
	glm::mat4 cameraMVP;
};

int main(int argc, char* argv[]);
