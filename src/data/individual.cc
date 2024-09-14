#include "data/individual.hh"

using namespace fargo;

static unsigned long uid_counter = 0;

Individual::Individual() {
    this->data.uid = uid_counter++;
}

Individual::~Individual() {
    // Nothing to do here
}
