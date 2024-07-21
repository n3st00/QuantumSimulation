#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int glfw_init()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


int main()
{
	glfw_init();
	// create a new window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//set coordinates of the triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //  lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
	};

	GLuint indices[] =
	{
		0, 3, 5, // lower left triangle
		3, 2, 4, // lower right triangle
		5, 4, 1 // upper triangle
	};

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	glfwSetKeyCallback(window, key_callback);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // 

	// initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize glad" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	

	
	GLuint VAO, EBO; // vertex buffer object 

	glGenVertexArrays(1, &VAO); // pointers to one ore more VBOs and tells OpenGL how to interpret them. needed to quickly switch between VBOs
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices
		, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // helps communicating with a vertex shader from the outside
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();
	}
	// cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;

}