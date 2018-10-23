#include "main.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

MainRunner* MainRunner::instance;

MainRunner::MainRunner()
{
	if (instance != nullptr) {
		cerr << "More than one instance of MainRunner! \n";
	}
	instance = this;

	//initialize one of each scene
	scenes.push_back(make_shared<IntroScene>());
	scenes.push_back(make_shared<GameScene>());
	scenes.push_back(make_shared<EndScene>());
}

MainRunner::~MainRunner()
{
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
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
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
	}
}

void MainRunner::DrawScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->drawScene();
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
	cameraPos = scene->Position() - Vector3(0, 0, 1);
	cameraForward = scene->Position() - cameraPos;
}

void MainRunner::UpdateCamera()
{
	//todo
	//Vector3 right = Vector3::y().Cross(cameraForward).Normalize();
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
	glfwSetErrorCallback(errorCallback);

	GLFWwindow* window = initialize();
	if (!window) {
		return 0;
	}

	MainRunner mainRunner;

	// Set the clear color to a nice green
	glClearColor(0.15f, 0.6f, 0.4f, 1.0f);

	mainRunner.SetUpShaders();

	mainRunner.SetUpScenes();

	//set up various arrays used to draw our only primitive, a textured cube
	Cube::SetUpCube();

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

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
