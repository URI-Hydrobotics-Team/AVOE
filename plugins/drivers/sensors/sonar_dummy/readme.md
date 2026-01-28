# HYDRO'S Biggest PITA code yet

>[!WARNING]
>THIS DOES NOT HAVE THE LIBRARY/DRIVER THE CODE WILL NOT WORK WITH OUT IT

### TODO:
* [ ] Include a subthingamabob of the custom ping cpp library 


>[!IMPORTANT]
>This sensor uses the CMake build system rather than the conventional .sh build system we have implemented -- vendor lock in :)

#### Compile 
Simply type the following
```
cmake -B build
```
This will generate the makefile for the cmake stuff

To actually make the program
```
cmake --build build
```

this program atm is able to utilise a virtual serial port to export utilizing socat

example
on a seperate console while the program is running 
```
echo "42 52 04 05 00 00 00 01 02 03 00 a3 00" > /dev/pts/1
```
the output should display somthing like this 

Version:0.0.0 \
Distance:0\
Conf:0

Version:0.0.0\
Distance:0\
Conf:0

Version:0.0.0\
Distance:0\
Conf:0

Version:1.2.3\
Distance:0\
Conf:0

Version:1.2.3\
Distance:0\
Conf:0

You can also get simple-distance values  for the distance in confidence in a similar manner

SEE [Ping Protocol](https://docs.bluerobotics.com/ping-protocol/)
for reference
