#pragma once
#include "exec/response.hh"
#include <string>

namespace fargo 
{

    // Interacts with C-style library minifb
    class Visualizer
    {
    
    public:
        Visualizer();
        ~Visualizer();

        Response<void> reset(const std::string& window_title);
        Response<void> update();
        Response<void> cancel();

    private:
        void* window;
        unsigned int* buffer;
        std::string title;
        void destroy_data();
        Response<void> reset_mfb();
        Response<void> update_mfb();

    };

}