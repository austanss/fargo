#include <iostream>
#include <minifb/minifb.h>

int main() {
    struct mfb_window *window = mfb_open_ex("fargo", 800, 600, 0x00);
    if (!window)
        return 0;

    uint32_t *buffer = (uint32_t *)malloc(800 * 600 * 4);

    do {
        int state;

        state = mfb_update_ex(window, buffer, 800, 600);

        if (state < 0) {
            window = nullptr;
            break;
        }
    } while(mfb_wait_sync(window));
}
