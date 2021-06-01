Compile with: gcc info.c -o info

--- Output ---------------------------------------------------
$ gcc info.c -o info
$ ./info
Original: Current PID: 389
Child: Current PID: 390
Original: Parent PID: 9
Child: Parent PID: 389
Original: Current Working Directory: /home/schmidp/ee462/hw3/p2
Child: Current Working Directory: /home/schmidp/ee462/hw3/p2/tmp
Original: Process Root Directory: /home/schmidp/ee462/hw3/p2
Child: Process Root Directory: /home/schmidp/ee462/hw3/p2/tmp
Original: Process Executable: /home/schmidp/ee462/hw3/p2/info
Child: Process Executable: /home/schmidp/ee462/hw3/p2/info