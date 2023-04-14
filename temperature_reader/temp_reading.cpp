#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <algorithm> // For sorting
#include <cstring> // For memset
#include <fstream> // For file writing
// For shared mmemory object
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

mutex m;

void generateTemperature(float* temp)
{
    while(1) 
    {
        float decimal = (float) rand() / RAND_MAX;  // A random decimal [0,1]
        *temp = (decimal * 170 ) -100; // Arandom temeprature [-100,70]
        this_thread::sleep_for(chrono::minutes(1)); // Waits 1 minute between readings
        //this_thread::sleep_for(chrono::milliseconds(100)); // Testing on 100 milliseconds
    }
}

void logTemperatures(float* temps, int n, int hour)
{
    char timestamp[100];
    float diff = 0;
    float max_diff = 0;
    int max_diff_start = 0, max_diff_end = 0;

    vector<float> temp_tracker(temps, temps + n);
    sort(temp_tracker.begin(), temp_tracker.end()); // Sets the temps in order
    vector<float> highest(temp_tracker.end() - 5, temp_tracker.end()); // Stores 5 highest temps
    vector<float> lowest(temp_tracker.begin(), temp_tracker.begin() + 5); // Stores 5 lowest temps

    for (int i = 0; i < n - 1; i++)
    {
        diff = abs(temps[i+1] - temps[i]);
        if (diff > max_diff)
        {
            max_diff = diff;
            max_diff_start = i;
        }
    }
    max_diff_end = max_diff_start + 1;

    // Write the output to a text file
    ofstream outfile;
    outfile.open("temp_reading_log.txt", ios::app); // Opens the file in append mode

    cout << "Hour " << hour << endl;
    outfile << "Hour " << hour << endl;

    cout << "Top 5 highest temperatures: ";
    outfile << "Top 5 highest temperatures: ";
    for (float temp : highest)
    {
        cout << temp << ", ";
        outfile << temp << ", ";
    }

    cout << "\nTop 5 lowest temperatures: ";
    outfile << "\nTop 5 lowest temperatures: ";
    for (float temp : lowest)
    {
        cout << temp << ", ";
        outfile << temp << ", ";
    }
    cout << "\nThe largest temperature difference: " << max_diff << "F occurs between the indices " << max_diff_start << " and " << max_diff_end << endl;
    outfile << "\nThe largest temperature difference: " << max_diff << "F occurs between the indices " << max_diff_start << " and " << max_diff_end << endl;
}

int main()
{
    srand(time(nullptr)); // Random seed initialization
    int n = 100; // Number of readings done by each thread
    int time_tracker = 1;
    thread threads[8]; // Using 8 threads
    
    // Creates a shared memory object to store the temperatures
    int shm_fd = shm_open("/temp_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(float) * 1000); // Sets the size
    float* shared_memory = (float*) mmap(NULL, sizeof(float) * 1000, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    // Sets the default values of every temperature to 0
    memset(shared_memory, 0, sizeof(float) * 1000);
    
    // Each thread generates n random temperatures
    for (int i = 0; i < 8; i++)
        threads[i] = thread(generateTemperature, &shared_memory[i*n]);

    while(1)
    {
        this_thread::sleep_for(chrono::minutes(60)); // Waits for 1 hour
        //this_thread::sleep_for(chrono::minutes(1)); // Testing on 1 minute
        m.lock(); // Stop concurrent shared memeory access
        logTemperatures(shared_memory, 1000, time_tracker); // Records the temperatures for this minute
        memset(shared_memory, 0, sizeof(float) * 1000); // Resets the temperatures
        m.unlock();

        time_tracker++;
        if (time_tracker > 24) // Stops after 24 hours
            break;
    }
    for (int i = 0; i < 8; i++)
        threads[i].join();

    munmap(shared_memory, sizeof(float) * 1000); // Frees the shared memory mapping
    shm_unlink("/temp_shm"); // Frees the shared memory object

    return 0;
}
