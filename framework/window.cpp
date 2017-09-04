// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Window
// -----------------------------------------------------------------------------

#include "window.hpp"
#include <cstring>
#include <iostream>
#include <sstream>

Window::Window(glm::ivec2 const &windowsize) : m_window(nullptr), m_size(windowsize), m_title("AnSciVis"), m_mousePosition(), m_mouseButtonFlags(0), m_keypressed()
{
    std::fill(std::begin(m_keypressed), std::end(m_keypressed), false);

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    m_window = SDL_CreateWindow(m_title.c_str(), 0, 0, windowsize.x, windowsize.y, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if(m_window)
    {
        assert(m_window != nullptr);
        SDL_SetWindowData(m_window, WIN_DATA, this);
        m_glcontext = SDL_GL_CreateContext(m_window);

        //        printf("%s\n", SDL_GetError());

        //        gl3wInit();
        glewExperimental = GL_TRUE;
        glewInit();
        //         glGetError();

        const GLubyte *renderer = glGetString(GL_RENDERER);
        const GLubyte *vendor = glGetString(GL_VENDOR);
        const GLubyte *version = glGetString(GL_VERSION);
        const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

        std::stringstream ss;
        ss << "\n-------------------------------------------------------------\n";
        ss << "GL Vendor    : " << vendor;
        ss << "\nGL GLRenderer : " << renderer;
        ss << "\nGL Version   : " << version;
        ss << "\nGLSL Version : " << glslVersion;
        ss << "\n-------------------------------------------------------------\n";
        printf("%s", ss.str().c_str());

        //        glEnable(GL_ALPHA_TEST);
        //        glAlphaFunc(GL_NOTEQUAL, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //        glEnable(GL_POINT_SMOOTH);
        //        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        //        glPointSize(5.0f);
        //        glEnable(GL_POINT_SMOOTH);

        glLineWidth(2.0f);
//        glEnable(GL_LINE_SMOOTH);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
    }
}

Window::~Window()
{
    if(m_window)
    {
        SDL_GL_DeleteContext(m_glcontext);
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}

void Window::cursorPositionCallback(SDL_Window *win, double x, double y)
{
    Window *w = reinterpret_cast<Window *>(SDL_GetWindowData(win, WIN_DATA));
    assert(w);

    w->m_mousePosition = glm::ivec2(x, y);
}

void Window::mouseButtonCallback(SDL_Window *win, int button, int act, int mods)
{
    Window *w = reinterpret_cast<Window *>(SDL_GetWindowData(win, WIN_DATA));
    assert(w);

    if(SDL_PRESSED == act)
    {
        switch(button)
        {
        case SDL_BUTTON_LEFT:
            w->m_mouseButtonFlags |= Window::MOUSE_BUTTON_LEFT;
            break;
        case SDL_BUTTON_MIDDLE:
            w->m_mouseButtonFlags |= Window::MOUSE_BUTTON_MIDDLE;
            break;
        case SDL_BUTTON_RIGHT:
            w->m_mouseButtonFlags |= Window::MOUSE_BUTTON_RIGHT;
            break;
        default:
            break;
        }
    }
    else if(act == SDL_RELEASED)
    {
        switch(button)
        {
        case SDL_BUTTON_LEFT:
            w->m_mouseButtonFlags &= ~Window::MOUSE_BUTTON_LEFT;
            break;
        case SDL_BUTTON_MIDDLE:
            w->m_mouseButtonFlags &= ~Window::MOUSE_BUTTON_MIDDLE;
            break;
        case SDL_BUTTON_RIGHT:
            w->m_mouseButtonFlags &= ~Window::MOUSE_BUTTON_RIGHT;
            break;
        default:
            break;
        }
    }
}

void Window::keyCallback(SDL_Window *win, int key, int scancode, int act, int mods)
{
    Window *w = reinterpret_cast<Window *>(SDL_GetWindowData(win, WIN_DATA));
    assert(w);
    w->m_keypressed[key] = act == SDL_PRESSED;
}

glm::vec2 Window::mousePosition() const { return glm::vec2(m_mousePosition.x / float(m_size.x), 1.0f - m_mousePosition.y / float(m_size.y)); }
void Window::stop() { this->shouldClose = true; }
void Window::update() { SDL_GL_SwapWindow(m_window); }
glm::ivec2 Window::windowSize() const
{
    glm::ivec2 size(0);
    SDL_GetWindowSize(m_window, &size.x, &size.y);
    return size;
}

void Window::drawLine(glm::vec2 const &start, glm::vec2 const &end, Color const &col) const
{
    glColor3f(GLfloat(col.r_) / 255.0f, GLfloat(col.g_) / 255.0f, GLfloat(col.b_) / 255.0f);
    glBegin(GL_LINES);
    {
        glVertex2f(GLfloat(start.x), GLfloat(start.y));
        glVertex2f(GLfloat(end.x), GLfloat(end.y));
    }
    glEnd();
}

void Window::drawLine(float startX, float startY, float endX, float endY, float r, float g, float b) const { drawLine(glm::vec2(startX, startY), glm::vec2(endX, endY), Color(r, g, b)); }
void Window::drawPoint(glm::vec2 const &p, Color const &col) const
{
    glColor3f(GLfloat(col.r_) / 255.0f, GLfloat(col.g_) / 255.0f, GLfloat(col.b_) / 255.0f);
    glBegin(GL_POINTS);
    glVertex2f(GLfloat(p.x), GLfloat(p.y));
    glEnd();
}

void Window::drawPoint(float x, float y, float r, float g, float b) const { drawPoint(glm::vec2(x, y), Color(r, g, b)); }
float Window::getTime() const { return float(SDL_GetTicks()); }
void Window::resize(glm::ivec2 const &windowsize) { SDL_SetWindowSize(m_window, windowsize.x, windowsize.y); }
