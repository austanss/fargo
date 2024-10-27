#pragma once
#include "response.hh"
#include <string>

namespace fargo {

    class FontReference {

    public:
        ~FontReference();
        static Response<FontReference> load_font(const std::string& file_path);

    private:
        FontReference();
        std::string     file_path;
        unsigned char*  font_data;
    };
}
