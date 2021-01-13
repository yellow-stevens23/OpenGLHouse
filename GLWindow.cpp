#include "GLWindow.h"


GLWindow::GLWindow(GLint width, GLint height, char *windowTitle)
{
    m_width = width;
    m_height = height;
    m_windowName = windowTitle;
    xChange = 0.0f;
    yChange = 0.0f;
    mousedFirstMoved = true;
    

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

void GLWindow::init()
{
    if (!glfwInit())
    {
        cout << "Failed to initialise GLFW" << endl;
        glfwTerminate();
        exit (EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

void GLWindow::openFullscreen()
{
	m_windowName = "Full Screen Window";
	GLFWmonitor* myMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* theVideoMode = glfwGetVideoMode(myMonitor);
	if (theVideoMode != NULL)
	{
		myWindow = glfwCreateWindow(theVideoMode->width, theVideoMode->height, m_windowName, myMonitor, NULL);
	}
	
    	setup();
}

void GLWindow::openWindow()
{
 	myWindow = glfwCreateWindow(m_width, m_height, m_windowName, NULL, NULL); // the first NULL can be monitor to set the monitor currently used
	setup();
}

void GLWindow::pollEvents()
{
    glfwPollEvents();
}

void GLWindow::setColour()
{
    glClearColor(1.0f, 0.83f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

 bool GLWindow::getShouldClose()
 {
     return glfwWindowShouldClose(myWindow);
 }

 void GLWindow::swapBuffers()
 {
     glfwSwapBuffers(myWindow);
 }
 
void GLWindow::setup()
{
	if (!myWindow)
    	{
        	cout << "Failed to open Window....perhaps its painted shut!" << endl;
        	glfwTerminate();
        	exit (EXIT_FAILURE);
    	}
    	glfwMakeContextCurrent(myWindow);  // set up the context for Open GL
    	glfwGetFramebufferSize(myWindow, &bufferWidth, &bufferHeight); // this sets the frame bufferhight and width and stores in those varibles both ints.
    	// Bufferwidth and height are the size of the drawable bit of windowi
    	
    	createCallBacks();
    	glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    	
    	glewExperimental = GL_TRUE; // allows extensions which you wont be using!

    	if (glewInit() != GLEW_OK)
    	{
        	cout << "GLEW became unstuck!" << endl;
        	glfwDestroyWindow(myWindow);
        	glfwTerminate();
        	exit (EXIT_FAILURE);
    	}
	glEnable(GL_DEPTH_TEST);
    	// how much of the window can we draw to. Not the total size but from 0,0 to bufferWidth, bufferHeight
    	glViewport(0, 0, bufferWidth, bufferHeight);  // this sets the top coordinates x and y to 0 and 0, then bottom right
    	
    	glfwSetWindowUserPointer(myWindow, this); // pass window in and the owner which is this class so we can use callbacks
}

void GLWindow::createCallBacks()
{
	glfwSetKeyCallback(myWindow, keyHandler); 
	glfwSetCursorPosCallback(myWindow, mouseHandler);
}

void GLWindow::keyHandler(GLFWwindow *window, int key, int code, int action, int mode)
{
	GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void GLWindow::mouseHandler(GLFWwindow *window, double xPos, double yPos)
{
	// grab the pointer to our window as this is a static function
	GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	if (theWindow->mousedFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mousedFirstMoved = false;
	}
	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;
	
	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
	
}

GLfloat GLWindow::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0;
	return theChange;
}

GLfloat GLWindow::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0;
	return theChange;
}

GLWindow::~GLWindow()
{
    glfwDestroyWindow(myWindow);
    glfwTerminate();
}

