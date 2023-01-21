# PS4a: Sokoban

## Contact
Name: Andrew Allman
Section: 202
Time to Complete: ~4hr


## Description
Builds the UI of a Sokoban game.

### Features
Tried to make everything as convenient as possible to write down the road. All the textures and sprites are containerized, with global const index values.
The positions for all thestatic textures are set up front. Will have to modify the crate logic so it can be adjusted freely.

### Memory
The data is stored as characters in an nxm matrix structure based on the class written in class. This makes it easy to write out to a stream.

### Lambdas
Uses a lambda for formatting the elapsed time string.

### Issues
Makefile. Spent about an hour dealing with redefinition error. The problem is I get frustrated and stop thinking clearly. This will get better with time.
Also, same linting issue as last time, where if include the header file for it's corresponding .cpp, it tells me to include directory, but when I do, it says it shouldn't be relative.
I don't see another option besides providing the system path in this case, so I'm not going to do it. If you actually read this README, can you tell me what this is about?

### Extra Credit
Implemented elapsed time.


## Acknowledgements
Notes
SFML Documentation
Adobe Fonts (SourceCodePro-ExtraLight.ttf)
