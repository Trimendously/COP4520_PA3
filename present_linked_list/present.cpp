#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>

using namespace std;


int thank_counter = 0;
int presents_processed = 0;
class Present
{
public:
    int id;
    Present* next;

    Present(int value) 
    {
        id = value;
        next = NULL;
    }
};

class LinkedList 
{
public:
    Present* head;

    LinkedList() 
    {
        head = NULL;
    }

    void addPresent(int value) 
    {
        Present* newPresent = new Present(value);
        if (head == NULL) 
            head = newPresent;
        
        else 
        {
            Present* current = head;
            while (current->next != NULL) 
                current = current->next;
            
            current->next = newPresent;
        }
    }

    void printList() 
    {
        Present* current = head;
        while (current != NULL) 
        {
            cout << current->id << " ";
            current = current->next;
        }
        cout << endl;
    }

    void deletePresent(int value) 
    {
        if (head == NULL) 
            return;
        
        if (head->id == value) 
        {
            Present* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Present* current = head;
        while (current->next != NULL && current->next->id != value) 
            current = current->next;
        

        if (current->next == NULL) 
            return;
        

        Present* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    bool contains(int value)
    {
        Present* current = head;
        while (current != NULL) 
        {
            if (current->id == value) 
                return true;
          
            current = current->next;
        }
        return false;
    }
    bool empty() {
        return head == nullptr;
    }
};


vector<int> generateIds(int n) 
{
    vector<int> ids(n);
    for (int i = 0; i < n; i++)
        ids[i] = i + 1;

    return ids;
}


// Function to generate a random integer between min and max (inclusive)
int getRandomInt(int min, int max) 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void presentsTask(LinkedList& list, vector<int>& ids) 
{
    while (1) 
    {
        // Random action by servant
        int operation = getRandomInt(0, 2);
        switch (operation) 
        {
            // Add present
            case 0: 
            {
                int index = getRandomInt(0, ids.size()-1); // Want random selection but has repeats now
                int presentId = ids[index];
                list.addPresent(presentId);
                break;
            }
            // Delete Present
            case 1: {
                if (!list.empty()) {
                    int index = getRandomInt(0, ids.size()-1);
                    int presentId = ids[index];
                    cout << "Thank you " << presentId << endl;
                    list.deletePresent(presentId);
                    

                }
                break;
            }
            // Check if contains present
            case 2: 
            {
                if (!list.empty()) {
                    int index = getRandomInt(0, ids.size()-1);
                    int presentId = ids[index];
                    bool presentExists = list.contains(presentId);
                    if (presentExists) {
                        cout << "Present " << presentId << " is present" << endl;
                    } else {
                        cout << "Present " << presentId << " is not present" << endl;
                    }
                }
                break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(getRandomInt(100, 1000)));
    }
}

int main() 
{
    int num_presents = 10;
    LinkedList myList;
    vector<int> ids = generateIds(num_presents);

    vector<thread> threads(4);
    for (int i = 0; i < threads.size(); i++) {
        threads[i] = thread(presentsTask, ref(myList),ref(ids));
    }
    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    return 0;
}
