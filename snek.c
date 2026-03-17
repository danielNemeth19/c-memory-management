#include "snek.h"

unsigned long size_of_addr(long long i){
    unsigned long sizeof_snek_version = sizeof(&i);
    return sizeof_snek_version;
}
