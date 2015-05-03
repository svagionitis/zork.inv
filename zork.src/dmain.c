/* DUNGEON-- MAIN PROGRAM */

/*COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142*/
/* ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED */
/* WRITTEN BY R. M. SUPNIK */

#define EXTERN
#define INIT

#include "funcs.h"
#include "vars.h"

/* void changed to int, Volker Blasius, 11jul93 */
int main(int argc, char *argv[])
{
    // Silence the compiler warnings
    // by using argc and argv.
    argc = argc;
    argv[argc] = NULL;

/* 1) INITIALIZE DATA STRUCTURES */
/* 2) PLAY GAME */

    if (init_()) {
	game_();
    }
/* 						!IF INIT, PLAY GAME. */
    exit_();

    return 0;
/* 						!DONE */
} /* MAIN__ */

