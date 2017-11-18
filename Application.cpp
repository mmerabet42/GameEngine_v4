#include "Application.h"

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Sound.h"

void dn::Application::WindowStart(dn::Window * p_window)
{
	if (p_window)
	{
		p_window->Start();
		if (p_window->IsOpen() && p_window->_atStartCallback)
			p_window->_atStartCallback(p_window);
		if (p_window->IsOpen())
			p_window->StartEvent.Trigger(p_window);
	}
}

void dn::Application::WindowUpdate(dn::Window * p_window)
{
	if (p_window)
	{
		p_window->Update();
		if (p_window->IsOpen() && p_window->_atUpdateCallback)
			p_window->_atUpdateCallback(p_window);
		if (p_window->IsOpen())
			p_window->UpdateEvent.Trigger(p_window);
	}
}

void dn::Application::WindowSizeCallback(GLFWwindow * p_window, int p_width, int p_height)
{
	dn::Window * win = dn::Application::_windows.at(p_window);
	if (win)
	{
		if (win->IsOpen())
		{
			win->SetSize(p_width, p_height);
			win->OnSizeChange(p_width, p_height);
		}
		if (win->IsOpen() && win->_atSizeChangeCallback)
			win->_atSizeChangeCallback(win, p_width, p_height);
		if (win->IsOpen())
			win->SizeChangeEvent.Trigger(win, p_width, p_height);
	}
}

void dn::Application::WindowPosCallback(GLFWwindow * p_window, int p_x, int p_y)
{
	dn::Window * win = dn::Application::_windows.at(p_window);
	if (win)
	{
		if (win->IsOpen())
		{
			win->SetPos(p_x, p_y);
			win->OnPositionChange(p_x, p_y);
		}
		if (win->IsOpen() && win->_atPositionChangeCallback)
			win->_atPositionChangeCallback(win, p_x, p_y);
		if (win->IsOpen())
			win->PositionChangeEvent.Trigger(win, p_x, p_y);
	}
}

void dn::Application::WindowKeyCallback(GLFWwindow * p_window, int p_keycode, int p_scancode, int p_action, int p_mods)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win && win->IsOpen())
	{
		win->_keylogger[p_keycode] = p_action;

		if (win->IsOpen())
		{
			win->OnKey(p_keycode, p_action);
			if (win->IsOpen())
				win->KeyEvent.Trigger(win, p_keycode, p_action);
		}
		if (win->IsOpen() && p_action == GLFW_PRESS)
		{
			win->OnKeyPress(p_keycode);
			if (win->IsOpen() && win->_atKeyPressCallback)
				win->_atKeyPressCallback(win, p_keycode);
			if (win->IsOpen())
				win->KeyPressEvent.Trigger(win, p_keycode);
		}
		else if (win->IsOpen() && p_action == GLFW_RELEASE)
		{
			win->OnKeyRelease(p_keycode);
			if (win->IsOpen() && win->_atKeyReleaseCallback)
				win->_atKeyReleaseCallback(win, p_keycode);
			if (win->IsOpen())
				win->KeyReleaseEvent.Trigger(win, p_keycode);
		}
	}
}

void dn::Application::WindowCloseCallback(GLFWwindow * p_window)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		if (win->IsOpen())
			win->OnClose();
		if (win->IsOpen() && win->_atCloseCallback)
			win->_atCloseCallback(win);
		if (win->IsOpen())
			win->CloseEvent.Trigger(win);
		dn::Application::DestroyGLFWwindow(win, dn::Application::_destroyEraseDefault);
	}
}

void dn::Application::WindowMouseMotionCallback(GLFWwindow * p_window, double p_xpos, double p_ypos)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		win->_mouseX = p_xpos;
		win->_mouseY = p_ypos;
		win->_mouseNormX = ((p_xpos / ((double)win->width() / 2.0)) - 1);
		win->_mouseNormY = (-(p_ypos / ((double)win->height() / 2.0)) + 1);

		if (win->IsOpen())
			win->OnMouseMotion(p_xpos, p_ypos, win->_mouseNormX, win->_mouseNormY);
		if (win->IsOpen() && win->_atMouseMotionCallback)
			win->_atMouseMotionCallback(win, p_xpos, p_ypos);
		if (win->IsOpen())
			win->MouseMotionEvent.Trigger(win, p_xpos, p_ypos);
		if (win->IsOpen())
			win->MouseMotionNormEvent.Trigger(win, win->_mouseNormX, win->_mouseNormY);
	}
}

void dn::Application::WindowMouseButtonCallback(GLFWwindow * p_window, int p_button, int p_action, int p_mods)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		win->_mouselogger[p_button] = p_action;

		if (win->IsOpen())
		{
			win->OnMouseButton(p_button, p_action);
			if (win->IsOpen() && win->_atMouseButtonCallback)
				win->_atMouseButtonCallback(win, p_button, p_action);
			if (win->IsOpen())
				win->MouseButtonEvent.Trigger(win, p_button, p_action);
		}
		if (win->IsOpen() && p_action == GLFW_PRESS)
		{
			win->OnMousePress(p_button);
			if (win->IsOpen() && win->_atMousePressCallback)
				win->_atMousePressCallback(win, p_button);
			if (win->IsOpen())
				win->MousePressEvent.Trigger(win, p_button);
		}
		else if (win->IsOpen() && p_action == GLFW_RELEASE)
		{
			win->OnMouseRelease(p_button);
			if (win->IsOpen() && win->_atMouseReleaseCallback)
				win->_atMouseButtonCallback(win, p_button, p_action);
			if (win->IsOpen())
				win->MouseReleaseEvent.Trigger(win, p_button);
		}
	}
}

void dn::Application::WindowMouseEnterCallback(GLFWwindow * p_window, int p_enter)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		bool entered = (p_enter == GLFW_TRUE ? true : false);
		if (win->IsOpen())
			win->OnMouseEnter(entered);
		if (win->IsOpen())
			win->MouseEnterEvent.Trigger(win, entered);
	}
}

void dn::Application::WindowScrollCallback(GLFWwindow * p_window, double p_xoffset, double p_yoffset)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		if (win->IsOpen())
			win->OnScroll(p_xoffset, p_yoffset);
		if (win->IsOpen() && win->_atScrollCallback)
			win->_atScrollCallback(win, p_xoffset, p_yoffset);
		if (win->IsOpen())
			win->ScrollEvent.Trigger(win, p_xoffset, p_yoffset);
	}
}

void dn::Application::WindowDropCallback(GLFWwindow * p_window, int p_filesCount, const char ** p_filesPath)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		std::vector<std::string> files;
		for (int i = 0; i < p_filesCount; ++i)
			files.push_back(std::string(p_filesPath[i]));
		if (win->IsOpen())
			win->OnFileDrop(files);
		if (win->IsOpen() && win->_atFileDropCallback)
			win->_atFileDropCallback(win, files);
		if (win->IsOpen())
			win->FileDropEvent.Trigger(win, files);
	}
}

void dn::Application::WindowCharCallback(GLFWwindow * p_window, unsigned int p_char)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		if (win->IsOpen())
			win->OnCharInput(p_char);
		if (win->IsOpen() && win->_atCharInputCallback)
			win->_atCharInputCallback(win, p_char);
		if (win->IsOpen())
			win->CharInputEvent.Trigger(win, p_char);
	}
}

void dn::Application::WindowFocusCallback(GLFWwindow * p_window, int p_focus)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (p_focus == GLFW_TRUE)
		dn::Application::_windowFocus = win;
	if (win)
	{
		bool v_focus = (p_focus == GLFW_TRUE ? true : false);
		if (win->IsOpen())
			win->OnFocus(v_focus);
		if (win->IsOpen() && win->_atFocusCallback)
			win->_atFocusCallback(win, v_focus);
		if (win->IsOpen())
			win->FocusEvent.Trigger(win, v_focus);
	}

}

void dn::Application::WindowRefreshCallback(GLFWwindow * p_window)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		if (win->IsOpen())
			win->OnRefresh();
		if (win->IsOpen() && win->_atRefreshCallback)
			win->_atRefreshCallback(win);
		if (win->IsOpen())
			win->RefreshEvent.Trigger(win);
		if (win->IsOpen())
		{
			WindowUpdate(win);
			if (win->IsOpen())
				glfwSwapBuffers(p_window);
		}
	}
}

void dn::Application::WindowIconifyCallback(GLFWwindow * p_window, int p_iconify)
{
	dn::Window * win = dn::Application::GetWindowPtr(p_window);
	if (win)
	{
		bool iconified = (p_iconify == GLFW_TRUE ? true : false);
		if (win->IsOpen())
			win->OnIconify(iconified);
		if (win->IsOpen() && win->_atIconifyCallback)
			win->_atIconifyCallback(win, iconified);
		if (win->IsOpen())
			win->IconifyEvent.Trigger(win, iconified);
	}
}

bool dn::Application::_isRunning = false;
bool dn::Application::_destroyEraseDefault = true;

void(*dn::Application::_atExitCallback)(const std::string &, const int &) = nullptr;
void(*dn::Application::_atStartCallback)() = nullptr;
void(*dn::Application::_atUpdateCallback)() = nullptr;

dn::Window * dn::Application::_windowFocus = nullptr;
dn::Window * dn::Application::_windowContext = nullptr;

std::vector<dn::Shader *> dn::Shader::_shadersToCreate;

std::vector<dn::Window *> dn::Application::_windowsToCreate;
std::vector<dn::Window *> dn::Application::_windowsToDestroy;

std::map<GLFWwindow *, dn::Window *> dn::Application::_windows;
std::map<dn::Window *, GLFWwindow *> dn::Application::_windowsPointer;

bool dn::Application::IsRunning()
{
	return (dn::Application::_isRunning);
}

void dn::Application::Run()
{
	if (dn::Application::IsRunning())
		return;

	if (!glfwInit())
		dn::Application::ExitFailure("GLFW failed to init.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_SAMPLES, 512);

	for (size_t i = 0; i < dn::Application::_windowsToCreate.size(); ++i)
		dn::Application::AddGLFWwindow(dn::Application::_windowsToCreate[i]);
	dn::Application::_windowsToCreate.clear();

	if (glewInit() != GLEW_OK)
		dn::Application::ExitFailure("GLEW failed to init.");

	glEnable(GL_DEPTH);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 0.2f);
	

	dn::Application::_isRunning = true;

	dn::Shader::CreatePrograms();
	dn::Texture::CreateTextures();

	if (dn::Application::_atStartCallback)
		dn::Application::_atStartCallback();

	for (std::map<GLFWwindow *, dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
	{
		dn::Application::ShowWindow(it->second, it->second->IsVisible());
		if (it->second->IsIconified())
			dn::Application::IconifyWindow(it->second);
		if (it->second == dn::Application::_windowFocus)
			dn::Application::FocusWindow(it->second);
		if (it->second->_positionSpecified)
			dn::Application::UpdateGlfwWindowPos(it->second);
		if (it->second->_cursorSpecified)
			dn::Application::UpdateGlfwWindowCursorPos(it->second);
		else
			glfwGetWindowPos(it->first, &it->second->_x, &it->second->_y);

		dn::Application::WindowStart(it->second);
	}
	DestroyClosedWindows();

	do
	{
		glfwPollEvents();
		
		if (dn::Application::_atUpdateCallback)
			dn::Application::_atUpdateCallback();

		for (std::map<GLFWwindow *, dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		{
			dn::Application::WindowUpdate(it->second);
			glfwSwapBuffers(it->first);
		}

		if (dn::Sound::_fmodSystem)
			dn::Sound::_fmodSystem->update();

		DestroyClosedWindows();

	} while (_isRunning);
	dn::Application::TerminateSuccess();
}

void dn::Application::AtExit(void(*p_atExitCallback)(const std::string &, const int &))
{
	dn::Application::_atExitCallback = p_atExitCallback;
}

void dn::Application::AtStart(void(*p_atStartCallback)())
{
	dn::Application::_atStartCallback = p_atStartCallback;
}

void dn::Application::AtUpdate(void(*p_atUpdateCallback)())
{
	dn::Application::_atUpdateCallback = p_atUpdateCallback;
}

void dn::Application::Exit(const std::string & p_msg, const int & p_code)
{
	if (dn::Application::_atExitCallback)
		dn::Application::_atExitCallback(p_msg, p_code);
	if (dn::Application::IsRunning())
	{
		_isRunning = false;

		dn::Application::_destroyEraseDefault = false;
		for (std::map<GLFWwindow *, dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
			it->second->Close();
		dn::Application::_destroyEraseDefault = true;
		dn::Application::_windows.clear();
		dn::Application::_windowsPointer.clear();

		glfwTerminate();
	}

	std::cout << p_msg << std::endl;
	std::exit(p_code);
}

void dn::Application::ExitFailure(const std::string & p_msg)
{
	dn::Application::Exit(p_msg, EXIT_FAILURE);
}

void dn::Application::ExitSuccess(const std::string & p_msg)
{
	dn::Application::Exit(p_msg, EXIT_SUCCESS);
}

int dn::Application::Terminate(const int & p_code)
{
	if (dn::Application::IsRunning())
	{
		_isRunning = false;

		dn::Application::_destroyEraseDefault = false;
		for (std::map<GLFWwindow *, dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
			it->second->Close();
		dn::Application::_windows.clear();
		dn::Application::_windowsPointer.clear();

		glfwTerminate();
	}
	return p_code;
}

int dn::Application::TerminateSuccess()
{
	return dn::Application::Terminate(EXIT_SUCCESS);
}

int dn::Application::TerminateFailure()
{
	return dn::Application::Terminate(EXIT_FAILURE);
}

void dn::Application::AddWindow(dn::Window * p_window)
{
	if (p_window)
	{
		if (dn::Application::IsRunning())
			dn::Application::AddGLFWwindow(p_window);
		else
			dn::Application::_windowsToCreate.push_back(p_window);
	}
}

void dn::Application::CloseWindow(dn::Window * p_window)
{
	if (p_window && dn::Application::IsRunning())
		dn::Application::_windowsToDestroy.push_back(p_window);
	else if (p_window)
	{
		for (std::vector<dn::Window *>::iterator it = dn::Application::_windowsToCreate.begin(); it != dn::Application::_windowsToCreate.end(); ++it)
		{
			if (*it == p_window)
			{
				dn::Application::_windowsToCreate.erase(it);
				break;
			}
		}
	}
}

void dn::Application::ShowWindow(dn::Window * p_window, const bool & p_showWindow)
{
	if (dn::Application::IsRunning() && p_window && dn::Application::_windowsPointer.count(p_window))
	{
		if (p_showWindow)
			glfwShowWindow(dn::Application::_windowsPointer.at(p_window));
		else
			glfwHideWindow(dn::Application::_windowsPointer.at(p_window));
	}
}

void dn::Application::IconifyWindow(dn::Window * p_window)
{
	if (dn::Application::IsRunning() && p_window && dn::Application::GetWindowId(p_window))
	{
		glfwIconifyWindow(dn::Application::GetWindowId(p_window));
	}
}

void dn::Application::FocusWindow(dn::Window * p_window)
{
	if (p_window)
	{
		if (dn::Application::IsRunning())
			glfwFocusWindow(dn::Application::GetWindowId(p_window));
		dn::Application::_windowFocus = p_window;
	}
}

GLFWwindow * dn::Application::GetWindowId(dn::Window * p_window)
{
	if (dn::Application::_windowsPointer.count(p_window))
		return dn::Application::_windowsPointer.at(p_window);
	return nullptr;
}

dn::Window * dn::Application::GetWindowPtr(GLFWwindow * p_window)
{
	if (dn::Application::_windows.count(p_window))
		return dn::Application::_windows.at(p_window);
	return nullptr;
}

dn::Window * dn::Application::FindWindowByTitle(const std::string & p_title)
{
	for (std::map<GLFWwindow *, dn::Window *>::iterator it = dn::Application::_windows.begin(); it != dn::Application::_windows.end(); ++it)
		if (it->second && it->second->title() == p_title)
			return it->second;
	return nullptr;
}

dn::Window * dn::Application::GetFocusedWindow()
{
	return dn::Application::_windowFocus;
}

dn::Window * dn::Application::GetCurrentContext()
{
	return dn::Application::_windowContext;
}

void dn::Application::SetCurrentContext(dn::Window * p_window)
{
	if (p_window != dn::Application::_windowContext)
	{
		dn::Application::_windowContext = p_window;
		GLFWwindow * id = dn::Application::GetWindowId(p_window);
		if (id)
			glfwMakeContextCurrent(id);
	}
}

void dn::Application::UpdateGlfwWindowTitle(dn::Window * p_window)
{
	if (dn::Application::IsRunning() && p_window)
		glfwSetWindowTitle(dn::Application::_windowsPointer.at(p_window), p_window->title().c_str());
}

void dn::Application::UpdateGlfwWindowSize(dn::Window * p_window)
{
	if (dn::Application::IsRunning() && p_window)
		glfwSetWindowSize(dn::Application::_windowsPointer.at(p_window), p_window->width(), p_window->height());
}

void dn::Application::UpdateGlfwWindowPos(dn::Window * p_window)
{
	if (dn::Application::IsRunning() && p_window)
		glfwSetWindowPos(dn::Application::_windowsPointer.at(p_window), p_window->x(), p_window->y());
	else if (p_window)
		p_window->_positionSpecified = true;
}

void dn::Application::UpdateGlfwWindowCursorPos(dn::Window * p_window)
{
	if (dn::Application::IsRunning() && p_window)
		glfwSetCursorPos(dn::Application::GetWindowId(p_window), p_window->_mouseX, p_window->_mouseY);
	else if (p_window)
		p_window->_cursorSpecified = true;
}

void dn::Application::AddGLFWwindow(dn::Window * p_window)
{
	if (p_window)
	{
		GLFWwindow * windowId = glfwCreateWindow(p_window->width(), p_window->height(), p_window->title().c_str(), nullptr, nullptr);

		if (windowId)
		{
			glfwMakeContextCurrent(windowId);
			dn::Application::_windowContext = p_window;

			glfwSetWindowSizeCallback(windowId, dn::Application::WindowSizeCallback);
			glfwSetWindowPosCallback(windowId, dn::Application::WindowPosCallback);
			glfwSetKeyCallback(windowId, dn::Application::WindowKeyCallback);
			glfwSetWindowCloseCallback(windowId, dn::Application::WindowCloseCallback);
			glfwSetCursorPosCallback(windowId, dn::Application::WindowMouseMotionCallback);
			glfwSetMouseButtonCallback(windowId, dn::Application::WindowMouseButtonCallback);
			glfwSetScrollCallback(windowId, dn::Application::WindowScrollCallback);
			glfwSetDropCallback(windowId, dn::Application::WindowDropCallback);
			glfwSetCharCallback(windowId, dn::Application::WindowCharCallback);
			glfwSetWindowFocusCallback(windowId, dn::Application::WindowFocusCallback);
			glfwSetWindowRefreshCallback(windowId, dn::Application::WindowRefreshCallback);
			glfwSetWindowIconifyCallback(windowId, dn::Application::WindowIconifyCallback);
			glfwSetCursorEnterCallback(windowId, dn::Application::WindowMouseEnterCallback);

			dn::Application::_windows.insert(std::make_pair(windowId, p_window));
			dn::Application::_windowsPointer.insert(std::make_pair(p_window, windowId));
		}
	}
}

void dn::Application::DestroyGLFWwindow(dn::Window * p_window, const bool & p_erase)
{
	if (p_window)
	{
		if (dn::Application::IsRunning())
		{
			p_window->Hide();

			glfwDestroyWindow(dn::Application::GetWindowId(p_window));

			if (p_erase)
			{
				dn::Application::_windows.erase(dn::Application::GetWindowId(p_window));
				dn::Application::_windowsPointer.erase(p_window);
			}

			if (dn::Application::_windows.size() == 0)
				dn::Application::_isRunning = false;
		}
	}
}

void dn::Application::DestroyClosedWindows()
{
	for (size_t i = 0; i < dn::Application::_windowsToDestroy.size(); ++i)
		dn::Application::DestroyGLFWwindow(dn::Application::_windowsToDestroy[i], true);
	dn::Application::_windowsToDestroy.clear();
}

