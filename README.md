## GameEngine_v4

This game engine is a project that i started by myself with the goal of learning the OpenGL and GLFW libraries, but also improving my C++ knowledge.

My main inspiration was Unity, i wanted to create the same system of components and gameobjects, and all of this was possible with the OOP of C++. To create a gameobject and add a *Transform* component you would do as follow:
```C++
dn::Object *obj = new dn::Object();

obj->AddComponent<dn::Transform>();
```

And all of the window abstraction systen had to be done too, the callback system etc.
```C++
dn::Window *win = new dn::Window(100, 100);

win->KeyPressEvent.AddListener([](dn::Window, const int &key) {
  // Callback will be called everytime a key is pressed
});
```

The project isn't done, and has been developed in a Windows OS in the Visual Studio IDE, so it may not compile on other OS's.
