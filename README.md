# trafficLightTask
home task from seraphimas-hls
Original letter:

Guidelines:
The project should be written for linux, in C++ (14+), using std library only.
You can use any tool to build the project (from Eclipse IDE to writing your own make file).
Include a readme with software design decisions (what and why you implemented) and compilation instructions.
 
Project:
Create random amount of Trafic-lights (3..20), they don’t know about each other but only one can be green at a time.
 
Each traffic-light [class] has [a random] Priority; name-idx (for logging)
The traffic-light can be Green or Red <Bonus: Transition between states>
Each traffic-light is its own thread <Bonus: use timer instead; https://linux.die.net/man/2/timer_create>
 
Every time a traffic-light wants to / changes state it will call a custom created driver (ioctl / or ..) with the relevant command and name-idx; printk to the screen;
<Bonus: also write to the log file; Avoid conflicts using blocking flock https://linux.die.net/man/2/flock>
Avoid starvation of low Priority traffic-lights.
