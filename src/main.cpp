#include <iostream>
// #include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void error_callback(int error, const char* description)
{
    cerr << "Error: " << description << endl;
}

int main(void){

    if(glfwInit() == GL_FALSE)
    {
        /*
            After this call, you must initialize GLFW again 
            before using any GLFW functions that require it.
        */
        glfwTerminate();
        return 1;
    }    
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    
    if(window == NULL)
    {
        // Window or OpenGL context creation failed
        cerr << "Can't create GLFW window." << endl;
        glfwTerminate();
        return 1;
    }
    
    // ウィンドウをOpenGLの処理対象にする
    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    // GLenum err = glewInit();
    // if (GLEW_OK != err){
    //     // Problem: glewInit failed, something is seriously wrong.
    //     cerr << "Error: " << glewGetErrorString(err) << endl;
    //     return 1;
    // }

    while(glfwWindowShouldClose(window) == GL_FALSE){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}