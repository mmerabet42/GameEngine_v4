## GameEngine_v4

This game engine is a project that i started by myself with the goal of learning the OpenGL and GLFW libraries, but also improving my C++ knowledge.

My main inspiration was the Unity3D engine, but more precisely its system of 'Components' and 'GameObject'.

A 'GameObject' is an abstract object in a 3D scene, that can have one or more component attached to it. The components are a way to define the GameObject to make it less and less abstract. For example there is a component for rendering the object, another one for its physical behaviour with its surroundings, one for its position, scale and rotation in space, etc.

This is precisely this abstraction that i wanted to reimplement through this project, and it was possible under the power of the OOP (Oriented Object Programming) of the C++ language.

For a better understanding on how near it is to the original Unity system, this is how you would create an object with a *Transorm* component attached to it (Thankfully C# and C++ have a similar syntax for templates):
```C++
dn::Object *obj = new dn::Object();

obj->AddComponent<dn::Transform>();
```

As there was no window abstraction, it had to be done too, this is where the GLFW library shows its use. GLFW gives a low-level abstraction for window handlings and callback, i just did the high-level abstraction:
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

Unfortunately, the project isn't done, and has been developed in a Windows OS on the Visual Studio IDE, so it may not compile on other OS's.

But a new and better version is on its way with a deeper documentation. Which is [Dyne](https://github.com/mmerabet42/Dyne)
