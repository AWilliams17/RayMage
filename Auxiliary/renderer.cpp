//
// Created by awilliams on 7/27/18.
//

#include "renderer.h"

namespace renderer {
    /**
     * Initializes the SDL_WINDOW and SDL_RENDERER instances passed with the supplied arguments. Returns NULL on success,
     * otherwise returns the result of SDL_GetError().
     * @param[out] window The SDL_Window instance to be initialized.
     * @param[out] renderer The SDL_Renderer instance to be initialized.
     * @param[in] WIDTH The width of the window be created.
     * @param[in] HEIGHT The height of the window to be created.
     * @param[in] FULL_SCREEN If true, the resulting window be full screen. Otherwise, it will be set to the widthXheight.
     * @param[in] WINDOW_TITLE The title for the window to use.
     */
    string init(SDL_Window *window, SDL_Renderer *renderer,
                const int WIDTH, const int HEIGHT, const bool FULL_SCREEN, const string WINDOW_TITLE) {

    }

    /// Destroys the window and renderer.
    /// \param window The window to be destroyed.
    /// \param renderer The renderer to be destroyed.
    void terminate(SDL_Window *window, SDL_Renderer *renderer) {

    }

    /// Blacks out the renderer.
    /// \param[in,out] renderer The renderer instance to be cleared.
    void clear_screen(SDL_Renderer *renderer) {

    }

    /// Redraw the renderer.
    /// \param renderer the renderer instance to be redrawn.
    void redraw(SDL_Renderer *renderer) {

    };
}
