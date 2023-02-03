# WeatherDataSorter
Second year, first semester computer project by Efe Tatar &amp; Nathan Signoud

## How to get started
For the program to work, the user must initially enter "make" in the terminal.
This has to be done where the makefile is located.
The data file then must be put in the "resources" directory.

## How to use the program
In the main file, where the makefile and data_filter.sh are located, the user can 
use the command "bash data_filter.sh".
Some arguments are mandatory, such as -f to indicate the data file name.
It is possible to choose from an array of geographic regions such as France or Antarctica.
If no data type is specified, the program does nothing.
The user can delimit the date interval in which data is processed. 
It is possible to choose from 3 sorting algorithms which will be listed below.

## Arguments
#File
  -f
#Regions
  -F for France
  -A for Antilles
  -G for French Guyana
  -S for Saint Martin et Miquelon
  -Q for Antarctica
  -O for the Indian Ocean
#Data type
  -t or p 1
  -t or p 2
  -t or p 3
