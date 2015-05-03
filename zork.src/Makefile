# Makefile for dungeon

# Where to install the program
BINDIR = /usr/games

# Where to install the data file
LIBDIR = /usr/games/lib

# The dungeon program provides a ``more'' facility which tries to
# figure out how many rows the terminal has.  Several mechanisms are
# supported for determining this; the most common one has been left
# uncommented.  If you have trouble, especially when linking, you may
# have to select a different option.

# more option 1: use the termcap routines.  On some systems the LIBS
# variable may need to be set to -lcurses.  On some it may need to
# be /usr/lib/termcap.o.  These options are commented out below.
LIBS = -ltermcap
TERMFLAG =
# LIBS = -lcurses
# LIBS = /usr/lib/termcap.o

# more option 2: use the terminfo routines.  On some systems the LIBS
# variable needs to be -lcursesX, but probably all such systems support
# the termcap routines (option 1) anyhow.
# LIBS = -lcurses
# TERMFLAG = -DMORE_TERMINFO

# more option 3: assume all terminals have 24 rows
# LIBS =
# TERMFLAG = -DMORE_24

# more option 4: don't use the more facility at all
# LIBS =
# TERMFLAG = -DMORE_NONE

# End of more options

# Uncomment the following line if you want to have access to the game
# debugging tool.  This is invoked by typing "gdt".  It is not much
# use except for debugging.
# GDTFLAG = -DALLOW_GDT

# Compilation flags
CFLAGS = -O -Wall -Wextra -Wshadow -Wstrict-prototypes -Wmissing-prototypes
# On SCO Unix Development System 3.2.2a, the const type qualifier does
# not work correctly when using cc.  The following line will cause it
# to not be used and should be uncommented.
# CFLAGS= -O -Dconst=

##################################################################

# Source files
CSRC =	$(shell echo *.c)

# Object files
OBJS =	$(CSRC:.c=.o)

MAIN =	dungeon

$(MAIN): $(OBJS) dtextc.dat
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

install: $(MAIN) dtextc.dat
	cp $(MAIN) $(BINDIR)
	cp dtextc.dat $(LIBDIR)

clean:
	rm -f $(OBJS) $(MAIN) dtextc.dat core dsave.dat *~

dtextc.dat:
	cat dtextc.uu1 dtextc.uu2 dtextc.uu3 dtextc.uu4 | uudecode

.c.o:
	$(CC) $(CFLAGS) $(GDTFLAG) $(TERMFLAG) -DTEXTFILE=\"$(LIBDIR)/dtextc.dat\" -c $<  -o $@

