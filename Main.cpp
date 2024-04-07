#include<iostream>
#include<stb/stb_image.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;


// Triangle with Index Buffer
//GLfloat vertices[] =
//{
//
//	//               COORDINATES                  /     COLORS           //
//	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.03f,  0.02f, // Lower left corner
//	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     -0.8f, 0.3f,  0.02f, // Lower right corner
//	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.1f, 0.06f,  0.32f, // Upper corner
//	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.4f, 0.45f, 0.17f, // Inner left
//	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     -0.9f, 0.45f, 0.17f, // Inner right
//	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     -0.5f, 0.3f,  0.02f  // Inner down
//};
// Vertices coordinates for TEXTURE
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.10f, 0.10f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.10f, 0.20f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.10f, 0.30f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.10f, 0.40f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};
// Indices for vertices order
//GLuint indices[] =
//{
//	0, 3, 5, // Lower left triangle
//	3, 2, 4, // Lower right triangle
//	5, 4, 1 // Upper triangle
//};

// TEXTURE Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


//// Triangle
//	GLfloat vertices[] =
//{
//	//	//               COORDINATES                  /     COLORS           //
//	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
//	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     -0.8f, 0.3f,  0.02f, // Lower right corner
//	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.1f, 0.6f,  0.32f, // Upper corner
//};



int main()
{
	// Initialize GLFW
	glfwInit();

	//Tell GLFW what version of OPENGL being used
	//Using version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//TELL GLFW we are using core profile -> modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "3DLoader", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices 
	// FIX WHEN NOT HAVING INDEX BUFFER
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	/*VAO1.LinkVBO(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkVBO(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));*/

	//TEXTURE
	VAO1.LinkVBO(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkVBO(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkVBO(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	// FIX WHEN NOT HAVING INDEX BUFFER
	EBO1.Unbind();
	
	
	//SCALEUNIFORM
	//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// TEXTURE

	//int widthIMG, heightIMG, numColCh;
	//stbi_set_flip_vertically_on_load(true);

	//unsigned char* bytes = stbi_load("pop_cat.png.png", &widthIMG, &heightIMG, &numColCh, 0);

	//GLuint texture;
	//glGenTextures(1, &texture);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//// Assigns the image to the OpenGL Texture object
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthIMG, heightIMG, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	//// Generates MipMaps
	//glGenerateMipmap(GL_TEXTURE_2D);

	//// Deletes the image data as it is already in the OpenGL Texture object
	//stbi_image_free(bytes);

	//// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	//glBindTexture(GL_TEXTURE_2D, 0);


	//GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	//shaderProgram.Activate();
	//glUniform1i(tex0Uni, 0);

	Texture popCat("texture1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// Variables that help the rotation of the pyramid
	//TIMER IF NO CAMERA
	/*float rotation = 0.0f;
	double prevTime = glfwGetTime();*/

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		//Give value to uniform data right after activate function
		
		// *****
		//3D IMPLEMENTATION

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");



		// Simple timer FOR NO CAMERA
		//double crntTime = glfwGetTime();
		//if (crntTime - prevTime >= 1 / 60)
		//{
		//	rotation += 0.5f;
		//	prevTime = crntTime;
		//}


		//glm::mat4 model = glm::mat4(1.0f);
		//glm::mat4 view = glm::mat4(1.0f);
		//glm::mat4 proj = glm::mat4(1.0f);

		////rotation function to the model matrix giving it the matrix we want to modify the rotation in radians and the axis 
		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		//// Z IS POSITIVE TOWARD VIEWERS.
		//view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));

		////FIELD OF VIEW PROJECTION
		////FROM 0.1f to 100.0f, outside will be clipped
		//proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		


		//// Outputs the matrices into the Vertex Shader
		//int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		//
		////This is to SCALE the triangle
		//glUniform1f(uniID, 0.5f);
		
		//TEXTURE
		//glBindTexture(GL_TEXTURE_2D, texture);
		
		popCat.Bind();
		
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		/*double  timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		// Draw primitives, number of indices, datatype of indices, index of indices

		//Draw 3 indices triangle
		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/
		////Draw 9 indices triangle
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//TEXTURE TEST
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//3D IMPLEMENT

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();

	//FIX WHEN NOT HAVING INDEX BUFFER
	EBO1.Delete();


	//TEXTURE 
	//glDeleteTextures(1, &texture);


	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
// process all input: query GLFW whether relevant keys  are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}