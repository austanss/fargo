#include "gfx/text/renderer.hh"

using namespace fargo;

TextRenderer::TextRenderer() {
    font = FontReference::null();
    framebuffer = nullptr;
    framebuffer_width = 0;
    framebuffer_height = 0;
    font_width = 0;
    font_height = 0;
    text_width = 0;
    text_height = 0;
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

    return Responses::flawless();
}

Response<void> TextRenderer::unregister_font() {
    this->font = FontReference::null();

    return Responses::flawless();
}
