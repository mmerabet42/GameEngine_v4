#include "libft.h"

#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLSL(CODE) "#version 330 core\n" #CODE

const char	*vertexSrc = GLSL(
	in vec2 position;
	in vec4 color;

	out vec4 fcolor;

	void main()
	{
		gl_Position = vec4(position, 0, 1);
		fcolor = color;
	}
);

const char	*fragmentSrc = GLSL(
	in vec4 fcolor;

	out vec4 color;

	void main()
	{
		color = fcolor;
	}
);

void	quitapp(const char *msg);

int		main()
{
	GLFWwindow	*w;
	GLint		status;
	char		log[512];
	GLuint		vertexId, fragmentId, progId;
	GLuint		vao, vbos[2];
	GLint		colorAttrib, positionAttrib;

/*
** GLFW initialization
*/

	if (!glfwInit())
		quitapp("Glfw failed to init");

/*
 * Window creation
*/

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	glfwWindowHint(GLFW_SAMPLES, 8);

	if (!(w = glfwCreateWindow(600, 600, "Window title", NULL, NULL)))
		quitapp("Failed to create the window");
	glfwMakeContextCurrent(w);

/*
 * GLEW initialization
*/

	glewExperimental = 1;
	if (glewInit() != GLEW_OK)
		quitapp("Glew failed to init");

/*
 * Shader program creation
*/

	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexSrc, NULL);
	glCompileShader(vertexId);

	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertexId, 512, NULL, log);
		quitapp(log);
	}

	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentId);

	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fragmentId, 512, NULL, log);
		quitapp(log);
	}

	progId = glCreateProgram();
	glAttachShader(progId, vertexId);
	glAttachShader(progId, fragmentId);
	glLinkProgram(progId);

/*
 * Model definition
*/

	GLfloat	vertices[] = {
		0, 0.5f,	1, 1, 1, 1,
		0.5f, 0,	1, 1, 1, 1,
		-0.5f, 0,	1, 1, 1, 1
	};
	GLuint	indices[] = {
		0, 1, 2
	};

/*
 * Vertex array buffers and object creation.
 * Model creation.
*/

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffer(2, vbos);
	glBindVertexArray(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	colorAttrib = glGetAttribLocation(progId, "color");


	return (0);
}

void	quitapp(const char *msg)
{
	glfwTerminate();
	ft_printf("%s\n", msg);
	exit(0);
}
