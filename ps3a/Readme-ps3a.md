# PS4a: CircularBuffer

## Contact
Name: Andrew Allman	
Section: 202
Time to Complete: ~4hr


## Description
This project implements a ring buffer as a queue, and tests its implementation.

### Features
To gain a better understanding of the data type, it was written without taking advantage of algorithms or standard C++ data structures.
It's implementation is an array of template class T, dynamically allocated to a smart pointer to handle deallocation.

### Testing
Exceptions used were:
  -Invalid Argument in the case of constructing a Circular Buffer with an illegal capacity
  -Runtime errors in the case of attempting to peek or dequeue when the buffer was empty
  -Runtime error in the case of attempting to add items to the buffer when the buffer was full
  
Otherwise, checked operation against expected conditions - enqueue successful when appropriate, dequeue values correct, peek value correct. Then performed more operations and double checked.

### Complexity
Time complexity for all operations are O(1), with each function performing either a single constant time operation, or a static procedure of constant time operations.
Space complexity is bound to the size of the buffer, and is O(n).

### Issues
I initially wrote the full implementation as a Circular Stack. It worked great, but I mostly encountered issues there. Writing the queue was pretty straightforward.
Also lint. I fixed all the issues, I'm not sure it looks better. People work really hard to make C++ legible, so no complaints.

### Extra Credit
I had no good idea for a useful lambda function in this case given my implementation. In other languages I generally use lambdas for performing similar operations with 
slight differences in either data types or sort values, or for semi-verbose operations for the sake of readability.

I ended up writing this, and passing that in for the size member function, which handles evaluating the size of the buffer. 
It was already a one line function, but it was the only practical thing I could think of.

auto evalSize = [](size_t head, size_t tail, size_t capacity, bool is_full)
{return is_full ? capacity : (head - tail) % capacity;};


## Acknowledgements
cppreference
Class Notes
Wikipedia: 'Circular buffer'


