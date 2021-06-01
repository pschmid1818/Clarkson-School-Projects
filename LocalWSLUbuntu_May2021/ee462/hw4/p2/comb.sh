if [ ! -p /tmp/f1fo ]       #Check if pipe f1fo doesnt exists
then
    mkfifo /tmp/f1fo        #Create pipe f1fo
fi
if [ ! -p /tmp/f2fo ]       #Check if pipe f2fo doesnt exists
then
    mkfifo /tmp/f2fo        #Create pipe f2fo
fi
cat $1 > f1fo               #Redirect ouput of cat $1 (filler4.txt) into f1fo
bash prog1.sh > f2fo < f1fo #Redirect f1fo into prog1.sh, output of that is redirected into f2fo
bash prog2.sh < f2fo        #Redirect f2fo into prog2.c
bash prog3.sh < f2fo        #Redirect f2fo into prog3.c