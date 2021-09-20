# 2021 Update
Hey guys, this project ended on a bit of a sour note with me not being able to get it up and running last year. A lot of time has since passed though and I wanted to give an update that at long last... it lives! Thanks to an incredible little kickstarter project for the launch of the WVR Audio Board Ive been able to not only revive the dream of getting a line-in input working on the sample but also been completely in awe of the number of additional features and possibilites that are now completely feasable. Additionally, Ive significantly improved my coding chops over the last year so putting this all together is now something I am able to actually realize. 

Not putting the cart before the horse or anything, but Ive already been able to successfully transfer a syro stream to the Sample without any hiccups and the built in memory of the WVR allows for saving a huge number of streams on baord that can be loaded in and out on the fly. That alone is pretty nifty but the big boy is recording dicrectly which comes built in with the WVR by default. The only step is building an interface to work with moving recordings around and then compiling them into a new SyroStream which should not be an issue for the processor to handle at all!

Still doing some testing at the moment but everything is pointing towards this being in the homestretch! Thank you so much to https://github.com/marchingband/wvr for this amazing little tool!

# VolcaSample-Live
Project to create a line-in add on for the Korg Volca Sample that can process a recorded bit of audio and output a SyroStream that can be easily sent to the Volca Sample.

#Where things stand
Currently, this all compiles and will play syrostreams aded to an SD card. The stream will always start the update to the VS but fails halfway through. IVe tried multiple cables, adjusting the volume parameter at the #sgtl5000_1.volume(0.4);# parameter (controlled via the audio shield) and can always get the update to about 50% before it fails. The VS is notorious for being extremely finicky with how these updates are transmitted so it requires a near pristine audio signal to be output from the Teensy. Hopefully someone with more experience working with formatting audio signals on the teensy will be able to pinpoint where the culprit is at with the code and suggest a fix for it.
