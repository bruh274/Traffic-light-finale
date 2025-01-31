#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <exception>

using namespace std;

mutex mtx;

const int numberOfRoads = 8;
const int greenTime = 6;
const int yellowTime = 4;


void displayLights(int currentGreenRoad, const string& phase) {
    lock_guard<mutex> lock(mtx);
    
    system("CLS");
    
    try {
        
        if (currentGreenRoad < 0 || currentGreenRoad >= numberOfRoads) {
            throw out_of_range("Error: currentGreenRoad index out of bounds!");
        }

        cout << "Current light " << phase << ": road " << currentGreenRoad + 1 
             << " & " << ((currentGreenRoad + 1) % numberOfRoads) + 1 << endl;

        for (int r = 0; r < numberOfRoads; ++r) {
            if (r == currentGreenRoad || r == (currentGreenRoad + 1) % numberOfRoads) {
                cout << "road " << r + 1 << ": " << phase << endl;
            } else {
                cout << "road " << r + 1 << ": RED" << endl;
            }
        }
        cout << "===" << endl;

    } catch (const exception& e) {
        cerr << "Exception caught in displayLights(): " << e.what() << endl;
    }
}


void trafficLightSystem() {
    int currentGreenRoad = 0;

    try {
        while (true) {
            if (greenTime <= 0 || yellowTime <= 0) {
                throw invalid_argument("Error: Light durations must be positive values.");
            }

            displayLights(currentGreenRoad, "GREEN");
            this_thread::sleep_for(chrono::seconds(greenTime));

            displayLights(currentGreenRoad, "YELLOW");
            this_thread::sleep_for(chrono::seconds(yellowTime));

            currentGreenRoad = (currentGreenRoad + 2) % numberOfRoads;
        }

    } catch (const exception& e) {
        cerr << "Exception caught in trafficLightSystem(): " << e.what() << endl;
    }
}


int main() {
    try {
        if (numberOfRoads < 2) {
            throw invalid_argument("Error: The number of roads must be at least 2.");
        }

        thread trafficThread(trafficLightSystem);
        trafficThread.join();

    } catch (const exception& e) {
        cerr << "Exception caught in main(): " << e.what() << endl;
    }

    return 0;
}

