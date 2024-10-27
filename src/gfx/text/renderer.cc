#include "gfx/text/renderer.hh"
#include <ssfn2/ssfn.h>

using namespace fargo;

ssfn_t ssfn_ctx;
ssfn_buf_t ssfn_buf;

TextRenderer::TextRenderer() {
    font = FontReference::null();
    framebuffer = nullptr;
    framebuffer_width = 0;
    framebuffer_height = 0;
    font_width = 0;
    font_height = 0;
    text_width = 0;
    text_height = 0;
    ssfn_ctx = { 0 };
    ssfn_buf = { 0 };
}

TextRenderer::~TextRenderer() {
    this->unregister_font();
    this->unregister_framebuffer();
}

Response<void> TextRenderer::register_framebuffer(unsigned int* buffer, const unsigned int width, const unsigned int height) {
    if (buffer == nullptr) {
        return Response<void>(Status::ERROR_MISUSE);
    }

    if (width == 0 || height == 0) {
        return Response<void>(Status::ERROR_MISUSE);
    }

    this->framebuffer = buffer;
    this->framebuffer_width = width;
    this->framebuffer_height = height;
    this->font_width = 8; // hardcoded for now
    this->font_height = 16; // hardcoded for now
    this->text_width = width / this->font_width;
    this->text_height = height / this->font_height;

    ssfn_buf = {
        .ptr = (uint8_t *)buffer,
        .w = (int)width,
        .h = (int)height,
        .p = (unsigned short)(width * sizeof(unsigned int)),
        .x = 0,
        .y = 0,
        .fg = 0xFF808080 // hardcoded for now
    };

    return Responses::flawless();
}

Response<void> TextRenderer::unregister_framebuffer() {
    this->framebuffer = nullptr;
    this->framebuffer_width = 0;
    this->framebuffer_height = 0;

    return Responses::flawless();
}

Response<void> TextRenderer::register_font(const std::string& font_file_name) {
    Response<FontReference> font_response = FontReference::load_font(font_file_name);
    if (font_response.status != Status::FLAWLESS) {
        return Response<void>(font_response.status);
    }

    this->font = font_response.result;

    ssfn_load(&ssfn_ctx, font.get_font_data());
    ssfn_select(&ssfn_ctx, SSFN_FAMILY_ANY, nullptr, SSFN_STYLE_REGULAR, 128);

    return Responses::flawless();
}

Response<void> TextRenderer::unregister_font() {
    this->font = FontReference::null();

    ssfn_free(&ssfn_ctx);

    return Responses::flawless();
}

Response<void> TextRenderer::render_putc(const char character, const unsigned int pos_x, const unsigned int pos_y) {
    if (this->framebuffer == nullptr) {
        return Response<void>(Status::ERROR_MISUSE);
    }

    if (this->font.get_font_data() == nullptr) {
        return Response<void>(Status::ERROR_MISUSE);
    }

    if (pos_x >= this->text_width || pos_y >= this->text_height) {
        return Response<void>(Status::ERROR_MISUSE);
    }

    char text[2] = { character, '\0' };

    ssfn_render(&ssfn_ctx, &ssfn_buf, text);

    return Responses::flawless();
}
