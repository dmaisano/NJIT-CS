/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Extra Credit Project
Due by 8/08/17
*/

#include <iomanip> // included to set the precision for the percent float
#include <iostream>
using namespace std;

int main() {
  int numFloors, totalRooms = 0, totalOccupied = 0, totalUnoccupied = 0;
  float percent = 0.0f; // percentage must be a float as an int value will not work

  cout << "Enter the number of floors in the hotel: ";
  cin >> numFloors;

  while (numFloors < 1) { // input validation for number of floors
    cout << "Number of floors cannot be less than one.\nEnter the number of "
            "floors in the hotel: ";
    cin >> numFloors;
  }

  int numRooms[numFloors];
  int roomsOccupied[numFloors];

  for (int i = 0; i < numFloors; i++) {
    if (i == 0) { // display a message to the user to prevent input error
      cout << "(Number of rooms must be at least 10)\n";
    }

    if (i == 12) { // if there is a 13th floor, skip it
      numRooms[i] = 0;
      roomsOccupied[i] = 0;
      continue;
    }

    cout << "Enter the number of rooms on floor " << i + 1 << ": ";
    cin >> numRooms[i];

    while (numRooms[i] < 10) { // input validation for number of rooms on floor
      cout << "(Number of rooms must be at least 10)\nEnter the number of "
              "rooms on floor "
           << i + 1 << ": ";
      cin >> numRooms[i];
    }

    cout << "How many rooms are occupied on floor " << i + 1 << ": ";
    cin >> roomsOccupied[i];
  }

  for (int x = 0; x < numFloors; x++) {
    totalRooms += numRooms[x]; // add the number of rooms on floor 'n' to the totalRooms

    totalOccupied += roomsOccupied[x]; // add the number of occupied rooms on
                                       // floor 'n' to the totalOccupied

    totalUnoccupied += (numRooms[x] - roomsOccupied[x]); // add the number of unoccupied rooms
                                                         // on floor 'n' to the totalUnoccupied
  }

  // totalOccupied * 1.0f basically converts 'totalOccupied' to a float
  // so that it may be used in the calculation
  percent = (totalOccupied * 1.0f / totalRooms) * 100.0f;

  cout << "\n\nTotal number of rooms: " << totalRooms;
  cout << "\nTotal number of occupied rooms: " << totalOccupied;
  cout << "\nTotal number of unoccupied rooms: " << totalUnoccupied;
  cout << "\nPercentage of occupied rooms: " << setprecision(2) << fixed << percent
       << "%"; // set max decimal places to 2

  return 0;
}
