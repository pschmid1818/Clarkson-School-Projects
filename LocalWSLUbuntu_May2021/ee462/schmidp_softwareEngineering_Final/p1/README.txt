Compiled with: gcc zomb.c -o zomb
Run with:      ./zomb

As the child exits but the parent is waiting and cant reap it. 
Therefore when ps aux | grep 'Z' is called a processes started 10 seconds ago 
(the same minute but first) is the only one with the status "Z+", meaning zombie.

---- Output ----
$ ./zomb
Parent waiting...
Killing child...
Finding all zombie processes...
USER        PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
schmidp   59522  0.0  0.0      0     0 pts/60   Z+   10:35   0:00 [zomb] <defunct>
schmidp   59629  0.0  0.0 113284  1200 pts/60   S+   10:35   0:00 sh -c ps aux | grep 'Z'
schmidp   59631  0.0  0.0 112816   936 pts/60   R+   10:35   0:00 grep Z
