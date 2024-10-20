#include "gfx/visualizer.hh"
#include "constants.hh"
#include <minifb/minifb.h>

using namespace fargo;

Visualizer::Visualizer() 
{
    this->window = nullptr;
    this->buffer = nullptr;
    this->title = "Untitled";
}

Visualizer::~Visualizer() 
{
    this->destroy_data();
}

void Visualizer::destroy_data()
{
    if (this->window != nullptr) {
        mfb_close((struct mfb_window *)this->window);
    }

    if (this->buffer != nullptr) {
        delete[] this->buffer;
    }

    this->window = nullptr;
    this->buffer = nullptr;
}

Response<void> Visualizer::reset_mfb()
{
    this->destroy_data();

    struct mfb_window* mfb_window = nullptr;
    mfb_window = mfb_open_ex(this->title.c_str(), DISPLAY_SIZE_X, DISPLAY_SIZE_Y, DISPLAY_MFB_FLAGS);
    if (mfb_window == nullptr) {
        return Response<void>(Status::ERROR_FAILED_INIT);
    }

    this->buffer = new unsigned int[DISPLAY_SIZE_X * DISPLAY_SIZE_Y];
    if (this->buffer == nullptr) {
        return Response<void>(Status::ERROR_MISALLOCATION);
    }

    return Responses::flawless();
}

Response<void> Visualizer::update_mfb()
{
    mfb_wait_sync((struct mfb_window *)this->window);
    int mfb_status = mfb_update_ex((struct mfb_window *)this->window, (void *)this->buffer, DISPLAY_SIZE_X, DISPLAY_SIZE_Y);
    if (mfb_status < 0) {
        return Response<void>(Status::ERROR_UNKNOWN);
    }
    else {
        return Responses::flawless();
    }
}

// VISUALIZER_SHOULD_WORK determines if public methods will operate

Response<void> Visualizer::reset(const std::string& window_title)
{
    Status current_status = Status::FLAWLESS;

    this->title = window_title;

    if (!VISUALIZER_SHOULD_WORK) {
        return Responses::quiet_failure();
    }

    current_status = this->reset_mfb().status;

    return Response<void>(current_status);
}

Response<void> Visualizer::update_with(const PopulationData& pop_data)
{
    if (!VISUALIZER_SHOULD_WORK) {
        return Responses::quiet_failure();
    }

    Status current_status = Status::FLAWLESS;

    current_status = this->update_mfb().status;

    return current_status;
}

Response<void> Visualizer::cancel()
{
    if (!VISUALIZER_SHOULD_WORK) {
        return Responses::quiet_failure();
    }

    mfb_close((struct mfb_window *)this->window);
    this->destroy_data();

    return Responses::flawless();
}
