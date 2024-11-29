#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Maximum number of reservations = 100
const int MAX_RESERVATIONS = 100;
struct Guest {
    string name;
    int roomNumber;
    int duration;
    string checkInDate;
    string checkOutDate;
    double roomRate;
};

// Using a fixed-size array to store reservations
Guest reservations[MAX_RESERVATIONS];
int totalReservations = 0;

// Function to write reservations to a file
void writeToFile() {
    ofstream outFile("reservations.txt");

    if (outFile.is_open()) {
        outFile << totalReservations << endl;

        for (int i = 0; i < totalReservations; ++i) {
            const Guest& guest = reservations[i];
            outFile << guest.name << " "
                    << guest.roomNumber << " "
                    << guest.duration << " "
                    << guest.checkInDate << " "
                    << guest.checkOutDate << " "
                    << guest.roomRate << endl;
        }

        outFile.close();
    } else {
        cout << "Unable to open the file for writing.\n";
    }
}

// Function to read reservations from a file
void readFromFile() {
    ifstream inFile("reservations.txt");

    if (inFile.is_open()) {
        inFile >> totalReservations;

        for (int i = 0; i < totalReservations; ++i) {
            Guest& guest = reservations[i];
            inFile >> guest.name
                   >> guest.roomNumber
                   >> guest.duration
                   >> guest.checkInDate
                   >> guest.checkOutDate
                   >> guest.roomRate;
        }

        inFile.close();
    } else {
        cout << "Unable to open the file for reading. Starting with an empty reservation list.\n";
    }
}

void addGuestReservation() {
    if (totalReservations < MAX_RESERVATIONS) {
        // Add a new guest reservation
        Guest& guest = reservations[totalReservations];
        cout << "Enter Guest Name: ";
        cin >> guest.name;
        cout << "Enter Room Number: ";
        cin >> guest.roomNumber;
        cout << "Enter Duration of Stay (in days): ";
        cin >> guest.duration;
        cout << "Enter Room Rate: ";
        cin >> guest.roomRate;
        cout << "Enter CheckInDate: ";
        cin >> guest.checkInDate;
        cout << "Enter CheckOutDate: ";
        cin >> guest.checkOutDate;

        // Increment the totalReservations count
        totalReservations++;

        // Write reservations to file after adding a new reservation
        writeToFile();

        cout << "Guest Reservation added successfully.\n";
    } else {
        cout << "Cannot add more reservations. Maximum capacity reached.\n";
    }
}

void viewAllGuestReservations() {
    cout << "\nView Reservations\n";
    cout << "------------------\n";

    if (totalReservations == 0) {
        cout << "No reservations available.\n";
        return;
    }

    for (int i = 0; i < totalReservations; ++i) {
        const Guest& guest = reservations[i];
        cout << "Reservation " << i + 1 << "\n";
        cout << "Name: " << guest.name << "\n";
        cout << "Room Number: " << guest.roomNumber << "\n";
        cout << "Check-in Date: " << guest.checkInDate << "\n";
        cout << "Check-out Date: " << guest.checkOutDate << "\n";
        cout << "------------------\n";
    }
}

void searchGuestReservation() {
    string guestName;
    cout << "Enter Guest Name to search: ";
    cin >> guestName;

    for (int i = 0; i < totalReservations; ++i) {
        const Guest& guest = reservations[i];
        if (guest.name == guestName) {
            cout << "Guest Found:\n";
            cout << "Name: " << guest.name << ", Room Number: " << guest.roomNumber
                 << ", Duration: " << guest.duration << " days, Room Rate: Rs" << guest.roomRate << endl;
            return;
        }
    }

    cout << "Guest not found.\n";
}

void updateGuestInformation() {
    string guestName;
    cout << "Enter Guest Name to update information: ";
    cin >> guestName;

    for (int i = 0; i < totalReservations; ++i) {
        Guest& guest = reservations[i];
        if (guest.name == guestName) {
            cout << "Enter updated Room Number: ";
            cin >> guest.roomNumber;
            cout << "Enter updated Duration of Stay (in days): ";
            cin >> guest.duration;
            cout << "Enter updated Room Rate: ";
            cin >> guest.roomRate;
            cout << "Guest information updated successfully.\n";

            // Write reservations to file after updating guest information
            writeToFile();

            return;
        }
    }

    cout << "Guest not found.\n";
}

void checkOutGuest() {
    int roomNumber;
    cout << "Enter Room Number to check-out: ";
    cin >> roomNumber;

    for (int i = 0; i < totalReservations; ++i) {
        Guest& guest = reservations[i];
        if (guest.roomNumber == roomNumber) {
            guest.checkOutDate;
            cout << "\nChecking out Guest...\n";
            cout << "Guest checked-out successfully.....\n";

            // Write reservations to file after checking out
            writeToFile();

            return;
        }
    }

    cout << "No reservation found for Room " << roomNumber << "\n";
}

void calculateTotalBill() {
    string guestName;
    cout << "Enter Guest Name to calculate total bill: ";
    cin >> guestName;

    for (int i = 0; i < totalReservations; ++i) {
        const Guest& guest = reservations[i];
        if (guest.name == guestName) {
            double totalBill = guest.duration * guest.roomRate;
            cout << "Total Bill for " << guest.name << ": Rs" << totalBill << endl;
            return;
        }
    }

    cout << "Guest not found.\n";
}

void viewRoomAvailability() {
    // maximum number of rooms = 100
    const int totalRooms = 100;
    int occupiedRooms = totalReservations;
    int availableRooms = totalRooms - occupiedRooms;

    cout << "Room Availability:\n";
    cout << "Total Rooms: " << totalRooms << endl;
    cout << "Occupied Rooms: " << occupiedRooms << endl;
    cout << "Available Rooms: " << availableRooms << endl;
}

int main() {
    // Read reservations from file at the start of the program
    readFromFile();

    while (true) {
        cout << "\nWELCOME TO HOTEL MANAGEMENT SYSTEM\n";
        cout << "\n";
        cout << "1. Add a Guest Reservation\n";
        cout << "2. View All Guest Reservations\n";
        cout << "3. Search for a Guest Reservation\n";
        cout << "4. Update Guest Information\n";
        cout << "5. Check-out a Guest\n";
        cout << "6. Calculate Total Bill\n";
        cout << "7. View Room Availability\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addGuestReservation();
            break;
        case 2:
            viewAllGuestReservations();
            break;
        case 3:
            searchGuestReservation();
            break;
        case 4:
            updateGuestInformation();
            break;
        case 5:
            checkOutGuest();
            break;
        case 6:
            calculateTotalBill();
            break;
        case 7:
            viewRoomAvailability();
            break;
        case 8:
            // Write reservations to file before exiting the program
            writeToFile();
            cout << "THANK FOR VISITING OUR HOTEL. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
