## HYDRO'S Biggest PITA code yet

#### THIS DOES NOT HAVE THE LIBRARY/DRIVER THE CODE WILL NOT WORK WITH OUT IT

TODO: Include a subthingamabob of the custom ping cpp library 


##This Sensor Uses Cmake!!!

#To install 
simply type the following

cmake -B build

this will generate the makefile for the cmake stuff


to actually make the program

cmake --build build


this program atm is able to utilise a virtual serial port to export utilizing socat

example
on a seperate console while the program is running 

echo "42 52 04 05 00 00 00 01 02 03 00 a3 00" > /dev/pts/1

the output should display somthing like this 

Version:0.0.0
Distance:0
Conf:0

Version:0.0.0
Distance:0
Conf:0

Version:0.0.0
Distance:0
Conf:0

Version:1.2.3
Distance:0
Conf:0

Version:1.2.3
Distance:0
Conf:0

you can also enter values for distance in confidence in a simular manner

SEE https://docs.bluerobotics.com/ping-protocol/
for reference
