Question 2: Collaberated with Andrew York, but did not share code.

I changed xvdd (listed in hw) to xvda as the dev folder did not contain a xvdd
xen/   xvda   xvda1  xvda2  xvda3
were listed when searching by ./fltype x

---- Output ------------------------------------------------------------------

$ ./fltype $HOME
/imports/home/schmidp is a Directory

$ ./fltype /run/dmeventd-server
/run/dmeventd-server is a FIFO Special File

$ ./fltype /etc/shadow
/etc/shadow is a Regular File

$ ./fltype /dev/tty3
/dev/tty3 is a Character Special File

$ ./fltype /lib
/lib is a Directory

$ ./fltype /dev/log
/dev/log is a Socket

$ ./fltype /run/systemd/initctl/fifo
/run/systemd/initctl/fifo is a FIFO Special File

$ ./fltype /dev/xvda
/dev/xvda is a Block Special File
