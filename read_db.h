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


// Exits
#define EXITS_MAX 900
struct {
    integer xlnt, //Array counter for exits
            travel[EXITS_MAX];
} exits;

#define exits_rooms exits


// Objects
#define OBJCTS_MAX 220
struct {
    integer olnt, // Array counter for objects
            odesc1[OBJCTS_MAX], odesc2[OBJCTS_MAX],
            odesco[OBJCTS_MAX], oactio[OBJCTS_MAX],
            oflag1[OBJCTS_MAX], oflag2[OBJCTS_MAX],
            ofval[OBJCTS_MAX], otval[OBJCTS_MAX],
            osize[OBJCTS_MAX], ocapac[OBJCTS_MAX],
            oroom[OBJCTS_MAX], oadv[OBJCTS_MAX],
            ocan[OBJCTS_MAX], oread[OBJCTS_MAX];
} objcts;

#define objcts_o objcts
#define eqo ((integer *)&objcts_o + 1)

/* Object flags (oflags) */

#define VISIBT (32768)
#define READBT (16384)
#define TAKEBT (8192)
#define DOORBT (4096)
#define TRANBT (2048)
#define FOODBT (1024)
#define NDSCBT (512)
#define DRNKBT (256)
#define CONTBT (128)
#define LITEBT (64)
#define VICTBT (32)
#define BURNBT (16)
#define FLAMBT (8)
#define TOOLBT (4)
#define TURNBT (2)
#define ONBT (1)
#define FINDBT (32768)
#define SLEPBT (16384)
#define SCRDBT (8192)
#define TIEBT (4096)
#define CLMBBT (2048)
#define ACTRBT (1024)
#define WEAPBT (512)
#define FITEBT (256)
#define VILLBT (128)
#define STAGBT (64)
#define TRYBT (32)
#define NOCHBT (16)
#define OPENBT (8)
#define TCHBT (4)
#define VEHBT (2)
#define SCHBT (1)


// Object rooms
#define OBJCTS_ROOM2_MAX 20
struct {
    integer r2lnt, // Array counter for oroom
            oroom2[OBJCTS_ROOM2_MAX], rroom2[OBJCTS_ROOM2_MAX];
} oroom2;

#define oroom2_o oroom2


// Cevent
#define CEVENT_MAX 25
struct {
    integer clnt, // Array counter for cevent
            ctick[CEVENT_MAX], cactio[CEVENT_MAX];
    logical cflag[CEVENT_MAX];
} cevent;

#define cevent_c cevent
#define eqc ((integer *)&cevent_c + 1)

#endif /* READ_DB_H */
