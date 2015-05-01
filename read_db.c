#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read_db.h"

// If the character is printable return it, else return space
#define RETURN_PRINTABLE(n) (((n) > 31 && (n) < 127) ? (char) (n) : ' ')

#if 0
// dinit.c:38
/* Read a single two byte integer from the index file */
#define rdint(indxfile) \
    (ch = getc(indxfile), \
     ((ch > 127) ? (ch - 256) : (ch)) * 256 + getc(indxfile))
#endif

inline integer rdint(FILE *f)
{
    integer ch = 0;

    ch = getc(f);

    if (ch > 127)
        return ((ch - 256) << 8) + getc(f);
    else
        return (ch << 8) + getc(f);
}

#if 0
// dinit.c:44
/* Read a number of two byte integers from the index file */
static void rdints(c, pi, indxfile)
integer c;
integer *pi;
FILE *indxfile;
{
    integer ch;	/* Local variable for rdint */

    while (c-- != 0)
	*pi++ = rdint(indxfile);
}
#endif

// Read c 2-byte integers in pi
void rdints(integer c, integer *pi, FILE *f)
{
    while(c-- != 0)
        *pi++ = rdint(f);
}

#if 0
// dinit.c:57
/* Read a partial array of integers.  These are stored as index,value
 * pairs.
 */
static void rdpartialints(c, pi, indxfile)
integer c;
integer *pi;
FILE *indxfile;
{
    integer ch;	/* Local variable for rdint */

    while (1) {
	int i;

	if (c < 255) {
	    i = getc(indxfile);
	    if (i == 255)
		return;
	}
	else {
	    i = rdint(indxfile);
	    if (i == -1)
		return;
	}

	pi[i] = rdint(indxfile);
    }
}
#endif

void rdpartialints(integer c, integer *pi, FILE *f)
{
    integer i = 0;

    while(1)
    {
        if (c < 255)
        {
            i = getc(f);
            if (i == 255)
                return;
        }
        else
        {
            i = rdint(f);
            if (i == -1)
                return;
        }

        pi[i] = rdint(f);
    }
}

#if 0
// dinit.c:86
/* Read a number of one byte flags from the index file */
static void rdflags(c, pf, indxfile)
integer c;
logical *pf;
FILE *indxfile;
{
    while (c-- != 0)
	*pf++ = getc(indxfile);
}
#endif

void rdflags(integer c, logical *pf, FILE *f)
{
    while(c-- != 0)
        *pf++ = getc(f);
}

// Read each character and print
// in the stdout.
void rdfile(FILE *f)
{
    integer c = 0;

    do
    {
        c = getc(f);
        fprintf(stdout, "%c", (char) c);
#if 0
        // Print only the printable characters
        fprintf(stdout, "%c", (c > 31 && c < 127) ? (char) c : ' ');
#endif
    } while(c != EOF);

    fprintf(stdout, "\n");
}

void usage(char *argv0)
{
    fprintf(stdout, "Usage: %s <filename>\n", argv0);
    exit(-1);
}

int main(int argc, char *argv[])
{
    FILE *f = NULL;
    integer n = 0;

    if (argc != 2)
        usage(argv[0]);

    char *fname = argv[1];

    f = fopen(fname, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Cannot open file %s\n", fname);
        return -1;
    }

#if 0
    rdfile(f);
#endif

#if 1
    //Init state
    memset(&state_status, 0, sizeof(state));
    state_status.ltshft = 10;
    state_status.mxscor = state_status.ltshft;
    state_status.mxload = 100;

    // Init star
    memset(&star_obj, 0, sizeof(star));

    // Init rooms
    memset(&rooms_place, 0, sizeof(rooms));

    // Check version
    integer maj = rdint(f);
    fprintf(stdout, "Pos: %d Data read %d - %c\n", ftell(f), maj, RETURN_PRINTABLE(maj));
    integer min = rdint(f);
    fprintf(stdout, "Pos: %d Data read %d - %c\n", ftell(f), min, RETURN_PRINTABLE(min));
    integer edit = rdint(f);
    fprintf(stdout, "Pos: %d Data read %d - %c\n", ftell(f), edit, RETURN_PRINTABLE(edit));

    if (maj == version.vmaj && min == version.vmin && edit == version.vedit)
        fprintf(stdout, "The version %d.%d%c is correct\n", maj, min, edit);
    else
        fprintf(stdout, "The version %d.%d%c is *NOT* correct\n", maj, min, edit);


    state_status.mxscor = rdint(f);
    fprintf(stdout, "Pos: %d Data read %d - %c\n", ftell(f), state_status.mxscor, RETURN_PRINTABLE(state_status.mxscor));

    star_obj.strbit = rdint(f);
    fprintf(stdout, "Pos: %d Data read %d - %c\n", ftell(f), star_obj.strbit, RETURN_PRINTABLE(star_obj.strbit));

    state_status.egmxsc = rdint(f);
    fprintf(stdout, "Pos: %d Data read %d - %c\n", ftell(f), state_status.egmxsc, RETURN_PRINTABLE(state_status.egmxsc));


    rooms_place.rlnt = rdint(f); // Get array counter for rooms
    fprintf(stdout, "Pos: %d Data read %d - %c\n", ftell(f), rooms_place.rlnt, RETURN_PRINTABLE(rooms_place.rlnt));

    // Populate rooms arrays
    rdints(rooms_place.rlnt, &rooms_place.rdesc1[0], f);
    fprintf(stdout, "Pos: %d\n", ftell(f));
    rdints(rooms_place.rlnt, &rooms_place.rdesc2[0], f);
    fprintf(stdout, "Pos: %d\n", ftell(f));
    rdints(rooms_place.rlnt, &rooms_place.rexit[0], f);
    fprintf(stdout, "Pos: %d\n", ftell(f));
    rdpartialints(rooms_place.rlnt, &rooms_place.ractio[0], f);
    fprintf(stdout, "Pos: %d\n", ftell(f));
    rdpartialints(rooms_place.rlnt, &rooms_place.rval[0], f);
    fprintf(stdout, "Pos: %d\n", ftell(f));
    rdints(rooms_place.rlnt, &rooms_place.rflag[0], f);
    fprintf(stdout, "Pos: %d\n", ftell(f));

#endif

    if (f)
        fclose(f);

    return 0;
}
