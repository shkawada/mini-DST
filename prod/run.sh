#!/bin/bash

echo "Job started"
No=0

rm *~ log/*

while read row;
do
    No=$(( No + 1 ))
    cp base.xml proc${No}.xml
    sed -i "s@INPUTNAME@${row}@g" proc${No}.xml
    sed -i "s@OUTPUTNAME@DST${No}.slcio@g" proc${No}.xml
    cp submit.sh.orig submit${No}.sh
    sed -i "s@RUNNUMBER@${No}@g" submit${No}.sh
    chmod 755 submit${No}.sh
    cp exec.submit.orig exec${No}.submit
    sed -i "s@RUNNUMBER@${No}@g" exec${No}.submit
done < sample.txt

. submit_all.sh
echo "Job submitted"
