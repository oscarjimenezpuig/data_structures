#include "value.h"

int val_cpy(void* d,void* o,uchar sv) {
    if(d && o && sv) {
        uchar* po=o;
        uchar* pd=d;
        while(po!=o+sv) {
            *pd++=*po++;
        }
        return 1;
    }
    return 0;
}

