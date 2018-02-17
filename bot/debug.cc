#include "debug.h"

Bug * bugSingleton;

Bug & getDebugger() {
    if (bugSingleton) {
        return *bugSingleton;
    } else {
        bugSingleton = new Bug();
        bugSingleton->open("debug.log");
        return *bugSingleton;
    }
}