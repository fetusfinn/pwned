/*      pwnedhook v2
 *
 *  todo :  write todo list
 *          list features
 *              offscreen
 *          move all structs and enums to their headers
 *          https://www.unknowncheats.me/forum/counterstrike-global-offensive/330483-disable-model-occulusion.html
 *          menu : label, header, ect
 *
 *
 */
#include "common/hooker.h"

/*
 *  entry point
 */
int __attribute((constructor)) entry()
{
    cheat_init();
    
    cheat_start();
    
    return 0;
}

