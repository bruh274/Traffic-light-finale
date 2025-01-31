#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>

using namespace std;

mutex mtx;

const int numberOfRoads = 8;
const int greenTime = 6;
const int yellowTime = 4;

void displayLights(int currentGreenRoad, const string& phase) {
    lock_guard<mutex> lock(mtx);
    
    system("CLS"); // Clear the screen
    cout << "Current light " << phase << ": road " << currentGreenRoad + 1 
         << " & " << ((currentGreenRoad + 1) % numberOfRoads) + 1 << endl;

    for (int r = 0; r < numberOfRoads; ++r) {
        if (r == currentGreenRoad || r == (currentGreenRoad + 1) % numberOfRoads) {
            cout << "road " << r + 1 << ": " << phase << endl;
        } else {
            cout << "raod " << r + 1 << ": RED" << endl;
        }
    }
    cout << "===" << endl;
}

void trafficLightSystem() {
    int currentGreenRoad = 0;

    while (true) {
        // GREEN phase
        displayLights(currentGreenRoad, "GREEN");
        this_thread::sleep_for(chrono::seconds(greenTime));

        // YELLOW phase
        displayLights(currentGreenRoad, "YELLOW");
        this_thread::sleep_for(chrono::seconds(yellowTime));

        // Move to the next pair of quadrants
        currentGreenRoad = (currentGreenRoad + 2) % numberOfRoads;
    }
}

int main() {
    thread trafficThread(trafficLightSystem);
    trafficThread.join();
    return 0;
}

