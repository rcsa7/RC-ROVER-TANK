                   .:                     :,                                          
,:::::::: ::`      :::                   :::                                          
,:::::::: ::`      :::                   :::                                          
.,,:::,,, ::`.:,   ... .. .:,     .:. ..`... ..`   ..   .:,    .. ::  .::,     .:,`   
   ,::    :::::::  ::, :::::::  `:::::::.,:: :::  ::: .::::::  ::::: ::::::  .::::::  
   ,::    :::::::: ::, :::::::: ::::::::.,:: :::  ::: :::,:::, ::::: ::::::, :::::::: 
   ,::    :::  ::: ::, :::  :::`::.  :::.,::  ::,`::`:::   ::: :::  `::,`   :::   ::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  :::::: ::::::::: ::`   :::::: ::::::::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  .::::: ::::::::: ::`    ::::::::::::::: 
   ,::    ::.  ::: ::, ::`  ::: ::: `:::.,::   ::::  :::`  ,,, ::`  .::  :::.::.  ,,, 
   ,::    ::.  ::: ::, ::`  ::: ::::::::.,::   ::::   :::::::` ::`   ::::::: :::::::. 
   ,::    ::.  ::: ::, ::`  :::  :::::::`,::    ::.    :::::`  ::`   ::::::   :::::.  
                                ::,  ,::                               ``             
                                ::::::::                                              
                                 ::::::                                               
                                  `,,`


https://www.thingiverse.com/thing:2527319
Rover platform by nahueltaibo is licensed under the Creative Commons - Attribution license.
http://creativecommons.org/licenses/by/3.0/

# Summary

This a rover platform that you can assemble choosing among many **blocks** that fit in the same **mounting points**, so you can adapt the design to what ever fits your needs the better.

**NOTE:** You can find the main page of the project, with the index of related links and articles [here](http://savagemakers.com/portfolio/3d-printable-rover/). 

I thought it to be as symmetric as possible, allowing you to reuse many parts in different spots, for example, the front and back shells have the same mounting points, allowing you to print the *Shell - RPi Camera* for the front, and the *Shell - Blank* for the back part. Unless you want a camera in the back too. You could also print the *Shell - Switch* for the back, to control the power source of your rover.. Your imagination is the limit.

I am designing this in Sketchup, these files will be uploaded too, in case you want to design custom blocks yourself.

+ In [this video](https://youtu.be/DBhW78IU3l8), you can see in detail how to mount a track frame (One side of the robot)

**NOTE:** Please let me know if you find issues on any of the parts, and if you would like me to create a specific block for any hardware you think could be useful.

#####Files description
+ **InnerTrackFrame - DCMotor v0.3.stl**
  + It is the block that holds [this kind of  DC motor](http://savagemakers.com/yellowdcgearmotor).
  + You need 4 of them.
  
+ **CenterTrackFrame v0.3.stl**
  + Is the block used to hold two InnerTrackFrames together
  + You need 2 of them.
  
+ **OuterTrackFrame v0.3 .stl**
  + This block locks into the CenterTrackFrame and covers a wheel
  + You need 4 of them.
  
+ **Shell - Blank v0.2.stl**
  + This block locks into the InnerTrackFrames. It is the front and/or back of the rover
  + You need 2 Shell blocks of any type.
  
+ **Shell - Switch v0.1.stl**
  + This block locks into the InnerTrackFrames. It is the front and/or back of the rover
  + It is design to host [this kind of switch](http://savagemakers.com/latchingtoggleswitch), to control the power of your rover
  + You need 2 Shell blocks of any type.
  
+ **Shell - RPi Camerav0.3.stl**
  + This block locks into the InnerTrackFrames. It is the front and/or back of the rover
  + It is design to host a [Raspberry pi camera module](http://savagemakers.com/rpicamera)
  + You need 2 Shell blocks of any type.

+ **Shell - RPi Camera Support v0.3.stl**
  + This block locks inside the Shell - RPi Camera
  + You only need it if you are also printing the Shell - RPi Camera.

+ **Track v0.1.stl**
  + This block is one link of the track chain. 
  + You need print 27 per side (54 in total)
  
+ **Cog - Drive v0.1.stl**
  + This block is what moves the track
  + You need 4 of them.

+ **Spindle - DC Motor v0.3.stl**
  + This is what links a motor to its Cog
  + You need 1 per each InnerTrackFrame - DCMotor you have (so 4 in total)
  
+ **Cover - Blank - v3.stl**
  + This block acts as base or cap (top or bottom) of your rover
  + You need 2 Cover blocks of your choice.


# Print Settings

Printer: FLSun Mini Kossel
Rafts: Doesn't Matter
Supports: Doesn't Matter

Notes: 
The settings depend on the part you are printing.
+ **Cog** should be printed with Support, and I printed it also with brim, but just because the support was not sticking to the bed. If you dont have this problem, then you don't need the brim (but print it with support)

+ **Shell:** I printed without supports, and with 0.3 mm resolution
+ **InnerTrackFrame:** No supports, 0.3 mm resolution
+ **CenterTrackFrame:** No supports, 0.3 mm resolution
+ **OuterTrackFrame:** No supports, 0.3 mm resolution
+ **Tracks:** No support, 0.2mm resolution
 


# Post-Printing

#### Materials
To assemble this rover you will need the some M3 Screws. I bought mine from [here](http://savagemakers.com/cupheadm3screws). I used M3x10, but you can use something a little shorter too. I did not use nuts, but if you could, if you find the screw is not fasten enough

#### InnerTrackFrame Mounting point
These blocks support the motors, and act as main chassis for the rover. Right now I designed one for a 6v DC motor, but I'm planning to create another based on a standard continuos rotation servo [like these](http://savagemakers.com/360servo).

1. **InnerTrackTrame - DC Motor**
his block is design to support the common no name yellow dc geared motor. You can find them [here in aliexpress](http://savagemakers.com/yellowdcgearmotor).

---
#### Shell  Mounting point
   The Shells are the front and back of the rover. You can choose the shell block that fits your need the better. Here is the list of shells that exist right now:

1. **Shell  - Blank**
   As the name says, this is a basic shell, you could use this if you don't want your rover to have holes you will not use.

2. **Shell  - Raspberry Pi Cam**
   This Shell was design to accommodate a Raspberry Pi camera, if you are planning to use one, you can use this block to fit it in the front of your rover. You can find the camera [here](http://savagemakers.com/rpicamera)

3. **Shell  - Switch**
   This Shell was design to accommodate a switch so you can turn on/off your rover without using the main area for the electronics. The hole has 7mm, and was designed for the switch you can find [here](http://savagemakers.com/latchingtoggleswitch).

---
#### Cover Mounting point
   The Covers are the top and bottom of the rover. You can choose the cover block that fits your need the better. Here is the list of covers that exist right now:

1. **Cover - Blank**
   As the name says, this is a basic cover block, you could use this if you don't want your rover to have holes you will not use.