#include <iostream>
#include <Windows.h>

#pragma comment(lib, "fmod_vc.lib")

#include "Application.h"
#include "Shader.h"

#include "Window.h"
#include "Event.h"

#include "Object.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture.h"
#include "Image.h"

#include "opengl.h"

#include "Sound.h"

void detectCloseWindow(dn::Window * win, const int & key);

void windowAtFileDropped(dn::Window * win, const std::vector<std::string> & files);

std::map<int, dn::Sound *> soundsMapped;

dn::Object * obj0 = new dn::Object();
dn::Object * obj1 = new dn::Object();

dn::Object * camera = new dn::Object();

dn::Shader * defaultShader = new dn::Shader(dn::ReadFile("shader/vertex.shdr"), dn::ReadFile("shader/fragment.shdr"));

float speedCameraMovement = 0.01f;
float speedCameraRotation = 0.01f;
float xs = 1;

std::ostream &operator<<(std::ostream & stream, const glm::vec3 & a)
{
	return (stream << "(" << a.x << ", " << a.y << ", " << a.z << ")");
}

void MoveCameraUpdate(dn::Window * p_win);
void PlayDrum(dn::Window * p_win, const int & p_key);

void AddSoundMap(const int & p_key, const std::string & p_path);

double lMouseX = 0;
double lMouseY = 0;

int main()
{
	/*AddSoundMap(GLFW_KEY_A, "Piano/EPIANO2/Ep2 E2.wav");
	AddSoundMap(GLFW_KEY_Z, "Piano/EPIANO2/Ep2 E3.wav");
	AddSoundMap(GLFW_KEY_E, "Piano/EPIANO2/Ep2 E4.wav");
	AddSoundMap(GLFW_KEY_R, "Piano/APiano01/AI-APiano01 04(R).wav");
	AddSoundMap(GLFW_KEY_T, "Piano/APiano01/AI-APiano01 05(R).wav");
	AddSoundMap(GLFW_KEY_Y, "Piano/APiano01/AI-APiano01 06(R).wav");
	AddSoundMap(GLFW_KEY_U, "Piano/APiano01/AI-APiano01 07(R).wav");
	AddSoundMap(GLFW_KEY_I, "Piano/APiano01/AI-APiano01 08(R).wav");
	AddSoundMap(GLFW_KEY_O, "Piano/APiano01/AI-APiano01 09(R).wav");
	AddSoundMap(GLFW_KEY_P, "Piano/APiano01/AI-APiano01 10(R).wav");
	AddSoundMap(GLFW_KEY_Q, "Piano/APiano01/AI-APiano01 11(R).wav");
	AddSoundMap(GLFW_KEY_S, "Piano/APiano01/AI-APiano01 12(R).wav");
	AddSoundMap(GLFW_KEY_D, "Piano/APiano01/AI-APiano01 13(R).wav");
	AddSoundMap(GLFW_KEY_F, "Samples/Taiko Drum 5-2.wav");
	AddSoundMap(GLFW_KEY_G, "Samples/Taiko Drum 5-3.wav");
	AddSoundMap(GLFW_KEY_H, "Samples/Taiko Drum 6-0.wav");
	AddSoundMap(GLFW_KEY_J, "Samples/Taiko Drum 6-1.wav");
	AddSoundMap(GLFW_KEY_K, "Samples/Taiko Drum 6-2.wav");
	AddSoundMap(GLFW_KEY_L, "Samples/Taiko Drum 6-3.wav");
	AddSoundMap(GLFW_KEY_M, "Samples/Taiko Drum 6-4.wav");
	AddSoundMap(GLFW_KEY_W, "Samples/Taiko Drum Hit 1-15.wav");
	AddSoundMap(GLFW_KEY_X, "Samples/Taiko Drum Hit 1-16.wav");
	AddSoundMap(GLFW_KEY_C, "Samples/Taiko Drum Hit 1-17.wav");
	AddSoundMap(GLFW_KEY_V, "Samples/Taiko Drum Hit 1-18.wav");
	AddSoundMap(GLFW_KEY_B, "Samples/Taiko Drum Hit 1-19.wav");
	AddSoundMap(GLFW_KEY_N, "Samples/Taiko Drum Hit 1-23.wav");
	AddSoundMap(GLFW_KEY_SPACE, "Samples/Taiko Drum Hit 1-25.wav");
	AddSoundMap(GLFW_KEY_LEFT_ALT, "Samples/Taiko Drum Hit 1-27.wav");
	AddSoundMap(GLFW_KEY_RIGHT_ALT, "Samples/Taiko Drum Hit 1-28.wav");*/
	dn::Window * mainWindow = new dn::Window("Main", 800, 400);

	unsigned char blank_pxls[] = {
		255, 255, 255, 255,			255, 0, 0, 255,			0, 255, 0, 255,			0, 0, 255, 255,
		255, 0, 0, 255,				0, 255, 0, 255,			0, 0, 255, 255,			255, 255, 255, 255,
		0, 255, 0, 255,				0, 0, 255, 255,			255, 255, 255, 255,		255, 0, 0, 255,
		0, 0, 255, 255,				255, 255, 255, 255,		255, 0, 0, 255,			0, 255, 0, 255
	};
	unsigned char white[] = {
		255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255
	};
	dn::Image * blank_img = new dn::Image(white, 2, 2);

	obj0->AddComponent<dn::Transform>();
	obj0->AddComponent<dn::MeshRenderer>(new dn::MeshRenderer(dn::Shape::cubeForm, defaultShader, GL_TRIANGLES));
	obj0->GetComponent<dn::MeshRenderer>()->material()->color() = glm::vec4(1, 1, 1, 1);
	obj0->GetComponent<dn::MeshRenderer>()->material()->SetTexture(new dn::Texture(blank_img));

	obj1->AddComponent<dn::Transform>()->position().z = 2;
	obj1->AddComponent<dn::MeshRenderer>(new dn::MeshRenderer(dn::Shape::quad, defaultShader, GL_TRIANGLE_STRIP))->material()->SetTexture(new dn::Texture(blank_img));
	obj1->GetComponent<dn::MeshRenderer>()->material()->color() = glm::vec4(1, 1, 1, 0.2f);
	obj1->GetComponent<dn::MeshRenderer>()->SetActive(true);

	camera->AddComponent<dn::Camera>()->SetAspectRatio((float)(mainWindow->width()) / (float)(mainWindow->height()));
	camera->AddComponent<dn::Transform>()->position().z = 1;

	mainWindow->StartEvent.AddListener([](dn::Window * win) {
		camera->Start();
		obj0->Start();
		obj1->Start();
		win->SetCursorPos(0, 0, true);
	});
	mainWindow->UpdateEvent.AddListener(MoveCameraUpdate);
	mainWindow->UpdateEvent.AddListener([](dn::Window * win) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		lMouseX -= win->GetMouseX();
		lMouseY -= win->GetMouseY();

		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().x -= lMouseY;
		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().y += lMouseX;

		//camera->Update();

		obj0->Update();
		obj1->Update();

		lMouseX = win->GetMouseX();
		lMouseY = win->GetMouseY();
	});
	mainWindow->SizeChangeEvent.AddListener([](dn::Window * win, const int & w, const int & h) {
		glViewport(0, 0, w, h);
		camera->GetComponent<dn::Camera>()->SetAspectRatio((float)w / (float)h);
	});
	mainWindow->KeyPressEvent.AddListener(detectCloseWindow);
	mainWindow->MouseEnterEvent.AddListener([](dn::Window * win, const bool & enter) {
		if (enter)
			lMouseX = lMouseY = 0;
	});

	dn::Application::Run();

	return 0;
}

void PlayDrum(dn::Window * p_win, const int & p_key)
{
	if (soundsMapped.count(p_key))
		soundsMapped.at(p_key)->Play();
}

void AddSoundMap(const int & p_key, const std::string & p_path)
{
	if (soundsMapped.count(p_key))
		return;
	dn::Sound * s = new dn::Sound(p_path);
	if (!s->IsValid())
		return;
	soundsMapped.insert(std::make_pair(p_key, s));

}

void MoveCameraUpdate(dn::Window * win)
{
	if (win->GetKey(GLFW_KEY_W))
		camera->GetComponent<dn::Transform>()->position() += camera->GetComponent<dn::Transform>()->forward() * speedCameraMovement;
	if (win->GetKey(GLFW_KEY_S))
		camera->GetComponent<dn::Transform>()->position() += -camera->GetComponent<dn::Transform>()->forward() * speedCameraMovement;
	if (win->GetKey(GLFW_KEY_A))
		camera->GetComponent<dn::Transform>()->position() += -camera->GetComponent<dn::Transform>()->right() * speedCameraMovement;
	if (win->GetKey(GLFW_KEY_D))
		camera->GetComponent<dn::Transform>()->position() += camera->GetComponent<dn::Transform>()->right() * speedCameraMovement;
	if (win->GetKey(GLFW_KEY_LEFT_CONTROL))
		camera->GetComponent<dn::Transform>()->position() += -camera->GetComponent<dn::Transform>()->up() * speedCameraMovement;
	if (win->GetKey(GLFW_KEY_SPACE))
		camera->GetComponent<dn::Transform>()->position() += camera->GetComponent<dn::Transform>()->up() * speedCameraMovement;

	if (win->GetKey(GLFW_KEY_UP))
		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().x += speedCameraRotation;
	if (win->GetKey(GLFW_KEY_DOWN))
		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().x -= speedCameraRotation;
	if (win->GetKey(GLFW_KEY_LEFT))
		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().y += speedCameraRotation;
	if (win->GetKey(GLFW_KEY_RIGHT))
		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().y -= speedCameraRotation;
	if (win->GetKey(GLFW_KEY_O))
		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().z += speedCameraRotation;
	if (win->GetKey(GLFW_KEY_P))
		camera->GetComponent<dn::Transform>()->rotation().eulerAngles().z -= speedCameraRotation;
}

void detectCloseWindow(dn::Window * win, const int & button)
{
	if (button == GLFW_KEY_ESCAPE)
		win->Close();
}

void windowAtFileDropped(dn::Window * win, const std::vector<std::string> & files)
{
	std::cout << "Dropped file(s) :" << std::endl;
	for (size_t i = 0; i < files.size(); ++i)
		std::cout << "\t" << files[i] << std::endl;
}

/*void windowKeyPressLiveWriting(dn::Window * win, const int & key)
{
	if (key == GLFW_KEY_ESCAPE && !controlMode)
	{
		controlMode = true;
		std::cout << "\b@";
	}
	else if (key == GLFW_KEY_A && controlMode)
		win->Close();
	else if (key == GLFW_KEY_S && controlMode)
		dn::Application::ExitSuccess();
	else if (key == GLFW_KEY_I && controlMode)
	{
		controlMode = false;
		lockNextChar = true;
		std::cout << "\b|";
	}
	else if (!controlMode)
	{
		if (key == GLFW_KEY_BACKSPACE)
			std::cout << "\b \b\b|";
		else if (key == GLFW_KEY_ENTER)
			std::cout << "\b \n|";
		else if (key == GLFW_KEY_TAB)
			std::cout << "\b\t|";
	}
};

void windowCharPressLiveWriting(dn::Window * win, const unsigned int & chr)
{
	if (!controlMode && !lockNextChar)
		std::cout << '\b' << (char)(chr) << '|';
	lockNextChar = false;
};*/
