#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

// SHADER 1
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// SHADER 2
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main(void)
{
	glfwInit(); // Initialize OpenGL

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);				   // Tells OpenGL what major version it should use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);				   // Tells OpenGL what minor version it should use
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Tells OpenGL what package of functions it should use. CORE contains all the modern functions and COMPATIBILITY which contains the modern and older functions

	// ALL OPENGL OBJECTS ARE ACCESSED BY REFERENCES

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL); // Datatype of a window object in OpenGL, parameters are width, height, name, if fullscreen,
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	};

	glfwMakeContextCurrent(window); // Tells OpenGL to use the created window, tells it to be in the current context. A context is a sort of object that holds the content of a

	gladLoadGL(); // Used to load the needed OpenGL configurations

	glViewport(0, 0, 800, 800); // Area of the window we want OpenGL to render in

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);		// OpenGL of unsigned integer, used to specify our shader which in this case is a Vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Specify the Shader Source, first param is the reference value, second is the screen amount, third is the source code pointer, last is NULl
	glCompileShader(vertexShader);								// The GPU cant understand the source code so it needs to be compiled into machine code

	// Do the same as above but for fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();	 // A shader program is used to wrap the shaders together, nothing specified in function because it is just one type of shader program
	glAttachShader(shaderProgram, vertexShader); // Used to attach shaders, first param is the reference to the shader program, the other is the reference to the shader itself
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); // Wrap up shader program and pass the shader program reference

	// Deletes both shders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Clears and sets another color, first 3 params are the RGB as floats, the last is alpha, 1 = opaque and 0 = transparent. Back buffer
	glClear(GL_COLOR_BUFFER_BIT);			 // Tells OpenGl to execute the command we tell it to prepare for
	glfwSwapBuffers(window);				 // Swaps back and front buffers since only front buffers we need to see

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); // Tells GFLW to process all polled events, like the window appearing, its size,etc
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window); // Deletes the window
	glfwTerminate();		   // Terminate OpenGL
}