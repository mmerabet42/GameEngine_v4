#pragma once

#include <vector>
#include <map>
#include <string>
#include "Event.h"

namespace dn
{
	enum KeyState { KeyUp, KeyDown, KeyHold };

	class Application;

	/*A window can be controlled with callbacks or by inheriting the class and overriding his virtual member functions*/
	class Window
	{
		friend class dn::Application;
	public:

		Window(const std::string & p_title, const int & p_width, const int & p_height);
		Window(const std::string & p_title, const int & p_width, const int & p_height, const int & p_x, const int & p_y);

		~Window();

		std::string title() const;

		int width() const;
		int height() const;

		bool IsVisible() const;
		bool IsOpen() const;
		bool IsFocus() const;
		bool IsIconified() const;

		int x() const;
		int y() const;

		void SetFocus();
		void SetIconify();

		void SetTitle(const std::string & p_title);

		void SetWidth(const int & p_width);
		void SetHeight(const int & p_height);
		void SetSize(const int & p_width, const int & p_height);

		void SetPosX(const int & p_x);
		void SetPosY(const int & p_y);
		void SetPos(const int & p_x, const int & p_y);

		void SetCursorX(const double & p_x, const bool & p_normalized = false);
		void SetCursorY(const double & p_y, const bool & p_normalized = false);
		void SetCursorPos(const double & p_x, const double & p_y, const bool & p_normalized = false);

		bool GetKey(const int & p_key);
		bool GetKeyDown(const int & p_key);
		bool GetKeyUp(const int & p_key);

		bool GetMouse(const int & p_button);
		bool GetMouseDown(const int & p_button);
		bool GetMouseUp(const int & p_button);

		double GetMouseX(const bool & normalize = true) const;
		double GetMouseY(const bool & normalize = true) const;

		void SetAtStartCallback(void(*p_atStartCallback)(dn::Window *));
		void SetAtUpdateCallback(void(*p_atUpdateCallback)(dn::Window *));
		void SetAtCloseCallback(void(*p_atCloseCallback)(dn::Window *));
		void SetAtSizeChangeCallback(void(*p_atSizeChangeCallback)(dn::Window *, const int &, const int &));
		void SetAtPositionChangeCallback(void(*p_atPositionChangeCallback)(dn::Window *, const int &, const int &));
		void SetAtKeyCallback(void(*p_atKeyCallback)(dn::Window *, const int &, const int &));
		void SetAtKeyPressCallback(void(*p_atKeyPressCallback)(dn::Window *, const int &));
		void SetAtKeyReleaseCallback(void(*p_atKeyReleaseCallback)(dn::Window *, const int &));
		void SetAtKeyHoldCallback(void(*p_atKeyHoldCallback)(dn::Window *, const int &));
		void SetAtMouseMotionCallback(void(*p_atMouseMotionCallback)(dn::Window *, const double &, const double &));
		void SetAtMouseButtonCallback(void(*p_atMouseButtonCallback)(dn::Window *, const int &, const int &));
		void SetAtMousePressCallback(void(*p_atMousePressCallback)(dn::Window *, const int &));
		void SetAtMouseReleaseCallback(void(*p_atMouseReleaseCallback)(dn::Window *, const int &));
		void SetAtScrollCallback(void(*p_atScrollCallback)(dn::Window *, const double &, const double &));
		void SetAtFileDropCallback(void(*p_atFileDropCallback)(dn::Window *, const std::vector<std::string> &));
		void SetAtCharInputCallback(void(*p_atCharInputCallback)(dn::Window *, const unsigned int &));
		void SetAtFocusCallback(void(*p_atFocusCallback)(dn::Window *, const bool &));
		void SetAtRefreshCallback(void(*p_atRefreshCallback)(dn::Window *));
		void SetAtIconifyCallback(void(*p_atIconifyCallback)(dn::Window *, const bool &));

		void SetCallbacksDefault();

		void SetVisible(const bool & p_visibility);

		void Show();
		void Hide();

		void Close();

		// SIGNALS :
		dn::PriorityEvent<dn::Window *> StartEvent;
		dn::PriorityEvent<dn::Window *> UpdateEvent;
		dn::PriorityEvent<dn::Window *> CloseEvent;
		dn::PriorityEvent<dn::Window *, const int &, const int &> SizeChangeEvent;
		dn::PriorityEvent<dn::Window *, const int &, const int &> PositionChangeEvent;
		dn::PriorityEvent<dn::Window *, const int &, const int &> KeyEvent;
		dn::PriorityEvent<dn::Window *, const int &> KeyPressEvent;
		dn::PriorityEvent<dn::Window *, const int &> KeyReleaseEvent;
		dn::PriorityEvent<dn::Window *, const int &> KeyHoldEvent;
		dn::PriorityEvent<dn::Window *, const double &, const double &> MouseMotionEvent;
		dn::PriorityEvent<dn::Window *, const double &, const double &> MouseMotionNormEvent;
		dn::PriorityEvent<dn::Window *, const int &, const int &> MouseButtonEvent;
		dn::PriorityEvent<dn::Window *, const int &> MousePressEvent;
		dn::PriorityEvent<dn::Window *, const int &> MouseReleaseEvent;
		dn::PriorityEvent<dn::Window *, const bool &> MouseEnterEvent;
		dn::PriorityEvent<dn::Window *, const double &, const double &> ScrollEvent;
		dn::PriorityEvent<dn::Window *, const std::vector<std::string> &> FileDropEvent;
		dn::PriorityEvent<dn::Window *, const unsigned int &> CharInputEvent;
		dn::PriorityEvent<dn::Window *, const bool &> FocusEvent;
		dn::PriorityEvent<dn::Window *> RefreshEvent;
		dn::PriorityEvent<dn::Window *, const bool &> IconifyEvent;

	protected:

		std::string _title;
		int _width;
		int _height;

		int _x;
		int _y;
		bool _positionSpecified;

		bool _isVisible;
		bool _isIconify;
		bool _isOpen;

		std::map<int, int> _keylogger;
		std::map<int, int> _mouselogger;

		double _mouseX;
		double _mouseY;

		double _mouseNormX;
		double _mouseNormY;

		bool _cursorSpecified;

		void(*_atStartCallback)(dn::Window *);
		void(*_atUpdateCallback)(dn::Window *);
		void(*_atCloseCallback)(dn::Window *);
		void(*_atSizeChangeCallback)(dn::Window *, const int &, const int &);
		void(*_atPositionChangeCallback)(dn::Window *, const int &, const int &);
		void(*_atKeyCallback)(dn::Window *, const int &, const int &);
		void(*_atKeyPressCallback)(dn::Window *, const int &);
		void(*_atKeyReleaseCallback)(dn::Window *, const int &);
		void(*_atKeyHoldCallback)(dn::Window *, const int &);
		void(*_atMouseMotionCallback)(dn::Window *, const double &, const double &);
		void(*_atMouseButtonCallback)(dn::Window *, const int &, const int &);
		void(*_atMousePressCallback)(dn::Window *, const int &);
		void(*_atMouseReleaseCallback)(dn::Window *, const int &);
		void(*_atScrollCallback)(dn::Window *, const double &, const double &);
		void(*_atFileDropCallback)(dn::Window *, const std::vector<std::string> &);
		void(*_atCharInputCallback)(dn::Window *, const unsigned int &);
		void(*_atFocusCallback)(dn::Window *, const bool &);
		void(*_atRefreshCallback)(dn::Window *);
		void(*_atIconifyCallback)(dn::Window *, const bool &);

		virtual void Start() { }
		virtual void Update() { }
		virtual void OnClose() { }
		virtual void OnSizeChange(const int & p_width, const int & p_height) { }
		virtual void OnPositionChange(const int & p_x, const int & p_y) { }
		virtual void OnKey(const int & p_keycode, const int & p_action) { }
		virtual void OnKeyPress(const int & p_keycode) { }
		virtual void OnKeyRelease(const int & p_keycode) { }
		virtual void OnKeyHold(const int & p_keycode) { }
		virtual void OnMouseMotion(const double & p_xpos, const double & p_ypos, const double & p_xposNorm, const double & p_yposNorm) { }
		virtual void OnMouseButton(const int & p_button, const int & p_action) { }
		virtual void OnMousePress(const int & p_button) { }
		virtual void OnMouseRelease(const int & p_button) { }
		virtual void OnMouseEnter(const bool & p_enter) { }
		virtual void OnScroll(const double & p_xoffset, const double & p_yoffset) { }
		virtual void OnFileDrop(const std::vector<std::string> & p_files) { }
		virtual void OnCharInput(const unsigned int & p_char) { }
		virtual void OnFocus(const bool & p_focus) { }
		virtual void OnRefresh() { }
		virtual void OnIconify(const bool & p_iconify) { }
	};
}

