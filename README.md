# VolcaSample-Live
Project to create a line-in add on for the Korg Volca Sample that can process a recorded bit of audio and output a SyroStream that can be easily sent to the Volca Sample.

#Where things stand
Currently, this all compiles and will play syrostreams aded to an SD card. The stream will always start the update to the VS but fails halfway through. IVe tried multiple cables, adjusting the volume parameter at the #sgtl5000_1.volume(0.4);# parameter (controlled via the audio shield) and can always get the update to about 50% before it fails. The VS is notorious for being extremely finicky with how these updates are transmitted so it requires a near pristine audio signal to be output from the Teensy. Hopefully someone with more experience working with formatting audio signals on the teensy will be able to pinpoint where the culprit is at with the code and suggest a fix for it.
