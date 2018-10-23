#include "main.h"


MainRunner::MainRunner()
{
	//initialize one of each scene
	scenes.push_back(make_shared<IntroScene>());
	scenes.push_back(make_shared<GameScene>());
	scenes.push_back(make_shared<EndScene>());
}

MainRunner::~MainRunner()
{
}

void MainRunner::SetUpScenes()
{
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i]->setUpScene();
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
		scenes[i]->tearDownScene();
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
	Vector3 right = Vector3::y().Cross(cameraForward).Normalize();
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

   mainRunner.SetUpScenes();

   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);

	  mainRunner.UpdateCamera();
	  mainRunner.DrawScenes();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }
   
   mainRunner.TearDownScenes();

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}
