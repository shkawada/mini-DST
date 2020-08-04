#!/bin/bash

echo "Job started"
No=0

rm *~ log/* DST*slcio exec*submit proc*xml submit*sh
echo "#!/bin/bash" > submit_all.sh
echo "" >> submit_all.sh

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
    echo "condor_submit exec${No}.submit" >> submit_all.sh
done < sample.txt

. submit_all.sh
echo "Job submitted"
