temp_reading.cpp Instructions to Run


The atmospheric temperature reading module uses 8 sensors (8 threads) collect temperature readings at regular intervals and store them in shared memory space

Each thread will generate a random temeperature (between -100F to 70F) for every reading (will hard code to perform n readings)

Each reading will occur every minute


At the end of every hour the following are logged:
    -top 5 highest temperatures for that hour
    -top 5 lowest temperatures for that hour
    -the 10 minute interval when the largest temperature difference was observed




To run this program first make sure that you have a C++ compiler installed.
Here is a guide that should help to do so: https://www.ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html

Next open up the command prompt and navigate to the folder / directory you downloaded the file into 
and type in, or just copy and paste:
g++ -o temp_reading temp_reading.cpp
and then press enter.

This compiles the program so that you may now run it.

To run it simply type
./temp_reading
and then press enter once again.

After that the program should run and within the same folder/ directory that you are in a new temp_reading_log.txt file should be made storing the following:

    -top 5 highest temperatures for that hour
    -top 5 lowest temperatures for that hour
    -the 10 minute interval when the largest temperature difference was observed and the difference itself

Additionally as the program writes to the .txt file it should also print to the console