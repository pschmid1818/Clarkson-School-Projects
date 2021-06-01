Compiled with: gcc orph.c -o orph
Run with:      ./orph

Because the parent dies before the child by having the child sleep, it becomes a child of init.
The code prints out the ppid and the system call "ps aux | grep [ppid]" to compare.

---- Output ----
$ ./orph
Parent is leaving child!
$ Child sleeping!
$ Child sleeping!
root          1  0.0  0.0 126008  3228 ?        Ss   May04   2:44 /usr/lib/systemd/systemd --switched-root --system --deserialize 22

... (Removed for brevity, but its everything with a 1 in it)

Parent Procces ID: 1
$
