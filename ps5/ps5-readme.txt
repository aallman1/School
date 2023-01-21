/**********************************************************************
 *  readme 
 *  DNA Sequence Alignment
 **********************************************************************/

Name: Andrew Allman

Hours to complete assignment: ~3 hrs

/**********************************************************************
 * Explain which approach you decided to use when implementing
 * (either recursive with memoization, recursive without memoization,
 * dynamic programming or Hirschberg’s algorithm). Also describe why
 * you chose this approach and what its pros and cons are.
 **********************************************************************/
Went with dynamic programming with an mxn table. The solution for edit
distance was familiar to me, and I had done some work in the past 
trying to optimize a solution using fewer values.
Unfortunately, I didn't have the time to pursue similar optimizations
in this project.

Data structure used is a matrix class, which is an integer array, 
indexable with (i, j) values for convenience.

The pros of this approach is absolute accuracy, considers all the values
and charts a verifiably optimal course. The downside is the massive
space complexity with large inputs.

/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input: 
atattat
tattata

Expected output:
- a 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
a - 2

What happened:
Worked as expected. 
Output:

- a 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
a - 2


/**********************************************************************
 * Look at your computer’s specs in the settings. 
 * How much RAM does your computer have and explain what this means? 
 **********************************************************************/
CPU Speed: max 3600 mHZ, min 2200 mHZ

Operating System: 5.15.0-52-generic #58-Ubuntu SMP Thu Oct 13 08:03:55 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux

CPU Type: AMD Ryzen 5 2600X Six-Core Processor

My Computer has 16.7GB of RAM. RAM is used for immediate storage of information
to be utilized in a task being performed within an active process. RAM can 
be addressed very quickly and stored information can be retrieved and written
at a similar rate independent of its location. 
RAM is typically used by applications to read and write session-relevant information.
As such, I have 16.7GB of this kind of storage in my computer.


/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
a = 4
b = 2
largest N = 44721

If an integer is equal to 4 bytes and M = N, representing both strings are the 
same size, the resulting matrix will size N * N, yielding N^2 integers.

With a maximum size of 8,000,000,000, this can hold 2,000,000,000 ints.
As such, N * N must be less than or equal to 2,000,000,000. The square
root of 2,000,000,000 is equal to 44721.35955. We must take the floor
of this value to accomodate all the integers, and as such the the largest
N = 44721.

/**********************************************************************
 * Run valgrind if you can and attach the output file to your submission. 
 * If you cannot run it, explain why, and list all errors you’re seeing. 
 * If you can run it successfully, does the memory usage nearly match that 
 * found in the question above? 
 * Explain why or why not. 
/**********************************************************************
The memory usage does nearly match. For the case of 'ecoli5000.txt'
I'm showing a maximum, total heap size of 100,142,184B.

If we consider the majority of the memory usage should represent the 
stored integer values, we should divide by the string length squared,
and the result should look like the the approximate size of an integer.

As such 100,142,184 / (5,000 * 5,000) = 4.00568736 

And we can confirm the memory usage reflects our expected value.


/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt         118             0.510257          25.113048
ecoli5000.txt         160             1.99029           100.142184
ecoli7000.txt         194             3.84758           196.166392
ecoli10000.txt        223             7.81056           400.209528
ecoli20000.txt        3135            31.8306           1600.343192      
ecoli28284.txt        8394            63.8418           3200.363832

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730



/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
a = 8 * 10^-8
b = 2
largest N = 1040000

 8 * 10^-8 * x^2 = 86400
 8x^2 = 86400 * 10^8
 x^2 = (86400 * 10^8) / 8
 x < 1040000


/
**********************************************************************
 *  Did you use the lambda expression in your assignment? If yes, where 
 * (describe a method or provide a lines numbers)
 **********************************************************************/
Yes, quality of life lambda that formats a line for the return string
from Alignment(). It is a function pointer in the class 
definition (Matrix.hpp - 18:19), and it is defined and passed as a lambda
in Main.cpp (23:30).


**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/
 Reviewed edit distance in Algorithms a few weeks ago. Otherwise,
 just the assignment pdf.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
Had trouble passing the lambda for a bit. Otherwise, some difficulty with
the alignment logic, everything seems to work. Optimization flags did not 
seem to make a difference.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
I wish I had made more time for this one. There are a few variations of
edit distance that seem promising in this scenario.


/**********************************************************************
 * IMPLEMENTED MIN vs. STD::MIN (time comparisons)                                  
 **********************************************************************/
 Format of min(int, int, int)
 Format of std::min({int, int, int})

 Performance:

data file            min time (seconds)    std::min time (second)
------------------------------------------------------------------
ecoli2500.txt        0.510257          0.659435
ecoli5000.txt        1.99029           2.53946
ecoli7000.txt        3.84758           4.96165
ecoli10000.txt       7.81056           9.99467
ecoli20000.txt       31.8306           40.2334      
ecoli28284.txt       63.8418           80.7366

Per the trials, it seems like the implemented min function outperforms
the std::min function, and take about 1.3 times as long.
This may be due list initialization.