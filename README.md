# 3D-Mapping-Prototype

Note: Code:Blocks 10.03 and SDL 1.2 must be installed to run. I'll just post a video of it working instead.

## 21/4/20
This is what we plan on eventually importing to a raspberry pi for use during the land rover competition.
When we order the accelerometers and gyroscopes and a few more US sensors then hopefully we will have a (half) decent product. 
It's more about the idea and the attempt - arduinos can only be so accurate.
The original arduino serial to SDL template comes from YouTube Channel amorag59. I used a lot of his code to set up the system initially.
There was a lot (understatement) of deugging required, but it eventually worked. The next step is to start making my own major
modifications for an ultrasonic sensor - as well as learn more about SDL and how it works

## 25/4/20
The program works about as well as I expected. Considering the competition was cancelled and I had to use a potentiometer instead of a 
gyroscope, it's not bad. The potentiometer is by no means accurate and the ultrasonic sensor isn't any better. For anyone hoping to
recreate this for some god forsaken reason, I highly recommend you use a better ultrasonic sensor than the default, and a real gyroscope
too. With just a few alterations to the arduino file, it should work much better with those instead. Besides that, it does what it was
meant to. Mission success.
