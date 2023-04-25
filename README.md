GM updates Spring 2023

First, read the original README file from Yakov (copied below). My additions
are just for convenience -- namely fix_xxusb.sh will update the udev rules
according to the troubleshooting section in the original README.

----- Troubleshooting -----
1. If you get an error about libxxusb not being found while trying to install
   or run the DAQ software, try sourcing env.sh:
      $ source MyDaq/run/env.sh

2. If you run the DAQ program and it exits with an error "Device not xxusb",
   run the fix_xxusb.sh script (as root):
      $ sudo MyDaq/run/fix_xxusb.sh
   If running the DAQ still does not work after this, try running fix_xxusb.sh
   again... sometimes it does not work the first time.

----- Other Additions -----
I added a script under MuonData/convert_to_csv to convert a .root data file
into a .csv for use in analysis. By default only the STDC data are included in
the csv file. To write ADC and FTDC data as well, pass the --write-all option:
      $ MuonData/convert_to_csv/convertROOTtoCSV.sh [--write-all] <file.root>
The csv file will have the same base name as the .root file with only the
extension changed. The script will also create a compressed .zip copy of the
data for convenience (again with the same base name).

----- Other Notes -----
In Spring 2023 I did *not* need to change the root version 
(i.e. module load root). The default ROOT version installed on esb-5103-linux-02
worked correctly with the DAQ software. That said, Mason had to fight with this
in Fall 2022 to find a version of ROOT which does work with the DAQ. YMMV?


----- Original README -----


README FOR MUON LAB USING CC-USB CRATE CONTROLLER
WRITTEN BY YAKOV KULINICH SPRING 2016

------------------------------------------------------
------------------------------------------------------
Simple Installation Instructions

1)  First, you need root loaded on this machine, type	   
    module load root/6.02.08

    Note: root might be upgraded and versions change
    Best bet is to type
    module load root/6[TAB]
    Do not type [TAB] but instead autocomplete root/6*.**.**

2)  install
    source setup.sh

3)  load environment variable XXUSBDIR
    echo env.sh (from run directory)

4)  Run directory is in MyDaq/run
    cd MyDaq/run

------------------------------------------------------
------------------------------------------------------
General Installation Instructions
For users with Linux Experience

1)  Copy xxusb_3.22 to some local directory
    I.E. ~/soft
   
    (You can put this anywhere, but for the sake of the instructions
    I will continue assuming this directory.)

2)  Go to ~/soft/xxusb_3.22/src

    make

    make install

Now, xxusb libraries are installed. Next, you need to add 
xxusb and it's libraries to your environment variables.

3)  Using favorite editor, open ~/.bashrc

4)  At bottom, add (USERNAME is your username)
    export XXUSBDIR=/home/USERNAME/soft/xxusb_3.22
 
    Again, if you put the xxusb_3.22 somewhere else, change the path
    appropriately.

5)  Close terminal and open new one.
    (Alternitavely, run source ~/.bashrc)

6)  Load root every time you have a new terminal
    module load root/6.02.08

7)  Take MyDaq (from the tar package) and copy it to directory of choice
   
    Inside DIRECTORY_OF_CHOICE/MyDaq

    make

8)  ./runMyDaq

    A GUI will pop up. There is a text entry field.
    You can enter a name for your run (i.e. run_04_18_15)
    Otherwise, default name (output) will be used.
    
    Note: .root will be appended to the run name.
    	  So, in above examples, the outputs will be 
    	  run_04_18_15.root or output.root
 	
    Click Start.

    Do not exit using X at top. Finish with Stop first.

Enjoy! 

------------------------------------------------------
------------------------------------------------------
TROUBLESHOOTING

1) If you get 

Finding XX_USB devices and opening first one found
Found   XX_USB device
Segmentation fault

		You need to turn on and off the CAMAC crate.

2) If you get 

Finding XX_USB devices and opening first one found


Device not xxusb

... Followed by a Seg Fault

    	     There is something wrong with the permissions to
	     access the usb. 
	     This can be solved by going as some super user
	     and typing
	     
	     udevadm control --reload-rules
	     udevadm trigger

	     Alternatively, contact IT support and explain to them 
	     the USB udev rules are incorrect somehow.

3) If above does not work, might need to update udev rules.
	
	Add following lines into
	/etc/udev/rules.d
	/lib/udev/rules.d
	
	SUBSYSTEM=="usb", ATTRSidVendor=="16dc", MODE:="0666"

4) If during setup you get something about usb.h not found. You probably dont have libusb-devel
		
	     sudo yum install libusb*

