#! /bin/bash
if [ $# -lt 1 ]; then
    echo 'Usage: convertROOTtoCSV [--write-all] <filename.root>'
    echo 'Default is to write only the STDCs. --write-all will also write ADCs and FTDCs.'
else
    WRITEALL="false"
    INFILE=$1
    if [ $# -eq 2 ]; then
	INFILE=$2
	if [ $1 = "--write-all" ]; then
	    WRITEALL="true"
	fi
    fi
    echo "Converting file $1 to CSV..."
    root -b -q 'src/convertROOTtoCSV.cxx("'$INFILE'", '$WRITEALL')'
    FNAME=`basename $INFILE`
    CSVNAME=`echo $FNAME | sed 's/\.root/\.csv/'`
    ZIPNAME=`echo $FNAME | sed 's/\.root/\.zip/'`
    echo "Done converting file. Compressing to $ZIPNAME ..."
    zip $ZIPNAME $CSVNAME
fi

