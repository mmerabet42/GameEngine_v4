#pragma once

#include <iostream>

#include <map>
#include <vector>

#include "opengl.h"

namespace dn
{
	class Window;

	class Application
	{
	public:
		static bool IsRunning();

		static void Run();

		static void AtExit(void(*p_atExitCallback)(const std::string &, const int &));
		static void AtStart(void(*p_atStartCallback)());
		static void AtUpdate(void(*p_atUpdateCallback)());

		static void Exit(const std::string & p_msg, const int & p_code = EXIT_SUCCESS);
		static void ExitFailure(const std::string & p_msg);
		static void ExitSuccess(const std::string & p_msg);

		static int Terminate(const int & p_code = EXIT_SUCCESS);
		static int TerminateFailure();
		static int TerminateSuccess();

		static void AddWindow(dn::Window * p_window);
		static void CloseWindow(dn::Window * p_window);

		static void ShowWindow(dn::Window * p_window, const bool & p_showState);
		static void IconifyWindow(dn::Window * p_window);
		static void FocusWindow(dn::Window * p_window);

		static GLFWwindow * GetWindowId(dn::Window * p_window);
		static dn::Window * GetWindowPtr(GLFWwindow * p_window);
		static dn::Window * FindWindowByTitle(const std::string & p_title);

		static dn::Window * GetFocusedWindow();
		static dn::Window * GetCurrentContext();

		static void SetCurrentContext(dn::Window * p_window);

		static void UpdateGlfwWindowTitle(dn::Window * p_window);
		static void UpdateGlfwWindowSize(dn::Window * p_window);
		static void UpdateGlfwWindowPos(dn::Window * p_window);
		static void UpdateGlfwWindowCursorPos(dn::Window * p_window);

		template <typename T>
		static dn::Application Log(const T & p_t)
		{
			std::cout << p_t;
			return dn::Application();
		}

		template <typename T>
		static dn::Application Logln(const T & p_t)
		{
			std::cout << p_t << std::endl;
			return dn::Application();
		}

		static dn::Application Logln()
		{
			std::cout << std::endl;
			return dn::Application();
		}

	private:

		static bool _isRunning;
		static bool _destroyEraseDefault;
		
		static void(*_atExitCallback)(const std::string &, const int &);
		static void(*_atStartCallback)();
		static void(*_atUpdateCallback)();

		static dn::Window * _windowFocus;
		static dn::Window * _windowContext;

		static std::vector<dn::Window *> _windowsToCreate;
		static std::vector<dn::Window *> _windowsToDestroy;

		static std::map<dn::Window *, GLFWwindow *> _windowsPointer;
		static std::map<GLFWwindow *, dn::Window *> _windows;

		static void AddGLFWwindow(dn::Window * p_window);
		static void DestroyGLFWwindow(dn::Window * p_window, const bool & p_erase = true);

		static void DestroyClosedWindows();

		static void WindowStart(dn::Window * p_window);
		static void WindowUpdate(dn::Window * p_window);
		static void WindowSizeCallback(GLFWwindow * p_window, int p_width, int p_height);
		static void WindowPosCallback(GLFWwindow * p_window, int p_x, int p_y);
		static void WindowKeyCallback(GLFWwindow * p_window, int p_keycode, int p_scancode, int p_action, int p_mods);
		static void WindowCloseCallback(GLFWwindow * p_window);
		static void WindowMouseMotionCallback(GLFWwindow * p_window, double p_xpos, double p_ypos);
		static void WindowMouseButtonCallback(GLFWwindow * p_window, int p_button, int p_action, int p_mods);
		static void WindowMouseEnterCallback(GLFWwindow * p_window, int p_enter);
		static void WindowScrollCallback(GLFWwindow * p_window, double p_xoffset, double y_offset);
		static void WindowDropCallback(GLFWwindow * p_window, int p_filesCount, const char ** p_filesPath);
		static void WindowCharCallback(GLFWwindow * p_window, unsigned int p_char);
		static void WindowFocusCallback(GLFWwindow * p_window, int p_focus);
		static void WindowRefreshCallback(GLFWwindow * p_window);
		static void WindowIconifyCallback(GLFWwindow * p_window, int p_iconify);
	};
}
