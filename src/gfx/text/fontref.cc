#include "gfx/text/fontref.hh"
#include <filesystem>
#include <fstream>

using namespace fargo;

FontReference::FontReference() {
    font_data = nullptr;
    file_path = "";
}

FontReference::~FontReference() {
    // Hay nada que hacer
}

Response<FontReference> FontReference::load_font(const std::string& file_name) {
    // Load the font data from the file path
    FontReference font_return = FontReference();
    font_return.file_path = file_name;

    std::filesystem::path font_fs_path = std::filesystem::path(file_name);
    unsigned long font_size = std::filesystem::file_size(font_fs_path); // Check if the file exists and find size
    if (font_size == 0) {
        return Response<FontReference>(Status::ERROR_FILE_404, font_return);
    }

    font_size = (font_size / 0x1000 + 1) * 0x1000; // Align the font size to the nearest 4KB boundary
    font_return.font_data = std::make_shared<std::vector<unsigned char>>(font_size); // Allocate memory for the font data
    
    if (font_return.font_data == nullptr) {
        return Response<FontReference>(Status::ERROR_MISALLOCATION, font_return);
    }

    std::ifstream font_in = std::ifstream(font_fs_path, std::ios::in | std::ios::binary);
    font_in.read((char*)font_return.get_font_data(), 0); // Read the font data from the file
    font_in.close();

    return Response<FontReference>(Status::FLAWLESS, font_return);
}
