#pragma once
#include "response.hh"
#include <string>
#include <memory>
#include <vector>

namespace fargo {

    class FontReference {

    public:
        FontReference();
        ~FontReference();
        static Response<FontReference> load_font(const std::string& file_path);
        inline const unsigned char* get_font_data() const { return this->font_data.get()->data(); }
        static inline FontReference null() { return FontReference(); }

    private:
        std::string     file_path;
        std::shared_ptr<std::vector<unsigned char>> font_data;
    };
}
