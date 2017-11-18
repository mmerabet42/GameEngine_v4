#include "Window.h"

#include "Application.h"

dn::Window::Window(const std::string & p_title, const int & p_width, const int & p_height)
	: _title(p_title), _width(p_width), _height(p_height), _x(0), _y(0), _isVisible(true), _positionSpecified(false), _cursorSpecified(false), _isOpen(true), _isIconify(false)
{
	this->SetCallbacksDefault();
	dn::Application::AddWindow(this);
}

dn::Window::Window(const std::string & p_title, const int & p_width, const int & p_height, const int & p_x, const int & p_y)
	: Window(p_title, p_width, p_height)
{
	this->_x = p_x;
	this->_y = p_y;
	this->_positionSpecified = true;
}

dn::Window::~Window()
{
	this->Close();
}

std::string dn::Window::title() const
{
	return this->_title;
}

int dn::Window::width() const
{
	return this->_width;
}

int dn::Window::height() const
{
	return this->_height;
}

bool dn::Window::IsVisible() const
{
	return this->_isVisible;
}

bool dn::Window::IsOpen() const
{
	return this->_isOpen;
}

bool dn::Window::IsFocus() const
{
	return (this == dn::Application::GetFocusedWindow());
}

bool dn::Window::IsIconified() const
{
	return this->_isIconify;
}

int dn::Window::x() const
{
	return this->_x;
}

int dn::Window::y() const
{
	return this->_y;
}

void dn::Window::SetFocus()
{
	dn::Application::FocusWindow(this);
}

void dn::Window::SetIconify()
{
	this->_isIconify = true;
	dn::Application::IconifyWindow(this);
}

void dn::Window::SetTitle(const std::string & p_title)
{
	if (this->_title != p_title)
	{
		this->_title = p_title;
		dn::Application::UpdateGlfwWindowTitle(this);
	}
}

void dn::Window::SetWidth(const int & p_width)
{
	if (this->_width != p_width)
	{
		this->_width = p_width;
		dn::Application::UpdateGlfwWindowSize(this);
	}
}

void dn::Window::SetHeight(const int & p_height)
{
	if (this->_height != p_height)
	{
		this->_height = p_height;
		dn::Application::UpdateGlfwWindowSize(this);
	}
}

void dn::Window::SetSize(const int & p_width, const int & p_height)
{
	if (this->_width != p_width || this->_height != p_height)
	{
		this->_width = p_width;
		this->_height = p_height;
		dn::Application::UpdateGlfwWindowSize(this);
	}
}

void dn::Window::SetPosX(const int & p_x)
{
	this->_positionSpecified = true;
	if (this->_x != p_x)
	{
		this->_x = p_x;
		dn::Application::UpdateGlfwWindowPos(this);
	}
}

void dn::Window::SetPosY(const int & p_y)
{
	this->_positionSpecified = true;
	if (this->_y != p_y)
	{
		this->_y = p_y;
		dn::Application::UpdateGlfwWindowPos(this);
	}
}

void dn::Window::SetPos(const int & p_x, const int & p_y)
{
	this->_positionSpecified = true;
	if (this->_x != p_x || this->_y != p_y)
	{
		this->_x = p_x;
		this->_y = p_y;
		dn::Application::UpdateGlfwWindowPos(this);
	}
}

void dn::Window::SetCursorX(const double & p_x, const bool & p_normalized)
{
	if (p_x != this->GetMouseX(p_normalized))
	{
		this->_mouseX = (p_normalized ? ((p_x + 1) * (this->width() / 2.0)) : p_x);
		this->_mouseNormX = (p_normalized ? p_x : (p_x / (this->width() / 2.0)) - 1);
		dn::Application::UpdateGlfwWindowCursorPos(this);
	}
}

void dn::Window::SetCursorY(const double & p_y, const bool & p_normalized)
{
	if (p_y != this->GetMouseY(p_normalized))
	{
		this->_mouseY = (p_normalized ? (-(p_y - 1) * (this->height() / 2.0)) : p_y);
		this->_mouseNormY = (p_normalized ? p_y : -(p_y / this->height() / 2.0) + 1);
		dn::Application::UpdateGlfwWindowCursorPos(this);
	}
}

void dn::Window::SetCursorPos(const double & p_x, const double & p_y, const bool & p_normalized)
{
	if (p_x != this->GetMouseX(p_normalized) && p_y != this->GetMouseY(p_normalized))
	{
		this->_mouseX = (p_normalized ? ((p_x + 1) * (this->width() / 2.0)) : p_x);
		this->_mouseNormX = (p_normalized ? p_x : (p_x / (this->width() / 2.0)) - 1);

		this->_mouseY = (p_normalized ? (-(p_y - 1) * (this->height() / 2.0)) : p_y);
		this->_mouseNormY = (p_normalized ? p_y : -(p_y / this->height() / 2.0) + 1);
		dn::Application::UpdateGlfwWindowCursorPos(this);
		
	}
}

bool dn::Window::GetKey(const int & p_key)
{
	return (this->_keylogger[p_key] > 0);
}

bool dn::Window::GetKeyDown(const int & p_key)
{
	if (this->_keylogger[p_key] == 1)
	{
		this->_keylogger[p_key] = 2;
		return true;
	}
	return false;
}

bool dn::Window::GetKeyUp(const int & p_key)
{
	if (this->_keylogger[p_key] == 0)
	{
		this->_keylogger[p_key] = -1;
		return true;
	}
	return false;
}

bool dn::Window::GetMouse(const int & p_key)
{
	return (this->_mouselogger[p_key] > 0);
}

bool dn::Window::GetMouseDown(const int & p_key)
{
	if (this->_mouselogger[p_key] == 1)
	{
		this->_mouselogger[p_key] = 2;
		return true;
	}
	return false;
}

bool dn::Window::GetMouseUp(const int & p_key)
{
	if (this->_mouselogger[p_key] == 0)
	{
		this->_mouselogger[p_key] = -1;
		return true;
	}
	return false;
}

double dn::Window::GetMouseX(const bool & normalize) const
{
	return (normalize ? this->_mouseNormX : this->_mouseX);
}
double dn::Window::GetMouseY(const bool & normalize) const
{
	return (normalize ? this->_mouseNormY : this->_mouseY);
}

void dn::Window::SetAtStartCallback(void(*p_atStartCallback)(dn::Window *))
{
	this->_atStartCallback = p_atStartCallback;
}

void dn::Window::SetAtUpdateCallback(void(*p_onUpdateCallback)(dn::Window *))
{
	this->_atUpdateCallback = p_onUpdateCallback;
}

void dn::Window::SetAtCloseCallback(void(*p_atCloseCallback)(dn::Window *))
{
	this->_atCloseCallback = p_atCloseCallback;
}

void dn::Window::SetAtSizeChangeCallback(void(*p_atSizeChangeCallback)(dn::Window *, const int &, const int &))
{
	this->_atSizeChangeCallback = p_atSizeChangeCallback;
}

void dn::Window::SetAtPositionChangeCallback(void(*p_atPositionChangeCallback)(dn::Window *, const int &, const int &))
{
	this->_atPositionChangeCallback = p_atPositionChangeCallback;
}

void dn::Window::SetAtKeyCallback(void(*p_atKeyCallback)(dn::Window *, const int &, const int &))
{
	this->_atKeyCallback = p_atKeyCallback;
}

void dn::Window::SetAtKeyPressCallback(void(*p_atKeyPressCallback)(dn::Window *, const int &))
{
	this->_atKeyPressCallback = p_atKeyPressCallback;
}

void dn::Window::SetAtKeyReleaseCallback(void(*p_atKeyReleaseCallback)(dn::Window *, const int &))
{
	this->_atKeyReleaseCallback = p_atKeyReleaseCallback;
}

void dn::Window::SetAtKeyHoldCallback(void(*p_atKeyHoldCallback)(dn::Window *, const int &))
{
	this->_atKeyHoldCallback = p_atKeyHoldCallback;
}

void dn::Window::SetAtMouseMotionCallback(void(*p_atMouseMotionCallback)(dn::Window *, const double &, const double &))
{
	this->_atMouseMotionCallback = p_atMouseMotionCallback;
}

void dn::Window::SetAtMouseButtonCallback(void(*p_atMouseButtonCallback)(dn::Window *, const int &, const int &))
{
	this->_atMouseButtonCallback = p_atMouseButtonCallback;
}

void dn::Window::SetAtMousePressCallback(void(*p_atMousePressCallback)(dn::Window *, const int &))
{
	this->_atMousePressCallback = p_atMousePressCallback;
}

void dn::Window::SetAtMouseReleaseCallback(void(*p_atMouseReleaseCallback)(dn::Window *, const int &))
{
	this->_atMouseReleaseCallback = p_atMouseReleaseCallback;
}

void dn::Window::SetAtScrollCallback(void(*p_atScrollCallback)(dn::Window *, const double &, const double &))
{
	this->_atScrollCallback = p_atScrollCallback;
}

void dn::Window::SetAtFileDropCallback(void(*p_atFileDropCallback)(dn::Window *, const std::vector<std::string> &))
{
	this->_atFileDropCallback = p_atFileDropCallback;
}

void dn::Window::SetAtCharInputCallback(void(*p_atCharInputCallback)(dn::Window *, const unsigned int &))
{
	this->_atCharInputCallback = p_atCharInputCallback;
}

void dn::Window::SetAtFocusCallback(void(*p_atFocusCallback)(dn::Window *, const bool &))
{
	this->_atFocusCallback = p_atFocusCallback;
}

void dn::Window::SetAtRefreshCallback(void(*p_atRefreshCallback)(dn::Window *))
{
	this->_atRefreshCallback = p_atRefreshCallback;
}

void dn::Window::SetAtIconifyCallback(void(*p_atIconifyCallback)(dn::Window *, const bool &))
{
	this->_atIconifyCallback = p_atIconifyCallback;
}

void dn::Window::SetCallbacksDefault()
{
	this->_atPositionChangeCallback = nullptr;
	this->_atSizeChangeCallback = nullptr;
	this->_atStartCallback = nullptr;
	this->_atUpdateCallback = nullptr;
	this->_atKeyCallback = nullptr;
	this->_atKeyPressCallback = nullptr;
	this->_atKeyReleaseCallback = nullptr;
	this->_atKeyHoldCallback = nullptr;
	this->_atCloseCallback = nullptr;
	this->_atMouseMotionCallback = nullptr;
	this->_atMouseButtonCallback = nullptr;
	this->_atMousePressCallback = nullptr;
	this->_atMouseReleaseCallback = nullptr;
	this->_atScrollCallback = nullptr;
	this->_atFileDropCallback = nullptr;
	this->_atCharInputCallback = nullptr;
	this->_atFocusCallback = nullptr;
	this->_atRefreshCallback = nullptr;
	this->_atIconifyCallback = nullptr;
}

void dn::Window::SetVisible(const bool & p_visible)
{
	this->_isVisible = p_visible;
	dn::Application::ShowWindow(this, this->_isVisible);
}

void dn::Window::Show()
{
	if (this->_isVisible == true)
		return;
	this->_isVisible = true;
	dn::Application::ShowWindow(this, true);
}

void dn::Window::Hide()
{
	if (this->_isVisible == false)
		return;
	this->_isVisible = false;
	dn::Application::ShowWindow(this, false);
}

void dn::Window::Close()
{
	this->_isOpen = false;

	this->CharInputEvent.Release();
	this->CloseEvent.Release();
	this->FileDropEvent.Release();
	this->FocusEvent.Release();
	this->KeyEvent.Release();
	this->KeyHoldEvent.Release();
	this->KeyPressEvent.Release();
	this->KeyReleaseEvent.Release();
	this->MouseButtonEvent.Release();
	this->MouseMotionEvent.Release();
	this->MouseMotionNormEvent.Release();
	this->MousePressEvent.Release();
	this->MouseReleaseEvent.Release();
	this->MouseEnterEvent.Release();
	this->PositionChangeEvent.Release();
	this->RefreshEvent.Release();
	this->ScrollEvent.Release();
	this->SizeChangeEvent.Release();
	this->StartEvent.Release();
	this->UpdateEvent.Release();
	this->IconifyEvent.Release();

	this->SetCallbacksDefault();

	dn::Application::CloseWindow(this);
}