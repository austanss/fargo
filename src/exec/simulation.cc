#include "constants.hh"
#include "exec/simulation.hh"
#include <iostream>
#include <minifb/minifb.h>

using namespace fargo;

SimulationHandle::SimulationHandle(const std::string &name) : moniker(name) {
    fresh = true;
    displayed = false;
    context = nullptr;
}

SimulationHandle::~SimulationHandle() {
    // Nothing to do here
}

void SimulationHandle::reset(bool should_display) {
    if (displayed) {
        this->display_destroy();
    }
    displayed = should_display;
    if (should_display) {
        this->display_create();
    }

    if (!!context) {
        context.release();
    }
    context = std::make_unique<SimulationContext>();
    context->population_refresh(420);

    fresh = false;
}

// Ticks one day
void SimulationHandle::tick() {
    if (fresh) {
        throw new std::runtime_error("Simulation not initialized");
    }

    this->data_update();

    if (displayed) {
        this->display_update();
    }
}

bool SimulationHandle::is_valid() {
    return !!window && !!buffer;
}

void SimulationHandle::display_create() {
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

void SimulationHandle::display_destroy() {
    if (window && displayed) {
        mfb_close((struct mfb_window *)this->window);
        this->window = nullptr;
        delete[] this->buffer;
    }
}

extern void redraw(uint32_t *buffer);
void SimulationHandle::display_update() {
    if (!displayed)
        throw new std::runtime_error("Simulation not displayable yet attempted update");
    
    int state = mfb_update_ex((struct mfb_window *)window, buffer, DISPLAY_SIZE_X, DISPLAY_SIZE_Y);
    if (state < 0) {
        mfb_close((struct mfb_window *)window);
        window = nullptr;
    }

    redraw(buffer);
    
    mfb_wait_sync((struct mfb_window *)window);
}

void SimulationHandle::data_update() {
    // Placeholder for now
}
