#define GLFW_INCLUDE_ES3
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include "svpng.inc"
#include "loaders/shader_loader.h"
#include "loaders/program_loader.h"
#include "loaders/png_loader.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char *argv[])
{
	glfwInit();
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow *window = glfwCreateWindow(1920, 1080, "My Title", NULL, NULL);
	if (!window)
		return EXIT_FAILURE;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	//0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	//1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	//0.5f, 0.5f
	};
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLuint program = load_program("v.glsl", "f.glsl");
	// GLuint texture = load_png_texture("sister.png");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	// glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		// glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		// glBindTexture(GL_TEXTURE_2D, 0);
		glfwSwapBuffers(window);
	}
	// free_png_texture(texture);
	free_program(program);
	glfwTerminate();
	return 0;
}