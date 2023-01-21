# PS3b: StringSound

## Contact
Name: Andrew Allman
Section: 202
Time to Complete: 12+ hrs


## Description
The program builds a dual-oscillator FM synthesizer, and also implements the guitar voicing.

### Features
The knobs only work for the synthesizer, so you'll have to hit the hastily drawn Inst switch to use them.

MASTER PITCH: Adjusts the frequency of both oscillators, but not the modulating frequency.
OSC I GAIN: Adjusts the amplitude of OSC I, works similar, but because it's voltage, it is a tonal effect.
MOD FREQ: Adjusts the frequency of the modulating oscillator.
MOD GAIN: Adjusts the modulating oscillator amplitude.
OSC II GAIN: Adjusts the OSC II amplitude.
OSC II PITCH: Adjusts the OSC II pitch, independent of OSC I. Good for harmonies, dischord, and small chorus effects.
DECAY: Adjusts the decay rate of the note.

### Testing
Runtime errors on the circle buffer.
Invalid argument exceptions on the constructors.
I wasn't sure how to test a sample value, given I was feeding in random values for the start. I supposed I could have figured out a range for the persisting values to check against,
but I checked to make sure it contained a realistic value when it should.
Checked the time after an iteration of ticks.


### Lambda
Same lambda from the ps3a, handles returning a size calculation for the Circular buffer. Tested in test.

### Issues
I had trouble with lint. I wrote a lot of code in a relatively short amount of time - then spent nearly 5 hours on Makefile compiling and lint combined. Makefile I'm okay with,
but in the end, after removing about 400 linting issues, I'm left with 3. This issue is, if you're including the header file that belongs to the cpp (of the same name), you're not supposed to use
relative file paths. If I omit the './' from the file path, it says I should specify the directory. The only alternative I see is the system path, but that doesn't seem very helpful for 
portability. Otherwise, having to fix line length issues in nested bodies is actually damaging my ability to read the code.

I had a lot of fun building this. I researched audio synthesis, derived my mod oscillator formulas from a 1970s paper out of stanford, and some of the other fx from wiki entries.
I was looking forward to implementing post-fx like reverb and chorus, potentially envelopes but alas, time had already run thin.

Some thought had to go into how to make the notes sustain, so they persisted on a new key stroke, as your changing the dials. Building 37 vectors wasn't feasible, so I created a circular buffer 
of dynamically allocated sf::Sound/sf::Sound buffer pairs to delete once the queue was full. They're all deleted at close of the program.

### Extra Credit
I made a powerful but small digital synthesizer. I could have made a chirp noise and turned the project in a day ago with extra credit. Dr Daly said no extra time, so I've pulled an all nighter
to give you 75% of what I wanted for my implementation, likely with a late penalty. Speaking of which, please don't deduct lateness points.

Hit the switch to toggle instruments.

## Acknowledgements
cppreference
"The Synthesis of Complex Audio Spectra
by Means of Frequency Modulation" - JOHN M. CHOWNING
wikipedia
notes
