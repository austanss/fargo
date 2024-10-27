#pragma once
#include "response.hh"
#include "gfx/text/fontref.hh"

namespace fargo
{
    // Does not handle full TTY logic, only text rendering
    // Does not track the cursor or any text rendered
    // Does not handle text wrapping
    // Will cut off strings that necessitate newlines
    // Will not handle escape sequences
    class TextRenderer
    {

    public:
        // Default constructor, must register a font and framebuffer
        TextRenderer();
        // Automatically unregisters the framebuffer and destroys font data
        ~TextRenderer();
        Response<void> register_font(const std::string& font_file_name);
        // Will destroy the font data
        Response<void> unregister_font();
        Response<void> register_framebuffer(unsigned int* buffer, const unsigned int width, const unsigned int height);
        // Does not free the framebuffer, simply forgets it
        Response<void> unregister_framebuffer();
        // Position is in characters, not pixels
        Response<void> render_putc(const char character, const unsigned int pos_x, const unsigned int pos_y);
        // Position is in characters, not pixels
        Response<void> render_puts(const std::string& text, const unsigned int pos_x, const unsigned int pos_y);

    private:
        FontReference font;
        unsigned int* framebuffer;
        unsigned int framebuffer_width;
        unsigned int framebuffer_height;
        unsigned int font_width;
        unsigned int font_height;
        unsigned int text_width;
        unsigned int text_height;

    };
}
