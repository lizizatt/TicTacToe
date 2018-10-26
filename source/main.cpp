#include "main.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <time.h>

using namespace std;

MainRunner* MainRunner::instance;

MainRunner::MainRunner()
{
	if (instance != nullptr) {
		cerr << "More than one instance of MainRunner! \n";
	}
	instance = this;

	//initialize one of each scene
	scenes.push_back(new IntroScene(glm::vec3(0, 10, 0), glm::mat3(1.0f), glm::vec3(1, 1, 1)));
	scenes.push_back(new GameScene(glm::vec3(0, 0, 0), glm::mat3(1.0f), glm::vec3(1, 1, 1)));
	scenes.push_back(new EndScene(glm::vec3(0, -10, 0), glm::mat3(1.0f), glm::vec3(1, 1, 1)));
}

MainRunner::~MainRunner()
{
	for (int i = 0; i < scenes.size(); i++) {
		delete scenes[i];
	}
	scenes.clear();
}

void MainRunner::SetUpShaders()
{
	string path = ExePath();

	//load from files
	ifstream tVert(path + "\\vertex.vert");
	stringstream bufferVert;
	bufferVert << tVert.rdbuf();
	string vertStr = bufferVert.str();
	const char* vertex_shader_text = vertStr.c_str();

	ifstream tFrag(path + "\\fragment.frag");
	stringstream bufferFrag;
	bufferFrag << tFrag.rdbuf();
	string fragStr = bufferFrag.str();
	const char* fragment_shader_text = fragStr.c_str();

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertex_shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	//fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);
	cout << "Compiled fragment shader with error code:" << glGetError() << "\n";

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragment_shader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	//program
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	cout << "Created glProgram with error code:" << glGetError() << "\n";

	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glUseProgram(program);

	mvp_location = glGetUniformLocation(program, "MVP");
	cout << "Got MVP location with error code:" << glGetError() << "\n";
}

void MainRunner::SetUpScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->InitializeScene();
		scenes[i]->LoadCubeTextures();
	}
	FocusOnScene(scenes[0]);
}

void MainRunner::DrawScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->drawScene(cameraMVP);
	}
}

void MainRunner::TearDownScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->TearDownScene();
	}
}

void MainRunner::FocusOnScene(Scene *scene)
{
	//todo move camera over to new scene w/ a smooth glide
	cameraPos = scene->Position() - glm::vec3(0,0,5);
	cameraForward = glm::vec3(0, 0, 1);
}

void MainRunner::UpdateCamera()
{
	cameraP = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	cameraMVP = cameraP * glm::lookAt(cameraPos, cameraPos + cameraForward, glm::vec3(0, 1, 0));
}

bool MainRunner::RunTests()
{
	return true;
}

string MainRunner::ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

namespace {
   void errorCallback(int error, const char* description) {
      fprintf(stderr, "GLFW error %d: %s\n", error, description);
   }

   GLFWwindow* initialize() {
      int glfwInitRes = glfwInit();
      if (!glfwInitRes) {
         fprintf(stderr, "Unable to initialize GLFW\n");
         return nullptr;
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
      if (!window) {
         fprintf(stderr, "Unable to create GLFW window\n");
         glfwTerminate();
         return nullptr;
      }

      glfwMakeContextCurrent(window);

      int gladInitRes = gladLoadGL();
      if (!gladInitRes) {
         fprintf(stderr, "Unable to initialize glad\n");
         glfwDestroyWindow(window);
         glfwTerminate();
         return nullptr;
      }

      return window;
   }
}


int main(int argc, char* argv[]) {


	MainRunner mainRunner;

	if (mainRunner.RUN_TESTS && !mainRunner.RunTests()) {
		return -1;
	}

	glfwSetErrorCallback(errorCallback);

	GLFWwindow* window = initialize();
	if (!window) {
		return 0;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mainRunner.SetUpShaders();

	//set up various arrays used to draw our only primitive, a textured cube
	Cube::SetUpCube();

	mainRunner.SetUpScenes();

	time_t lastChangeScene;
	time(&lastChangeScene);
	int curScene = 0;

	while (!glfwWindowShouldClose(window)) {

		time_t frameStart;
		time(&frameStart);

		if (frameStart - lastChangeScene > 3) {
			curScene = (curScene + 1) % mainRunner.getNumScenes();
			mainRunner.FocusOnScene(mainRunner.getScene(curScene));
			cout << "Swapping scenes to " << curScene << "...\n";
			lastChangeScene = frameStart;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mainRunner.UpdateCamera();
		mainRunner.DrawScenes();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//tear down cube arrays
	Cube::TearDownCube();
   
	//tear down scenes
	mainRunner.TearDownScenes();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
