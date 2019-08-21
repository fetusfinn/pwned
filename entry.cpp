/*
 *  pwnedhook v2
 */

/*  todo
 *
 *  move all structs and enums to their headers
 *
 *  features
 *      offscreen
 *      chams
 *      antiaim
 *
 *  menu
 *      header
 *      group
 */

/*  links
 *
 *  https://www.unknowncheats.me/forum/counterstrike-global-offensive/330483-disable-model-occulusion.html
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

