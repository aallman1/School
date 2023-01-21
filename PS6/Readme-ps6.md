# PS6: RandWriter

## Contact
Name: Andrew Allman
Section: 202
Time to Complete: ~5.5hr


## Description
This project ingests a corpus from which to generate random text in the given style.

### Features
Had a difficult time deciding on data structures. Before I fully understood what the implementation
would be per the instructions, I started capturing frequency of all phrases <= k, assigning them to vectors of
maps, then vectors of sorted vectors. When I realized the look-ahead / string-building process baked in the 
markovian probability, the rest was smooth.

Implementation was a bit heavy handed - generating an ascii table for every ingested k-gram will all 127 items per
kgram. This wastes quite a lot of space, and I planned on going back for it, but have run out of time.

The data structure I implemented was a unordered_map with a string key, and a vector<pair<char, int>> value. The vector
is the symbol table that represents frequencies of letter adjacent to the key. I wasted a lot of time trying to 
define a custom comparator for a different data structure that was an unordered_map<string, map<char, int>> that would act like a heap, but there seems like there is no good way to do this to get a map to order by value. As such, I defined a custom
sort that would sort the vectors by frequency. The cost is greater up-front time for ingestion, but relatively fast generation of text, using constant time lookup for the phrase and iterating through the sorted vector, subtracting off sequential frequencies.

Definitely could be far more performant for ingestion, but in practice, I think it made sense to focus on performant generation of text.

### Testing

  BOOST_REQUIRE_NO_THROW(RandWriter(buffer.str(), 10)); // tests valid initialization
  RandWriter rw(buffer.str(), 0); 
  BOOST_REQUIRE_EQUAL(rw.orderK(), 0); // tests orderK accuracy
  BOOST_REQUIRE_GT(rw.freq("", ' '), rw.freq("", 'e')); // test general frequency of chars by comparison
  BOOST_REQUIRE_GT(rw.freq(""), 380000); // tests general total frequency of ingested chars (real number is closer to 385K)
  BOOST_REQUIRE_NO_THROW(rw.kRand("")); //  confirms 0-order kRand throws no errors 
  BOOST_REQUIRE_NO_THROW(rw.generate("", 0)); // confirms 0-order generate throws no erro
  BOOST_REQUIRE_THROW(rw.generate("I", 10), std::runtime_error); // tests exception thrown when provided string != k

### Lambda
I used a couple lambdas, mainly passing to algorithm functions:

// simple one for sorting vectors of pairs by frequency
sort((*itm.second).begin(), (*itm.second).end(), [](
            pair<char, int> a, pair<char, int> b) {
            return a.second > b.second;

// another simple lambda for summing up total frequency of a kgram
return std::accumulate((*SymbolTableMap.at(kgram)).begin(),
    (*SymbolTableMap.at(kgram)).end(), 0, [](
        int sum, pair<char, int> a) { return sum + a.second; });        

### Issues
I admit I had some trouble understanding the concept at first. At first I tried to build it without the assignment
instructions, experimenting with different data structures and implementations, based on the premise that I would
collect frequencies on every string <= k in the corpus, then build the L-sized string starting with one random character
using frequency for 1-grams to build a 2-gram, so on and so forth. 

Also, initially had some trouble with 0-order grams. Had to do with template argument in random device.
Also, had some trouble generating text if the corpus included ascii values outside of range(0, 127), so the the TextWriter
omits any delimited words containing illegal characters. 

All seems good now with the somewhat prescribed implementation. 

### Extra Credit
This may be the only project I submitted without the optional extra-credit. Turning it in, it feels a bit short. I may 
write about a word based implementation in the Portfolio.

## Acknowledgements
-Assignment PDF
-Class Slides
-Stack Overflow for the map ordering by value inquisition & file ops (https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring)