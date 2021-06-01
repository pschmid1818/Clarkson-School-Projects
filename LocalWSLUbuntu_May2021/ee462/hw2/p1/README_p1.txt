Question 1: Collaberated with Andrew York, but did not share code.

---- Output ------------------------------------------------------

$ ./simtee test.txt
To be written to file test.txt, enter to end:
this is a test
this is a test
to write to file
to write to file
end of file
end of file


File test.txt has been closed
$ cat test.txt
this is a test
to write to file
end of file

$ ls | ./simtee test.txt
To be written to file test.txt, enter to end:
README_p1.txt
simtee
simtee.c
test.txt

File test.txt has been closed
$ cat test.txt
README_p1.txt
simtee
simtee.c
test.txt
