#!/bin/sh

FILENAME='Angel_Lopez_Manriquez_DSD_4CM1_1.txt'

# create new file
rm $FILENAME > /dev/null 2> /dev/null
touch $FILENAME


for f in $(ls *\.cpp); do
    cat $f >> $FILENAME
    echo '********************************************************************************************************' >> $FILENAME
done


