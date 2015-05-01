#ifndef READ_DB_H
#define READ_DB_H

#include <stdint.h>

typedef int32_t integer;
typedef int8_t logical;

// Version
const struct {
    integer vmaj, vmin, vedit;
} vers = { 2, 7, 'A' };

#define version vers


// State
struct {
    integer moves, deaths,
            rwscor, mxscor,
            mxload, ltshft,
            bloc, mungrm, hs,
	    egscor, egmxsc;
} state;

#define state_status state


// Star
struct {
    integer mbase, strbit;
} star;

#define star_obj star


// Rooms
#define ROOMS_MAX 200
struct {
    integer rlnt, // Array counter for rooms
            rdesc1[ROOMS_MAX], rdesc2[ROOMS_MAX],
            rexit[ROOMS_MAX], ractio[ROOMS_MAX],
	    rval[ROOMS_MAX], rflag[ROOMS_MAX];
} rooms;

#define rooms_place rooms
#define eqr ((integer *)&rooms_place + 1)
#define rrand ((integer *)&rooms_place + 601)

/* Room flags */
#define RSEEN  (32768)
#define RLIGHT (16384)
#define RLAND  (8192)
#define RWATER (4096)
#define RAIR   (2048)
#define RSACRD (1024)
#define RFILL  (512)
#define RMUNG  (256)
#define RBUCK  (128)
#define RHOUSE (64)
#define RNWALL (32)
#define REND   (16)


#endif /* READ_DB_H */
