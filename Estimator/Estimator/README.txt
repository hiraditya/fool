This program can be used to estimate the coordinates of a person
when sample guesses have been provided.

A. PRE-CONDITIONS:

1. A file guesses.txt which has the estimated coordinates
to be provided in JSON format. Although the program only understands
the sample format, sufficient facilities have been provided
to extend it, or to read an entirely different format.
One particular implementation has been provided due to which 
each file should conform to the same format as provided in the sample.

2. Qt,qwt includes and libraries should be in the path 
  --the Estimator.pro file can be modified accordingly

3. jsoncpp includes and libraries should be in the path 
  --the Estimator.pro file can be modified accordingly

4. g++ compiler with support for C++11, in particular g++ > 4.6 will
work.

5. Boost header files (boost/lexical_cast.hpp) should be in the 
include path.

B. HOW TO COMPILE:

* Please read the Estimator.pro file and modify the 
include paths as per your requirement.

* Build and run the project from Qt Creator IDE 
or
* run qmake to generate Makefile
  and then run make
  and then ./Estimator
or
* modify Makefile to set the include-path and 
libraries
run make
then ./Estimator

C. DESIGN CHOICE:
Basically the class layout is following:
1. Estimator(virtual) and other derived classes
which implement specific algorithms for estimating the cordinates.
2. The Serialize_Coordinate class which is specialization of the
IJsonSerializable(to provide uniform interface to other formats)

The main.cpp file is the entry point, which contains the main function.
It instantiates the Serialize_Coordinate class and 
gets the coordinates parsed into a vector of complex numbers.

I chose complex number to represent a point in the plane,
because it is widely used to do so.

Then the main program calls a helper function to estimate the 
location of the person using a particular algorithm.
The choice of algorithm can be changes by modifying the 
estimate() function. 

Then the main function plots all the estimates in red and the
expected location in black.

Advantages of my design choice:
1. The JSON parser is fully extensible and customizable.
2. The Estimator class can be extended to use any algorithm
3. The plotting is solely handled in main which can be 
gotten rid of to to add another plot utility.

Brittle variables in my design:
1. The filename of input-json-formatted-file is 
specified in the main function. It could have been passed 
from the commandline or from a pop-up menu
2. At a number of places in the main function I have used the 
raw numbers.


D. OUTPUT:
After running the project you'll get a graph,
where the red-colored dots are the guess-coordinates
and the thick-black dot will be the expected location of 
the person. 

A sample output file has been attached in the project directory.

E. ALGORITHM:
Althouth the Estimator class is extensible to provide implementations
for different algorithms, I have implemented a simple method
which just outputs the means of all the guesses.

(X',Y') = (sum(x)/total_points,sum(y)/total_points)

