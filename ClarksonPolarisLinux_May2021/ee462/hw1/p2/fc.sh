if [ -z "$1" ]
then
        echo [Using pwd: $PWD]
        cd $PWD
        ls -1 | wc -l
else
        if [ -d "$1" ]
        then
                cd $1
                ls -1 | wc -l
        else
                echo [$1 is not a directory]
                echo [Using pwd: $PWD]
                cd $PWD
                ls -1 | wc -l
        fi
fi

exit 0

