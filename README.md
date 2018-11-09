## GameEngine_v4

This game engine is a project that i started by myself with the goal of learning the OpenGL and GLFW libraries, but also improving my C++ knowledge.

My main inspiration was Unity, i wanted to create the same system of components and gameobjects, and all of this was possible with the OOP of C++. For example adding a *Transform* component on a created object:
```C++
dn::Object *obj = new dn::Object();

obj->AddComponent<dn::Transform>();
```

And all of the window abstraction system had to be done too, the callback system etc.
```C++
dn::Window *win = new dn::Window(100, 100);
dn::Object *camera = new dn::Object();
dn::Object *obj = new dn::Object();

camera->AddComponent<dn::Camera>();
obj->AddComponent<dn::Transform>();
obj->AddComponent<dn::MeshRenderer>(...);

win->KeyPressEvent.AddListener([](dn::Window *p_win, const int &p_key) {
  // Callback will be called everytime a key is pressed
});

win->StartEvent.AddListener([](dn::Window *p_win) {
  obj->Start();
  camera->Start();
});

win->UpdateEvent.AddListener([](dn::Window *p_win) {
  obj->Update();
  camera->Update();
});

dn::Application::Run();
```

The project isn't done, and has been developed in a Windows OS on the Visual Studio IDE, so it may not compile on other OS's.

But a new and better version is on its way with a deeper documentation.
