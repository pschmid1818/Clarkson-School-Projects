Midterm Part 2

To Compile: gcc lf.c -o lf -std=c99

Output:
$ ./lf ./tmp1/ -d
Directory: 2tmp
Directory: 3tmp
$ ./lf ./tmp1/ -d -r
Directory: 2tmp
Regular File: n1.txt
Directory: 3tmp
$ ./lf ./tmp1/ -drs
Directory: 2tmp
Regular File: n1.txt
Directory: 3tmp
$ ./lf ./tmp1/2tmp -r
$ ./lf ./tmp1/2tmp/ -r
Regular File: file1.txt
Regular File: file2.txt
$ ./lf ./tmp1/2tmp/ -d
$ ./lf ./tmp1/3tmp/ -d
Directory: 5tmp
$ ./lf ./tmp1/3tmp/ -r
Regular File: file2.txt
