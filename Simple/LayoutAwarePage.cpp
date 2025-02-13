#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace cv;
using namespace std;

const int WIDTH = 640, HEIGHT = 480;
GLFWwindow* window;
GLuint texture;
Mat frame;
VideoCapture cap(0);
bool useGPU = false;

void initGL() {
    if (!glfwInit()) exit(EXIT_FAILURE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenCV + OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void processFrame() {
    cap >> frame;
    if (frame.empty()) return;
    if (useGPU && ocl::useOpenCL()) {
        UMat uFrame;
        frame.copyTo(uFrame);
        cvtColor(uFrame, uFrame, COLOR_BGR2BGRA);
        uFrame.copyTo(frame);
    } else {
        cvtColor(frame, frame, COLOR_BGR2BGRA);
    }
}

void updateTexture() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame.cols, frame.rows, 0, GL_BGRA, GL_UNSIGNED_BYTE, frame.data);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(-1, -1);
    glTexCoord2f(1, 1); glVertex2f(1, -1);
    glTexCoord2f(1, 0); glVertex2f(1, 1);
    glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    glfwSwapBuffers(window);
}

void cleanup() {
    cap.release();
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    initGL();
    while (!glfwWindowShouldClose(window)) {
        processFrame();
        updateTexture();
        render();
        glfwPollEvents();
    }
    cleanup();
    return 0;
}
