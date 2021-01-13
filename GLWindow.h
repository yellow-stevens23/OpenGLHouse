#ifndef GLWINDOW_H
#define GLWINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class GLWindow
{
    public:
        GLWindow(GLint width = 800, GLint height = 600,  char *windowTitle = "Test Window");
        void openFullscreen();
        void init();
        void openWindow();
        bool getShouldClose();
        bool* getKeys() { return keys; }
        GLfloat getXChange();
        GLfloat getYChange();
        void pollEvents();
        void setColour();
        void swapBuffers();
        ~GLWindow();


    private:
    	void setup();
    	void createCallBacks();
    	static void keyHandler(GLFWwindow *window, int key, int code, int action, int mode);
    	static void mouseHandler(GLFWwindow *window, double xPos, double yPos);
        GLFWwindow *myWindow;
        char *m_windowName;
        GLint m_width;
        GLint m_height;
        int bufferWidth, bufferHeight;
        bool keys[1024];
        GLfloat lastX;
        GLfloat lastY;
        GLfloat xChange;
        GLfloat yChange;
        bool mousedFirstMoved;
};

#endif // GLWINDOW_H

