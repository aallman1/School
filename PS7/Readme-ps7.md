# PS7: Kronos Log Parsing

## Contact
Name: Andrew Allman
Section: 202
Time to Complete: ~8hr


## Description
This application parses log information from Kronos devices - analyizing startup times/successes and services.

### Features
The program uses two class objects, one to represent a boot sequence, and another to represent a service object. The bootsequences
for a file are stored in a vector, and are built carrying a map of service objects. The bootsequence stores the bootsequence information (dates,
times, successful, linenumbers etc), and the service objects store the the service object information (elapsed, linenumbers, etc).

I do know there would be more performant ways to implement this - the file could be created while the other one was read, only chunks
of info need be known at a given time.

Performance of this implementation makes it so the file only need be read once, but lines will be searched several times while building the
object. Performance will resemble linear with n operations for all lines, m operations for server specific lines, and k operations for service specific
lines.

### Approach
Initially, getting my bearings in regex/data parsing in C++, wanted to identify schemes comprehensive enough to identify the correct lines
without being too strict as to omit target lines/phrases. After that, building the service analysis came with noticing a complete boot
would be signaled before the last service had signaled completion, so the logic needed to be changed. The structure is essentially, 
1. Identify when a boot attempt occured.
2. Capture all service relevant lines inbetween in vectors.
3. Transition the data to class objects once a new attempt occurs, record success or failure based on appearance of 'AbstractConnector' line.

From there, there was some basic logic included in outputting to the files - with the exception of device4, which I'll speak to in issues.

### Regex

The boost library version of Regex was used, as per the example file. I did substitute out boost with standard library, and performance was
much slower, so I switched back to boost.

const regex INIT_BOOT_RS("\\(log\\.c\\.[0-9]+\\) server started"); -> search phrase used to id server start attempt
const regex COMP_BOOT_RS("AbstractConnector:Started SelectChannelConnector@0\\.0\\.0\\.0:9080"); -> search phrase used to id server boot completion

const regex INIT_SERVICE_RS("Starting Service\\.  [a-zA-Z]+ [0-9]*\\.[0-9]+"); -> search phrase used to id service start
const regex COMP_SERVICE_RS("Service started successfully."); -> very explicity search phrase used to id service start success
const regex DATE_FRM_RS("[0-9]{4}-[0-9]{2}-[0-9]{2}"); -> search phrase used to id date substrings
const regex TIME_FRM_RS("[0-9]{2}:[0-9]{2}:[0-9]{2}(\\.[0-9]{1,3})?"); ->search phrase used to id time substrings
const regex ALPHA_STRING("[a-zA-Z]+"); -> search phrase used to id alphabetical substrings
const regex MS_FRM_NUMBER_RS("\\([0-9]+"); -> search phrase used to id numerical substrings in the context of milliseconds elapsed for services

### Issues
There were the general difficulties of building a project. I spent about 2 hours trying to identify why dynamic allocation of BootSequence objects
triggered segmentation error, turns out there were old build files using different data structures being used in the build. Upon deletion things went 
according to plan.

Additionally, I wrote the program according to the results given with device5_intouch.log_BOOT.rpt, and unfortunately, immediately moved on
to prepping my code for export, which makes it somewhat costly to change / debug. Upon testing device4, I recieved an segmentation error when 
attempting to index a specific service which wasn't contained in the service map, meaning it did not get added either in the file or by the logic.
I did exhaustively investigate this, since successful startup logic seems to produce quality reports for all other files, so my theory was exceptions
for these programs were occuring, but they did not prevent successful startup. As such, the not-so-super-tight patch for this was to identify when
expected services did not start correctly (either by identifying when no success line occurred, or when the service was not present between server boot signals),
and record them in services not successfully started. 

It may be the case this is the proper way to handle these exceptions, but I cannot say that with confidence because I do not fully understand these exceptions.

In either case, they are handled, and no faulty service detail information should exist.

### Extra Credit
Implemented to the specifications of the device5_intouch.log_BOOT.rpt example.

This includes:
1. Summary header
2. Boot process information for services

## Acknowledgements
https://stackoverflow.com/questions/56209611/c11-how-to-use-accumulate-lambda-function-to-calculate-the-sum-of-all-sizes (refresher)
https://www.boost.org/doc/libs/1_35_0/doc/html/date_time/date_time_io.html#date_time.format_flags
https://cplusplus.com/reference/ios/ios/imbue/
notes from class


## Note
Output files are stored in the reports directory