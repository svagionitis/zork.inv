Convert uppercase filenames to lowercase
=========================================

	for file in $(ls *.C); do git mv $file $(echo $file | tr [:upper:] [:lower:]); done

Sources:
*   http://blog.mc-thias.org/?title=rename-files-from-upper-case-filename-to&more=1&c=1&tb=1&pb=1
*   http://stackoverflow.com/questions/10523849/git-changing-capitalization-of-filenames


Graphical diff tool on Mac OS X
================================

There''s `FileMerge.app`, which comes with XCode. From command line run

	opendiff file1 file2 [-ancestor ancestorFile] [-merge mergeFile]

Sources:
*   http://stackoverflow.com/questions/229142/what-are-the-alternatives-for-meld-graphical-diff-tool-on-osx


Convert Windows line endings to Unix
=====================================

When the following command is executed


	cat dtextc.uu1 dtextc.uu2 dtextc.uu3 dtextc.uu4 | uudecode


I get the following error


	uudecode: stdin: dtextc.dat: character out of range: [33-96]


This means that either there was no proper uuencoding or something wrong with the uu* files. I already have the `dtextc.dat`,
so I generated the uuencoded file with the following command


	uuencode dtextc.dat dtextc.dat > dtextc.uu


The resulting file had size of 183283 bytes. Now, I just cancatenated the other uu* files into one using the following command


	cat dtextc.uu1 dtextc.uu2 dtextc.uu3 dtextc.uu4 > dtextc.uu1234


If there is no problem, these two files should be identical, but they are not. First their sizes are different, the `dtextc.uu`
has a size of 183283 and the `dtextc.uu1234` has a size of 186246 bytes. They differ for 2963 bytes. Now I used the `diff` tool
to check where were the differnces. I used like the following


	diff -u dtextc.uu dtextc.uu1234


and it showed that the whole files were different, every line. It seemed strange because, although it was reported that each line
was different, I could visually check that there was no difference. Next following a snippet from the first three lines (the first
line differs for the 644 and 664).


	--- dtextc.uu   2015-05-02 21:06:09.000000000 +0100
	+++ dtextc.uu1234       2015-05-02 21:08:59.000000000 +0100
	@@ -1,2959 +1,2960 @@
	-begin 644 dtextc.dat
	-M``(`!P!!`DD`OP!D`+[:BMIXVFS:70````#:2P````#:/]HLVBS:+-HLVB3:
	-M+-HDVBS:+-HLVB3:+-HLVBP``-HLVB3:+-HLVBS:'MH5V@C9^-H>``#9Y]G2
	+begin 664 dtextc.dat
	+M``(`!P!!`DD`OP!D`+[:BMIXVFS:70````#:2P````#:/]HLVBS:+-HLVB3:
	+M+-HDVBS:+-HLVB3:+-HLVBP``-HLVB3:+-HLVBS:'MH5V@C9^-H>``#9Y]G2


So, I thought that should be some non-printing characters that might cause the problem, like the Windows CRLF. In order to make these
non-prinitng characters appear on the `diff` command I run the following


	diff -u dtextc.uu dtextc.uu1234 | cat -v


where the option `-v` of `cat` shows the non-printing characters. And the non-printing characters appeared


	--- dtextc.uu   2015-05-02 21:06:09.000000000 +0100
	+++ dtextc.uu1234       2015-05-02 21:08:59.000000000 +0100
	@@ -1,2959 +1,2960 @@
	-begin 644 dtextc.dat
	-M``(`!P!!`DD`OP!D`+[:BMIXVFS:70````#:2P````#:/]HLVBS:+-HLVB3:
	-M+-HDVBS:+-HLVB3:+-HLVBP``-HLVB3:+-HLVBS:'MH5V@C9^-H>``#9Y]G2
	+begin 664 dtextc.dat^M
	+M``(`!P!!`DD`OP!D`+[:BMIXVFS:70````#:2P````#:/]HLVBS:+-HLVB3:^M
	+M+-HDVBS:+-HLVB3:+-HLVBP``-HLVB3:+-HLVBS:'MH5V@C9^-H>``#9Y]G2^M


It can be seen the `^M` at the end of each line in the `dtextc.uu1234`. Now, that would explain the 2959 bytes from the 2963 bytes
difference. There were 4 bytes different. Now, I suppose it''s not coincidence, that we concatenated 4 files, so this difference
should be either at the start or at the end of the file. So, using the following command


	cat -v dtextc.uu1


I checked that there was nothing at the start of the file, but I found `^Z` at the end of the file. The same happened for the other
files. The [`^Z`](http://en.wikipedia.org/wiki/Substitute_character) is the [EOF which is used by DOS and Windows](http://en.wikipedia.org/wiki/End-of-file#EOF%20character).

So, in order to convert them to Unix, we need to remove the `^M` and `^Z`. The following command was used


	cat  dtextc.uu1 | tr -d '\r' | tr -d '\15\32' > dtextc.uu1.unx


where the `\r` removes the `^M` in each line and the `\15\32` the `^Z` at the EOF. Checking with the `cat -v`, there is no `^M` and `^Z`.
The difference at the first of the uu encoded files, 644(-rw-r--r--) and 664(-rw-rw-r--), is for the permissions.

Sources:
*   http://blog.shvetsov.com/2012/04/covert-unix-windows-mac-line-endings.html
*   http://superuser.com/questions/560050/how-to-compare-two-files-for-non-printing-characters
*   http://unix.stackexchange.com/questions/45711/diff-reports-two-files-differ-although-they-are-the-same


Convert all files from DOS/Window to Unix format
=================================================

In order to remove the non-printable `^M` and `^Z` for all the files, we execute the following


	for file in $(ls); do cat ${file} | tr -d '\r' | tr -d '\15\32' > ${file}.unx; mv -f ${file}.unx ${file}; done


Useful compilation flags (CFLAGS) for gcc 4.8.4 (mostly for warnings)
=====================================================================

Next following a number of compilation flags which are useful:
*   `-Wall`: This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid
    (or modify to prevent the warning), even in conjunction with macros. See
    [documentation](https://gcc.gnu.org/onlinedocs/gcc-4.8.4/gcc/Warning-Options.html#Warning%20Options) for more info.
*   `-Wextra`: This enables some extra warning flags that are not enabled by `-Wall`. See documentation for more info.
*   `-Wshadow`: Warn whenever a local variable or type declaration shadows another variable, parameter, type, or class member (in C++),
    or whenever a built-in function is shadowed. Note that in C++, the compiler warns if a local variable shadows an explicit typedef,
    but not if it shadows a struct/class/enum.
*   `-Wstrict-prototypes`: Warn if a function is declared or defined without specifying the argument types. (An old-style function definition
    is permitted without a warning if preceded by a declaration that specifies the argument types.)
*   `-Wmissing-prototypes`: Warn if a global function is defined without a previous prototype declaration. This warning is issued even if the definition
    itself provides a prototype. Use this option to detect global functions that do not have a matching prototype declaration in a header file.
    This option is not valid for C++ because all function declarations provide prototypes and a non-matching declaration will declare an overload rather
    than conflict with an earlier declaration.
*   `-Wfloat-equal`: Warn if floating-point values are used in equality comparisons. (We don''t have any floating numbers, but it''s good to know)
*   `-Wcast-align`: Warn whenever a pointer is cast such that the required alignment of the target is increased. For example, warn if a `char *` is cast
    to an `int *` on machines where integers can only be accessed at two- or four-byte boundaries.
*   `-Wpedantic`: Issue all the warnings demanded by strict ISO C and ISO C++.

Source:
*   https://gcc.gnu.org/onlinedocs/gcc-4.8.4/gcc/Warning-Options.html#Warning%20Options
*   http://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c


C Operator Precedence
======================

Source:
*   http://en.cppreference.com/w/c/language/operator_precedence


C/C++ Code Static Analyzers
============================

Two static code analyzers used, [`cppcheck`](http://cppcheck.sourceforge.net/) and [`flawfinder`](http://www.dwheeler.com/flawfinder/).
The errors found by `cppcheck`, the command run was `cppcheck *.{c,h}` are the following


	Checking dinit.c...
	[dinit.c:29]: (error) syntax error
	Checking dinit.c: ALLOW_GDT...
	Checking dinit.c: INIT...
	Checking dinit.c: __AMOS__...
	Checking dinit.c: __STDC__...
	Checking dinit.c: unix...
	...
	Checking nobjs.c...
	[nobjs.c:399]: (error) Array 'puzzle_.cpwl[8]' accessed at index 9, which is out of bounds.
	[nobjs.c:612]: (error) Array 'objcts_.odesc2[220]' accessed at index 761, which is out of bounds.
	Checking nobjs.c: INIT...
	Checking nobjs.c: __STDC__...
	Checking nobjs.c: unix...

After inspecting the code, they really do exist. Now, executing the `flawfinder *.{c,h}`, the output is more of suggetion of possible
issues, rather than actual problems. Next following a sample


	clockr.c:618:  [4] (crypto) crypt:
	  Function crypt is a poor one-way hashing algorithm; since it only
	  accepts passwords of 8 characters or less, and only a two-byte salt, it is
	  excessively vulnerable to dictionary attacks given today''s faster
	  computing equipment. Use a different algorithm, such as SHA-1, with a larger
	  non-repeating salt.
	np.c:14:  [4] (shell) system:
	  This causes a new program to execute and is difficult to use safely.
	  try using a library call that implements the same functionality if
	  available.
	...
	dinit.c:18:  [3] (random) srand:
	  This function is not sufficiently random for security-related
	  functions such as key and nonce creation. use a more secure technique for
	  acquiring random values.
	...
	supp.c:108:  [3] (buffer) getenv:
	  Environment variables are untrustable input if they can be set by an
	  attacker.  They can have any content and length, and the same variable
	  can be set more than once. Check environment variables carefully before
	  using them.
	...
	dinit.c:326:  [2] (misc) fopen:
	  Check when opening files - can an attacker redirect it (via symlinks),
	  force the opening of special file type (e.g., device files), move
	  things around to create a race condition, control its ancestors, or change
	  its contents?.
	...
	dso3.c:160:  [2] (buffer) char:
	  Statically-sized arrays can be overflowed. Perform bounds checking,
	  use functions that limit length, or ensure that the size is larger than
	  the maximum possible length.
	...
	dinit.c:41:  [1] (buffer) getc:
	  Check buffer boundaries if used in a loop.
	...
	gdt.c:62:  [1] (buffer) sscanf:
	  it''s unclear if the %s limit in the format string is small enough.
	  Check that the limit is sufficiently small, or use a different input
	  function.

Sources:
*   http://www.reddit.com/r/cpp/comments/2aksxk/so_ive_seen_cppcheck_and_flawfinder_any_good/
*   http://cppcheck.sourceforge.net/
*   http://www.dwheeler.com/flawfinder/
