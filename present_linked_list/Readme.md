present.cpp Instructions to Run

Generate a collection of presents (each with a unique tag number) 

Goal is to add each present to a linked list by increasing id order

Using 4 threads
they do one of the three following actions (in no particular order):
    -pick a random element and add it to the correct spot in the linked list
    make sure that this element is linbked to the next eleemnt in the list
    -Print out 'thank you : ', print the id number, and remove the present from the list making sure to connect the predecessor with the next element
    -Check whether a certain id is in the linked list and print 'Present # is present' *puns*

Each thread is to not wait on one another to add presents to the linked list and write the 'thank you'

Run until all presents were added to the linked lsit and the linked list is empty

To run this program first make sure that you have a C++ compiler installed.
Here is a guide that should help to do so: https://www.ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html

Next open up the command prompt and navigate to the folder / directory you downloaded the file into 
and type in, or just copy and paste:
g++ -o present present.cpp
and then press enter.

This compiles the program so that you may now run it.

To run it simply type
./present
and then press enter once again.

After that the program should run and within the same folder/ directory that you are in a new temp_reading_log.txt file should be made storing the following:

    -top 5 highest temperatures for that hour
    -top 5 lowest temperatures for that hour
    -the 10 minute interval when the largest temperature difference was observed and the difference itself

Additionally as the program writes to the .txt file it should also print to the console