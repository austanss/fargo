#include <iostream>
#include <minifb/minifb.h>
#include "exec/simulation.hh"

static constexpr uint32_t DISPLAY_SIZE_X = 800;
static constexpr uint32_t DISPLAY_SIZE_Y = 600;
static constexpr uint32_t DISPLAY_FLAGS = 0x00;

using namespace fargo;

Simulation::Simulation(const std::string &name) : moniker(name) {
    fresh = true;
    displayed = false;
}

Simulation::~Simulation() {
    // Nothing to do here
}

void Simulation::reset(bool should_display) {
    if (displayed) {
        this->display_destroy();
    }
    displayed = should_display;
    if (should_display) {
        this->display_create();
    }
    fresh = false;
}

void Simulation::tick() {
    if (fresh) {
        throw new std::runtime_error("Simulation not initialized");
    }

    if (displayed) {
        this->display_update();
    }
}

bool Simulation::is_valid() {
    return !!window && !!buffer;
}

void Simulation::display_create() {
    std::string title = "Fargo - " + this->moniker;
    struct mfb_window *m_window = mfb_open_ex(title.c_str(), DISPLAY_SIZE_X, DISPLAY_SIZE_Y, DISPLAY_FLAGS);
    if (!m_window) {
        throw new std::runtime_error("Failed to create window for simulation");
    }

    this->buffer = new unsigned int[DISPLAY_SIZE_X * DISPLAY_SIZE_Y];
    if (!this->buffer) {
        mfb_close(m_window);
        throw new std::runtime_error("Failed to allocate buffer for simulation");
    }

    this->window = (void *)m_window;
}

void Simulation::display_destroy() {
    if (window && displayed) {
        mfb_close((struct mfb_window *)this->window);
        this->window = nullptr;
        delete[] this->buffer;
    }
}

void Simulation::display_update() {
    if (window && displayed) {
        int state = mfb_update_ex((struct mfb_window *)window, buffer, DISPLAY_SIZE_X, DISPLAY_SIZE_Y);
        if (state < 0) {
            mfb_close((struct mfb_window *)window);
            window = nullptr;
        }
    }
}
