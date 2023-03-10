# PS4a: Sokoban

## Contact
Name: Andrew Allman
Section: 202
Time to Complete: ~6.5hr


## Description
Builds a Sokoban game initialized from an input stream.

### Features
Fixes:
- Upon further playthrough, discovered a bug with indexing the matrix. This disrupted some proper crate interaction. The proper changes have been made.
- Clean up garbage from output with extraction operator.
- Removed vscode, autogenerated headstones
- Switched victory theme to royalty free. I like "The Price is Right Theme" a lot, but I have not been in touch with CBS.

Again, I'm not particulary pleased with how this one went. Wish I had started the semester off ahead of the game. Only a projects I've had all the time I wanted to explore the concepts in depth. 

Previous:
The upfront containerizing made interacting with the resources somewhat verbose in some cases. I tried to minimize time complexity,
most of the move logic operations are implemented via switch, with crate information stored in an unordered map, so depending on the compiler, a lot of this should run with constant complexity. Got a bit carried away with the win sequence.

### Algorithm/Data Structures
Used unorded map for crate position information for constant time operations. Uses std::copy for copying contents of ostream to string for initializing string stream. To be forthright, I had already written the entire project and included this as a requirement. It adds no value the way I wrote, in fact it's redundant. I'm sure there were points along the way I could've made better use of the library.

### Issues
Had some difficulty getting a stringstream object to read back into a new sGame object. Again, to be forthright, I didn't figure this one out. I found by converting the string stream data into a string, and initializing a stringstream object with that string, it read back in fine. My guess is either temporary variable issue or null-termination.

Was initially indexing the matrix for crates via the scheme (i * j + n_columns), which should have been (i * n_columns + j). This has been fixed.
I've actually had a number of difficulties with properly indexing mn matrices over the last couple of weeks.

### Extra Credit
Player changes direction when moving.
Plays sound on victory.
Play looks into the direction of last move on victory.
Boxes turn green when set, and can't be removed.
Confetti

## Acknowledgements
Notes
SFML Documentation
CPPReference
@GreenScreenEffect Youtube
Adobe Fonts (SourceCodePro-ExtraLight.ttf)
Victory Theme: "8-bit Paradise ??? kawaii / editing bgm" by nashmusiclibrary


