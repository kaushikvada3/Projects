#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

// hours, minutes, seconds for the timer
int hours = 0;
int minutes = 0;
int seconds = 0;

//to display the timer
void displayClock()
{
    //formatting
    cout << setfill(' ') << setw(55) << "         TIMER         \n";
    cout << setfill(' ') << setw(55) << " --------------------------\n";
    cout << setfill(' ') << setw(29);
    cout << "| " << setfill('0') << setw(2) << hours << " hrs | ";
    cout << setfill('0') << setw(2) << minutes << " min | ";
    cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
    cout << setfill(' ') << setw(55) << " --------------------------\n";
}

void timer()
{
    // loop until the timer reaches 00:00:00
    while (hours > 0 || minutes > 0 || seconds > 0) {

        // display the timer
        displayClock();

        // sleep system call to sleep for 1 second
        sleep(1);

        // decrement seconds
        seconds--;

        // if seconds reaches -1
        if (seconds < 0) {
            // decrement minutes
            minutes--;

            // if minutes reaches -1
            if (minutes < 0) {
                // decrement hours
                hours--;

                // reset minutes to 59
                minutes = 59;
            }
            // reset seconds to 59
            seconds = 59;
        }
    }

    // After the loop, meaning the timer is finished
    cout << "Time's up!\n";
}

void stopwatch(){
    
    
    while (true) {
         
        // display the timer
        displayClock();
 
        // sleep system call to sleep 
        // for 1 second
        sleep(1);
 
        // increment seconds
        seconds++;
 
        // if seconds reaches 60
        if (seconds == 60) {
         
            // increment minutes
            minutes++;
 
            // if minutes reaches 60
            if (minutes == 60) {
         
                // increment hours
                hours++;
                minutes = 0;
            }
            seconds = 0;
        }
    }
}


int main()
{
    string userChoice;
    cout << "Do you want a timer or a stopwatch? Enter 'timer' for a timer and 'stopwatch' for a stopwatch"<<endl;
    cout<< "Enter: ";
    cin >> userChoice;

    if(userChoice == "timer")
    {
        // Input start time for timer
        cout << "Enter the start time for the timer: \n";
        cout << "Hours: ";
        cin >> hours;
        cout << "Minutes: ";
        cin >> minutes;
        cout << "Seconds: ";
        cin >> seconds;

        // Start timer
        timer();
    }
    else if(userChoice == "stopwatch")
    {
        stopwatch();
    }
    
    return 0;
}
