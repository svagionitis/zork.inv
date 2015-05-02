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


