# trafficLightTask
home task from seraphimas-hls

## Guidelines:
The project should be written for linux, in C++ (14+), using std library only.
You can use any tool to build the project (from Eclipse IDE to writing your own make file).
Include a readme with software design decisions (what and why you implemented) and compilation instructions.
 
## Project:
Create random amount of Trafic-lights (3..20), they don’t know about each other but only one can be green at a time.
 
Each traffic-light [class] has [a random] Priority; name-idx (for logging)
The traffic-light can be Green or Red <Bonus: Transition between states>

Each traffic-light is its own thread <Bonus: use timer instead; https://linux.die.net/man/2/timer_create>
 
Every time a traffic-light wants to / changes state it will call a custom created driver (ioctl / or ..) with the relevant command and name-idx; printk to the screen; <Bonus: also write to the log file; Avoid conflicts using blocking flock https://linux.die.net/man/2/flock>

Avoid starvation of low Priority traffic-lights.
# Report
## Build && run
I have used WSL on my W10 machine, have installed it according this https://devblogs.microsoft.com/cppblog/targeting-windows-subsystem-for-linux-from-visual-studio/

Basically you have to intall your WSL, setup there build-essential, gdbserver and openssh-server. After need to configure ssh server.
but additionally you have to check for installed g++, gdb, make, rsync, zip. I can suggest just run:
```bash
sudo apt-get install -y g++ gdb make rsync zip
```
UPD from 24.06.2019:

As mentioned in task, was needed to create some driver, kernel module to emulate some device. Until this point I was running on WSL, but it based on NT kernel and ofcource there is no kernel headers which needed to compile an kernel module. I have switched to VirtualMachine with installed Debian on. Second trouble, VS 2019 still not able to recoginize all includes and in default mode compiling fails. To heal it, swithed to makefiles, Intellisense works by half, but atleast compiles.
So, to build lghtDriver project need just run make command in directory. After to load driver can call:
```bash
sudo insmod lghtIO
```
To unload:
```bash
sudo rmmod lghtIO
```
All output of driver was pointed to kernel log, to check this out need to run:
```bash
sudo dmesg
```
## TO-DO list:
 - fix of setting delays in lght.cpp, currently number are used. while using varible cause to stuck in random place of loop
 - move from threads to timers, currently respected branch "basedOnTimers" cause Segmentation fault

## First draft of system structure:
```bash
queue of levels  --> router broadcasting who can
      ^                 |
      |            wait for full queue
push idx+prior          |
 ^   ^   ^              |
 |   |   |              |
|1| |2| |n|     idx <--- 
```
Each module have inner while loop, in which:
 - pushing request (idx+priority) to queue for switch on green
 - wait until receive own idx
 - after setted delay switch to red and push request to clear reservation
 - wait for setted delay
 
 ## Current approach
 ### System structure:
 System consist: router and traffic lights
 ```bash
main()
  |
generate instances and set first idx
 |
 |>  queue of traffic lights
 |      |
 |> router broadcasting who can
 |         ^                 |
 |         |            wait for own idx
 |   next please             |
 |    ^   ^   ^              |
 |    |   |   |              |
 |>  |1| |2| |n|     idx <--- 
```
### Working flow
On very beginning we collecting all idx+priority in sorted queue

Creating stack of traffic lights and initilize each with own iterator in sorted queue

Run each traffic light in own thread with passing to pointer of router instance

To start swithing setting valid Top iterator

### Process of swithing:
Each traffic light have inner while loop, in which:
 - wait until receive own idx
 - switch on green
 - wait for setted delay
 - push request to clear reservation
 - switch to red
 - wait for setted delay

