Trigger Pattern notes
=====================


To make a "scene" currently : 

We have a bunch of TriggerPatterns which are a collection of triggers. Each trigger has at least one type of firework that it can fire, and it also has recharge settings, power levels etc. 

What's wrong with that? 

There's a lot of duplication of data, and lots of triggers. As there are only 2 or 3 recharge settings, it'd probably be better to have those preset rather than fully adjustable parameters. 



###Proposed new architecture - requirements

Triggers globally managed rather than owned by Scene->Arrangements->triggerPatterns->triggers. Or perhaps owned by Scene. 

Fixed number of triggers across the screen, and turned off and on dependent on the Scene/arrangement.

Preset trigger recharge types and speeds that can be adjusted globally.

Triggers can be synced together dependent on music. 

Scene owns music track? 

Scene owns playback / recording? 


##What is the data for a scene

Collection of rockets. 

Are rockets configurable? 
	- direction
	- colour
	- 'power'

##How do I want to design a scene?

I want to give specific triggers particular rockets
I think the triggerPattern system works - an arrangement of rockets.
I want to be able to make triggers recharge at a specific time to go with the music
I want to be able to make triggers that are based on the beat 
I want to be able to have the option of 'guitar hero' like sequences
I want the triggers to automatically change height dependent on the height of the people standing there. 

##What is the data for a scene? 

#A bunch of rockets
#A bunch of arrangements 
	- an arrangement is one or more rocket types that is repeated across the triggers
	- the rocket types should probably automatically shift across the triggers so that everyone gets a chance to make a particular type of rocket
	- The arrangement should probably also have trigger settings, 

#Trigger types :
	- fast / medium / slow recharge speeds
	- or give them a time when they have to be recharged by (possibly including 
	- triggers that make small fireworks when they're low on energy or big ones when they're full ? 

#Data for triggers
If we have a bunch of triggers, we're going to need to send them settings on an arrangement change for : 

	- rocketType
	- trigger type (one shot, rechargable, different rockets dependent on power) and recharge speed (just recharge speed?) 
	- render style

###Fireworks refactor

Settings for : 
	- speed variance
	- size variance (particles and velocities)
	- target height

Physics for rockets adjusted to use bezier curves - more controllable target positions

###Sound sync
Probably have a main jukebox type manager that can handle fade outs and stuff. Scenes need to know where in the music it is. Perhaps some sort of beat matching? Volume change between SFX and music. ofxAudioUnit for sound processing.




 

