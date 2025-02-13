/*
// Sample demonstrating interoperability of OpenCV UMat with OpenGL texture.
// At first, the data obtained from video file or camera and placed onto
// OpenGL texture, following mapping of this OpenGL texture to OpenCV UMat
// and call cv::Blur function. The result is mapped back to OpenGL texture
// and rendered through OpenGL API.
*/
#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#elif defined(__linux__)
# include <X11/X.h>
# include <X11/Xlib.h>
#endif

#include <iostream>
#include <queue>
#include <string>

#include <stdio.h>

#include "opencv2/core.hpp"
#include "opencv2/core/opengl.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "winapp.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <CL/cl.h>

using namespace cv;
using namespace std;

// OpenGL texture for displaying frames
GLuint texture;
VideoCapture cap(0);

void initGL() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void processFrame(Mat &frame) {
    // Convert to grayscale
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    // Apply Gaussian blur
    GaussianBlur(gray, gray, Size(5, 5), 0);
    
    // Apply Canny edge detection
    Canny(gray, gray, 50, 150);
    
    // Convert back to BGR for OpenGL
    cvtColor(gray, frame, COLOR_GRAY2BGR);
}

void displayEnhanced() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    processFrame(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (!cap.isOpened()) {
        cerr << "Error opening camera!" << endl;
        return -1;
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Enhanced Video Frame");
    
    initGL();
    glutDisplayFunc(displayEnhanced);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <CL/cl.h>

using namespace cv;
using namespace std;

// OpenGL texture for displaying frames
GLuint texture;
VideoCapture cap(0);

void initGL() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void processFrame(Mat &frame) {
    // Convert to grayscale
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    // Apply Gaussian blur
    GaussianBlur(gray, gray, Size(5, 5), 0);
    
    // Apply Canny edge detection
    Canny(gray, gray, 50, 150);
    
    // Convert back to BGR for OpenGL
    cvtColor(gray, frame, COLOR_GRAY2BGR);
}

void displayEnhanced() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    processFrame(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (!cap.isOpened()) {
        cerr << "Error opening camera!" << endl;
        return -1;
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Enhanced Video Frame");
    
    initGL();
    glutDisplayFunc(displayEnhanced);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <CL/cl.h>

using namespace cv;
using namespace std;

// OpenGL texture for displaying frames
GLuint texture;
VideoCapture cap(0);

void initGL() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void processFrame(Mat &frame) {
    // Convert to grayscale
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    // Apply Gaussian blur
    GaussianBlur(gray, gray, Size(5, 5), 0);
    
    // Apply Canny edge detection
    Canny(gray, gray, 50, 150);
    
    // Convert back to BGR for OpenGL
    cvtColor(gray, frame, COLOR_GRAY2BGR);
}

void displayEnhanced() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    processFrame(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (!cap.isOpened()) {
        cerr << "Error opening camera!" << endl;
        return -1;
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Enhanced Video Frame");
    
    initGL();
    glutDisplayFunc(displayEnhanced);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <CL/cl.h>

using namespace cv;
using namespace std;

// OpenGL texture for displaying frames
GLuint texture;
VideoCapture cap(0);

void initGL() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void processFrame(Mat &frame) {
    // Convert to grayscale
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    // Apply Gaussian blur
    GaussianBlur(gray, gray, Size(5, 5), 0);
    
    // Apply Canny edge detection
    Canny(gray, gray, 50, 150);
    
    // Convert back to BGR for OpenGL
    cvtColor(gray, frame, COLOR_GRAY2BGR);
}

void displayEnhanced() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    processFrame(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (!cap.isOpened()) {
        cerr << "Error opening camera!" << endl;
        return -1;
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Enhanced Video Frame");
    
    initGL();
    glutDisplayFunc(displayEnhanced);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <CL/cl.h>

using namespace cv;
using namespace std;

// OpenGL texture for displaying frames
GLuint texture;
VideoCapture cap(0);

void initGL() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void processFrame(Mat &frame) {
    // Convert to grayscale
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    // Apply Gaussian blur
    GaussianBlur(gray, gray, Size(5, 5), 0);
    
    // Apply Canny edge detection
    Canny(gray, gray, 50, 150);
    
    // Convert back to BGR for OpenGL
    cvtColor(gray, frame, COLOR_GRAY2BGR);
}

void displayEnhanced() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    processFrame(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (!cap.isOpened()) {
        cerr << "Error opening camera!" << endl;
        return -1;
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Enhanced Video Frame");
    
    initGL();
    glutDisplayFunc(displayEnhanced);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
// OpenGL texture for displaying frames
GLuint texture;
VideoCapture cap(0);

void initGL() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void processFrame(Mat &frame) {
    // Convert to grayscale
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    // Apply Gaussian blur
    GaussianBlur(gray, gray, Size(5, 5), 0);
    
    // Apply Canny edge detection
    Canny(gray, gray, 50, 150);
    
    // Convert back to BGR for OpenGL
    cvtColor(gray, frame, COLOR_GRAY2BGR);
}

void displayEnhanced() {
    Mat frame;
    cap >> frame;
    if (frame.empty()) return;
    
    processFrame(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (!cap.isOpened()) {
        cerr << "Error opening camera!" << endl;
        return -1;
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Enhanced Video Frame");
    
    initGL();
    glutDisplayFunc(displayEnhanced);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

class GLWinApp : public WinApp
{
public:
    enum MODE
    {
        MODE_CPU = 0,
        MODE_GPU
    };

    GLWinApp(int width, int height, std::string& window_name, cv::VideoCapture& cap) :
        WinApp(width, height, window_name)
    {
        m_shutdown        = false;
        m_use_buffer      = false;
        m_demo_processing = true;
        m_mode            = MODE_CPU;
        m_modeStr[0]      = cv::String("Processing on CPU");
        m_modeStr[1]      = cv::String("Processing on GPU");
        m_cap             = cap;
    }

    ~GLWinApp() {}

    virtual void cleanup() CV_OVERRIDE
    {
        m_shutdown = true;
#if defined(__linux__)
        glXMakeCurrent(m_display, None, NULL);
        glXDestroyContext(m_display, m_glctx);
#endif
        WinApp::cleanup();
    }

#if defined(_WIN32)
    virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) CV_OVERRIDE
    {
        switch (message)
        {
        case WM_CHAR:
            if (wParam == '1')
            {
                set_mode(MODE_CPU);
                return EXIT_SUCCESS;
            }
            if (wParam == '2')
            {
                set_mode(MODE_GPU);
                return EXIT_SUCCESS;
            }
            else if (wParam == '9')
            {
                toggle_buffer();
                return EXIT_SUCCESS;
            }
            else if (wParam == VK_SPACE)
            {
                m_demo_processing = !m_demo_processing;
                return EXIT_SUCCESS;
            }
            else if (wParam == VK_ESCAPE)
            {
                cleanup();
                return EXIT_SUCCESS;
            }
            break;

        case WM_CLOSE:
            cleanup();
            return EXIT_SUCCESS;

        case WM_DESTROY:
            ::PostQuitMessage(0);
            return EXIT_SUCCESS;
        }

        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }
#endif

#if defined(__linux__)
    int handle_event(XEvent& e) CV_OVERRIDE
    {
        switch(e.type)
        {
        case ClientMessage:
            if ((Atom)e.xclient.data.l[0] == m_WM_DELETE_WINDOW)
            {
                m_end_loop = true;
                cleanup();
            }
            else
            {
                return EXIT_SUCCESS;
            }
            break;
        case Expose:
            render();
            break;
        case KeyPress:
            switch(keycode_to_keysym(e.xkey.keycode))
            {
            case XK_space:
                m_demo_processing = !m_demo_processing;
                break;
            case XK_1:
                set_mode(MODE_CPU);
                break;
            case XK_2:
                set_mode(MODE_GPU);
                break;
            case XK_9:
                toggle_buffer();
                break;
            case XK_Escape:
                m_end_loop = true;
                cleanup();
                break;
            }
            break;
        default:
            return EXIT_SUCCESS;
        }
        return 1;
    }
#endif

    int init() CV_OVERRIDE
    {
#if defined(_WIN32)
        m_hDC = GetDC(m_hWnd);

        if (setup_pixel_format() != 0)
        {
            std::cerr << "Can't setup pixel format" << std::endl;
            return EXIT_FAILURE;
        }

        m_hRC = wglCreateContext(m_hDC);
        wglMakeCurrent(m_hDC, m_hRC);
#elif defined(__linux__)
        m_glctx = glXCreateContext(m_display, m_visual_info, NULL, GL_TRUE);
        glXMakeCurrent(m_display, m_window, m_glctx);
#endif

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, m_width, m_height);

        if (cv::ocl::haveOpenCL())
        {
            (void) cv::ogl::ocl::initializeContextFromGL();
        }

        m_oclDevName = cv::ocl::useOpenCL() ?
            cv::ocl::Context::getDefault().device(0).name() :
            (char*) "No OpenCL device";

        return EXIT_SUCCESS;
    } // init()

    int get_frame(cv::ogl::Texture2D& texture, cv::ogl::Buffer& buffer, bool do_buffer)
    {
        if (!m_cap.read(m_frame_bgr))
            return EXIT_FAILURE;

        cv::cvtColor(m_frame_bgr, m_frame_rgba, cv::COLOR_RGB2RGBA);

        if (do_buffer)
            buffer.copyFrom(m_frame_rgba, cv::ogl::Buffer::PIXEL_UNPACK_BUFFER, true);
        else
            texture.copyFrom(m_frame_rgba, true);

        return EXIT_SUCCESS;
    }

    void print_info(MODE mode, double time, cv::String& oclDevName)
    {
#if defined(_WIN32)
        HDC hDC = m_hDC;

        HFONT hFont = (HFONT)::GetStockObject(SYSTEM_FONT);

        HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);

        if (hOldFont)
        {
            TEXTMETRIC tm;
            ::GetTextMetrics(hDC, &tm);

            char buf[256+1];
            int  y = 0;

            buf[0] = 0;
            snprintf(buf, sizeof(buf), "Mode: %s OpenGL %s", m_modeStr[mode].c_str(), use_buffer() ? "buffer" : "texture");
            ::TextOut(hDC, 0, y, buf, (int)strlen(buf));

            y += tm.tmHeight;
            buf[0] = 0;
            snprintf(buf, sizeof(buf), "Time, msec: %2.1f", time);
            ::TextOut(hDC, 0, y, buf, (int)strlen(buf));

            y += tm.tmHeight;
            buf[0] = 0;
            snprintf(buf, sizeof(buf), "OpenCL device: %s", oclDevName.c_str());
            ::TextOut(hDC, 0, y, buf, (int)strlen(buf));

            ::SelectObject(hDC, hOldFont);
        }
#elif defined(__linux__)

        char buf[256+1];
        snprintf(buf, sizeof(buf)-1, "Time, msec: %2.1f, Mode: %s OpenGL %s, Device: %s", time, m_modeStr[mode].c_str(), use_buffer() ? "buffer" : "texture", oclDevName.c_str());
        XStoreName(m_display, m_window, buf);
#endif
    }

    void idle() CV_OVERRIDE
    {
        render();
    }

    int render() CV_OVERRIDE
    {
        try
        {
            if (m_shutdown)
                return EXIT_SUCCESS;

            int r;
            cv::ogl::Texture2D texture;
            cv::ogl::Buffer buffer;

            texture.setAutoRelease(true);
            buffer.setAutoRelease(true);

            MODE mode = get_mode();
            bool do_buffer = use_buffer();

            r = get_frame(texture, buffer, do_buffer);
            if (r != 0)
            {
                return EXIT_FAILURE;
            }

            switch (mode)
            {
                case MODE_CPU: // process frame on CPU
                    processFrameCPU(texture, buffer, do_buffer);
                    break;

                case MODE_GPU: // process frame on GPU
                    processFrameGPU(texture, buffer, do_buffer);
                    break;
            } // switch

            if (do_buffer) // buffer -> texture
            {
                cv::Mat m(m_height, m_width, CV_8UC4);
                buffer.copyTo(m);
                texture.copyFrom(m, true);
            }

#if defined(__linux__)
            XWindowAttributes window_attributes;
            XGetWindowAttributes(m_display, m_window, &window_attributes);
            glViewport(0, 0, window_attributes.width, window_attributes.height);
#endif

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            glEnable(GL_TEXTURE_2D);

            texture.bind();

            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 0.1f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.1f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0.1f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 0.1f);
            glEnd();

#if defined(_WIN32)
            SwapBuffers(m_hDC);
#elif defined(__linux__)
            glXSwapBuffers(m_display, m_window);
#endif

            print_info(mode, m_timer.getTimeMilli(), m_oclDevName);
        }


        catch (const cv::Exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            return 10;
        }

        return EXIT_SUCCESS;
    }

protected:

    void processFrameCPU(cv::ogl::Texture2D& texture, cv::ogl::Buffer& buffer, bool do_buffer)
    {
        cv::Mat m(m_height, m_width, CV_8UC4);

        m_timer.reset();
        m_timer.start();

        if (do_buffer)
            buffer.copyTo(m);
        else
            texture.copyTo(m);

        if (m_demo_processing)
        {
            // blur texture image with OpenCV on CPU
            cv::blur(m, m, cv::Size(15, 15));
        }

        if (do_buffer)
            buffer.copyFrom(m, cv::ogl::Buffer::PIXEL_UNPACK_BUFFER, true);
        else
            texture.copyFrom(m, true);

        m_timer.stop();
    }

    void processFrameGPU(cv::ogl::Texture2D& texture, cv::ogl::Buffer& buffer, bool do_buffer)
    {
        cv::UMat u;

        m_timer.reset();
        m_timer.start();

        if (do_buffer)
            u = cv::ogl::mapGLBuffer(buffer);
        else
            cv::ogl::convertFromGLTexture2D(texture, u);

        if (m_demo_processing)
        {
            // blur texture image with OpenCV on GPU with OpenCL
            cv::blur(u, u, cv::Size(15, 15));
        }

        if (do_buffer)
            cv::ogl::unmapGLBuffer(u);
        else
            cv::ogl::convertToGLTexture2D(u, texture);

        m_timer.stop();
    }

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// تطبيق مجموعة من التأثيرات على الصورة
void applyEffects(Mat& img)
{
    Mat gray, edges, blurred, sharpened;
    
    // تحويل الصورة إلى التدرج الرمادي
    cvtColor(img, gray, COLOR_BGR2GRAY);
    
    // تطبيق كشف الحواف
    Canny(gray, edges, 50, 150);
    
    // تطبيق تمويه Gaussian
    GaussianBlur(img, blurred, Size(15, 15), 0);
    
    // تطبيق زيادة الحدة
    Mat kernel = (Mat_<float>(3, 3) << 
                   -1, -1, -1, 
                   -1, 9, -1, 
                   -1, -1, -1);
    filter2D(img, sharpened, img.depth(), kernel);
    
    // دمج الصور في نافذة واحدة للعرض
    Mat combined;
    hconcat(img, blurred, combined);
    hconcat(combined, sharpened, combined);
    
    // عرض النتائج
    imshow("Image Effects", combined);
}

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Error: Cannot open webcam" << endl;
        return -1;
    }
    
    Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;
        
        applyEffects(frame);
        
        if (waitKey(30) == 27) // خروج عند الضغط على ESC
            break;
    }
    
    cap.release();
    destroyAllWindows();
    return 0;
}
#include "opencv2/opencv.hpp"
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

void displayFPS(VideoCapture& cap)
{
    int frameCount = 0;
    auto start = high_resolution_clock::now();
    Mat frame;
    
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;
        
        frameCount++;
        
        // حساب الزمن المنقضي
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        
        if (elapsed.count() >= 1.0) // تحديث الـ FPS كل ثانية
        {
            int fps = frameCount / elapsed.count();
            string fpsText = "FPS: " + to_string(fps);
            putText(frame, fpsText, Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
            frameCount = 0;
            start = high_resolution_clock::now();
        }
        
        imshow("Video FPS", frame);
        
        if (waitKey(30) == 27)
            break;
    }
}

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Error: Cannot open webcam" << endl;
        return -1;
    }
    
    displayFPS(cap);
    
    cap.release();
    destroyAllWindows();
    return 0;
}

#if defined(_WIN32)
    int setup_pixel_format()
    {
        PIXELFORMATDESCRIPTOR  pfd;

        pfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion        = 1;
        pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL  | PFD_DOUBLEBUFFER;
        pfd.iPixelType      = PFD_TYPE_RGBA;
        pfd.cColorBits      = 24;
        pfd.cRedBits        = 8;
        pfd.cRedShift       = 0;
        pfd.cGreenBits      = 8;
        pfd.cGreenShift     = 0;
        pfd.cBlueBits       = 8;
        pfd.cBlueShift      = 0;
        pfd.cAlphaBits      = 8;
        pfd.cAlphaShift     = 0;
        pfd.cAccumBits      = 0;
        pfd.cAccumRedBits   = 0;
        pfd.cAccumGreenBits = 0;
        pfd.cAccumBlueBits  = 0;
        pfd.cAccumAlphaBits = 0;
        pfd.cDepthBits      = 24;
        pfd.cStencilBits    = 8;
        pfd.cAuxBuffers     = 0;
        pfd.iLayerType      = PFD_MAIN_PLANE;
        pfd.bReserved       = 0;
        pfd.dwLayerMask     = 0;
        pfd.dwVisibleMask   = 0;
        pfd.dwDamageMask    = 0;

        int pfmt = ChoosePixelFormat(m_hDC, &pfd);
        if (pfmt == 0)
            return EXIT_FAILURE;

        if (SetPixelFormat(m_hDC, pfmt, &pfd) == 0)
            return -2;

        return EXIT_SUCCESS;
    }
#endif

#if defined(__linux__)
    KeySym keycode_to_keysym(unsigned keycode)
    {   // note that XKeycodeToKeysym() is considered deprecated
        int keysyms_per_keycode_return = 0;
        KeySym *keysyms = XGetKeyboardMapping(m_display, keycode, 1, &keysyms_per_keycode_return);
        KeySym keysym = keysyms[0];
        XFree(keysyms);
        return keysym;
    }
#endif

    bool use_buffer()        { return m_use_buffer; }
    void toggle_buffer()     { m_use_buffer = !m_use_buffer; }
    MODE get_mode()          { return m_mode; }
    void set_mode(MODE mode) { m_mode = mode; }

private:
    bool               m_shutdown;
    bool               m_use_buffer;
    bool               m_demo_processing;
    MODE               m_mode;
    cv::String         m_modeStr[2];
#if defined(_WIN32)
    HDC                m_hDC;
    HGLRC              m_hRC;
#elif defined(__linux__)
    GLXContext         m_glctx;
#endif
    cv::VideoCapture   m_cap;
    cv::Mat            m_frame_bgr;
    cv::Mat            m_frame_rgba;
    cv::String         m_oclDevName;
};

static const char* keys =
{
    "{c camera | 0     | camera id }"
    "{f file   |       | movie file name  }"
};

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv, keys);
    int    camera_id = parser.get<int>("camera");
    string file      = parser.get<string>("file");

    parser.about(
        "\nA sample program demonstrating interoperability of OpenGL and OpenCL with OpenCV.\n\n"
        "Hot keys: \n"
        "  SPACE - turn processing on/off\n"
        "    1   - process GL data through OpenCV on CPU\n"
        "    2   - process GL data through OpenCV on GPU (via OpenCL)\n"
        "    9   - toggle use of GL texture/GL buffer\n"
        "   ESC  - exit\n\n");

    parser.printMessage();

    cv::VideoCapture cap;

    if (file.empty())
        cap.open(camera_id);
    else
        cap.open(file.c_str());

    if (!cap.isOpened())
    {
        printf("can not open camera or video file\n");
        return EXIT_FAILURE;
    }

    int width  = (int)cap.get(CAP_PROP_FRAME_WIDTH);
    int height = (int)cap.get(CAP_PROP_FRAME_HEIGHT);

#if defined(_WIN32)
    string wndname = "WGL Window";
#elif defined(__linux__)
    string wndname = "GLX Window";
#endif

    GLWinApp app(width, height, wndname, cap);

    try
    {
        app.create();
        return app.run();
    }
    catch (const cv::Exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 10;
    }
    catch (...)
    {
        cerr << "FATAL ERROR: Unknown exception" << endl;
        return 11;
    }
}
