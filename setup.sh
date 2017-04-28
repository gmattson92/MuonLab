#!/bin/bash

MUONLABDIR=`pwd`
printf "\nMUONLABDIR = " $MUONLABDIR

MYDAQ='MyDaq'
XXUSB='xxusb_3.22'

MYDAQDIR=$MUONLABDIR/$MYDAQ
printf "\nMYDAQDIR   = " $MYDAQDIR

export XXUSBDIR=$MUONLABDIR/$XXUSB
printf "\nXXUSBDIR   = " $XXUSBDIR

printf "\n\nInstalling XXUSB\n\n"
cd $XXUSBDIR/src
make -j4

printf "\n\nInstalling MyDaq\n\n"
cd $MYDAQDIR
make -j4

printf "\nDone\n"