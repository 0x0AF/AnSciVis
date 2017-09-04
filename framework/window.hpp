#ifndef FENSTERCHEN_WINDOW_HPP
#define FENSTERCHEN_WINDOW_HPP

// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Window
// -----------------------------------------------------------------------------

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

#include "color.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS
//#include <glm/gtx/multiple.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <array>
#include <string>

#include <imgui_impl_sdl_gl3.h>

class Window
{
  public:
    Window(glm::ivec2 const &windowsize = glm::ivec2(320, 240));
    ~Window();

    enum MouseButton
    {
        MOUSE_BUTTON_NONE = 0,
        MOUSE_BUTTON_LEFT = (1 << 0),
        MOUSE_BUTTON_RIGHT = (1 << 1),
        MOUSE_BUTTON_MIDDLE = (1 << 2)
    };

    void drawLine(glm::vec2 const &start, glm::vec2 const &end, Color const &color) const;

    void drawLine(float startX, float startY, float endX, float endY, float r, float g, float b) const;

    void drawPoint(glm::vec2 const &p, Color const &col) const;

    void drawPoint(float x, float y, float r, float g, float b) const;

    glm::vec2 mousePosition() const;

    bool shouldClose = false;
    void stop();
    void update();
    inline bool isKeyPressed(int key) const { return m_keypressed[key]; }
    inline bool isButtonPressed(MouseButton b) const { return 0 != (m_mouseButtonFlags & b); }
    glm::ivec2 windowSize() const;
    float getTime() const;

    SDL_Window *getSDLwindow() { return m_window; }
    void resize(glm::ivec2 const &windowsize = glm::ivec2(640, 480));

    static void cursorPositionCallback(SDL_Window *win, double x, double y);
    static void mouseButtonCallback(SDL_Window *win, int button, int action, int mods);
    static void keyCallback(SDL_Window *win, int key, int scancode, int action, int mods);

  private:
    SDL_Window *m_window;
    SDL_GLContext m_glcontext;
    glm::ivec2 m_size;
    std::string const m_title;
    glm::vec2 m_mousePosition;

    int m_mouseButtonFlags;
    std::array<bool, 512> m_keypressed;
    static constexpr char *WIN_DATA = (char *const) "m_data";
};

#endif // define FENSTERCHEN_WINDOW_HPP
