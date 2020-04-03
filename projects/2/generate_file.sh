#!/bin/sh

fname='Angel_Lopez_Manriquez_DSD_4CM1_2.txt'

rm $fname
touch $fname

both() {
    bname=$1
    echo "// $bname.h  ------------------------------------------------------------------------------" >> $fname
    cat "$bname.h" >> $fname
    echo "// $bname.cpp  ------------------------------------------------------------------------------" >> $fname
    cat "$bname.cpp" >> $fname
}

both 'Coordenada'
both 'IrregularPolygon'
both 'Ellipse'
echo "// animacion.cpp  ------------------------------------------------------------------------------" >> $fname
cat animacion.cpp >> $fname

echo "// Makefile  ------------------------------------------------------------------------------" >> $fname
cat "Makefile" >> $fname
