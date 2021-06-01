Paul Schmid

Commands I used: (compiled in WSL Ubuntu)
$ gcc -c isPrime.c
$ gcc -c cfact.c 
$ ar crv libmth3cu.a cfact.o isPrime.o
$ gcc test1.c libmth3cu.a -lm -o test1
$ ./test1

output:
1329: 1 1329 3 443

27069: 1 27069 3 9023 7 3867 21 1289

8: 1 8 2 4

#non-primes: 3
