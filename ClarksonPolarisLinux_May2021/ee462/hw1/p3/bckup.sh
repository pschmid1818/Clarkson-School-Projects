BACKUPTIME=`date +%d%b%y_%H%M`

DEST=/tmp/$USER

backupfile () {

if [ -z "$1" ]
then
        exit 2
else
        if [ -d "$1" ]
        then
                exit 2
        else
		if [ -f "$1" ]; then
			if [ -d "$DEST" ]; then
				
                        	if [ "${1#/}" = "$1" ]; then
                        	cp -p $1 $DEST/$1_$BACKUPTIME.bk
                                	if [ "$?" != "0" ]; then
                                        	exit 1
                                	fi
                        	else
                        	cp -p $1 $DEST/hosts_$BACKUPTIME.bk
                                	if [ "$?" != "0" ]; then
                                        	exit 1
                                	fi
                        	fi
			else
				mkdir $DEST
				
                                if [ "${1#/}" = "$1" ]; then
                                cp -p $1 $DEST/$1_$BACKUPTIME.bk
                                        if [ "$?" != "0" ]; then
                                                exit 1
                                        fi
                                else
                                cp -p $1 $DEST/hosts_$BACKUPTIME.bk
                                        if [ "$?" != "0" ]; then
                                                exit 1
                                        fi
                                fi
			fi
		else
			exit 2		
		fi
        fi
fi

}

backupfile $1

exit 0
