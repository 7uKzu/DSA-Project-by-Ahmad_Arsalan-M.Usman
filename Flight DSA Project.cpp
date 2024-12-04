#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class Stack {
private:
    string data[100];
    int top;

public:
    Stack() : top(-1) {}

    void push(string value) {
        if (top >= 99) {
            cout << "\t\t\t\t\t\tStack Overflow.\n";
            return;
        }
        data[++top] = value;
    }

    string pop() {
        if (top < 0) {
            cout << "\t\t\t\t\t\tStack Underflow.\n";
            return "\t\t\t\t\t\t";
        }
        return data[top--];
    }

    string peek() {
        if (top < 0) {
            return "\t\t\t\t\t\t";
        }
        return data[top];
    }

    bool isEmpty() {
        return top < 0;
    }
};

class Queue {
private:
    string data[100];
    int front, rear, size;

public:
    Queue() : front(0), rear(0), size(0) {}

    void enqueue(string value) {
        if (size == 100) {
            cout << "\t\t\t\t\t\tQueue Overflow.\n";
            return;
        }
        data[rear] = value;
        rear = (rear + 1) % 100;
        size++;
    }

    string dequeue() {
        if (size == 0) {
            cout << "\t\t\t\t\t\tQueue Underflow.\n";
            return "";
        }
        string value = data[front];
        front = (front + 1) % 100;
        size--;
        return value;
    }

    bool isEmpty() {
        return size == 0;
    }
};

struct Flight {
    string flightID;
    string destination;
    int seatsAvailable;
    Flight* next;
};

Flight* head = NULL;
Stack bookingStack;
Queue notificationQueue;

void addFlight(string id, string destination, int seats) {
    Flight* newFlight = new Flight();
    newFlight->flightID = id;
    newFlight->destination = destination;
    newFlight->seatsAvailable = seats;
    newFlight->next = NULL;

    if (head == NULL) {
        head = newFlight;
    } else {
        Flight* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newFlight;
    }
    notificationQueue.enqueue("New flight added: " + id);
}

void displayFlights() {
    if (head == NULL) {
        cout << "\t\t\t\t\t\tNo flights available.\n";
        return;
    }
    cout << endl;
    cout << "\t\t\t\t\t\tAvailable Flights:\n";
    Flight* temp = head;
    while (temp != NULL) {
        cout << "\t\t\t\t\t\tFlight ID: " << temp->flightID
             << ", Destination: " << temp->destination
             << ", Seats Available: " << temp->seatsAvailable << endl;
        temp = temp->next;
    }
}

Flight* searchFlight(string id) {
    Flight* temp = head;
    while (temp != NULL) {
        if (temp->flightID == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void bookSeat(string id) {
    Flight* flight = searchFlight(id);
    if (flight == NULL) {
        cout << "\t\t\t\t\t\tFlight not found.\n";
        return;
    }
    if (flight->seatsAvailable > 0) {
        flight->seatsAvailable--;
        bookingStack.push(id);
        cout << "\t\t\t\t\t\tSeat booked successfully on flight: " << id << endl;
        notificationQueue.enqueue("\t\t\t\t\t\tSeat booked on flight: " + id);
    } else {
        cout << "\t\t\t\t\t\tNo seats available on this flight.\n";
    }
}

void undoBooking() {
    if (bookingStack.isEmpty()) {
        cout << "\t\t\t\t\t\tNo bookings to undo.\n";
        return;
    }

    string lastBooking = bookingStack.pop();
    Flight* flight = searchFlight(lastBooking);
    if (flight != NULL) {
        flight->seatsAvailable++;
        cout << "\t\t\t\t\t\tBooking undone for flight: " << lastBooking << endl;
        notificationQueue.enqueue("\t\t\t\t\t\tBooking undone for flight: " + lastBooking);
    }
}

void sortFlights() {
    if (head == NULL || head->next == NULL) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Flight* current = head;
        Flight* prev = NULL;

        while (current != NULL && current->next != NULL) {
            if (current->destination > current->next->destination) {
                Flight* temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if (prev == NULL) {
                    head = temp;
                } else {
                    prev->next = temp;
                }

                swapped = true;
                prev = temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);

    cout << "\t\t\t\t\t\tFlights sorted by destination.\n";
}

void displayNotifications() {
    if (notificationQueue.isEmpty()) {
        cout << "\t\t\t\t\t\tNo notifications.\n";
        return;
    }
    cout << endl;
    cout << "\t\t\t\t\t\tNotifications:\n";
    while (!notificationQueue.isEmpty()) {
        cout << "\t\t\t\t\t\t- " << notificationQueue.dequeue() << endl;
    }
}

int main() {
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t WELCOME TO FLIGHT MANAGEMENT SYSTEM!\n\n\n"; Sleep(300);
    cout << "\n\n\t\t\t\t\t\tProject Prepared by:"; Sleep(400);
    cout << "\n\n\t\t\t\t\t\t--------------------"; Sleep(500);
    cout << "\n\n\n\t\t\t\t     Ahmad Arsalan Zahid               54381"; Sleep(1000);
    cout << "\n\n\t\t\t\t        Muhammad Usman                 49649"; Sleep(2000);
    cout << endl;
    system("cls");

    int choice;
    string flightID, destination;
    int seats;

    do {
        cout << "\n\n\n\n";
        cout << "\t\t\t\t\t\t1. Add Flight\n";
        cout << "\t\t\t\t\t\t2. Display Flights\n";
        cout << "\t\t\t\t\t\t3. Search Flight\n";
        cout << "\t\t\t\t\t\t4. Book Seat\n";
        cout << "\t\t\t\t\t\t5. Undo Last Booking\n";
        cout << "\t\t\t\t\t\t6. Sort Flights by Destination\n";
        cout << "\t\t\t\t\t\t7. Display Notifications\n";
        cout << "\t\t\t\t\t\t0. Exit\n";
        cout << endl;
        cout << "\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
    case 1:
        cout << "\t\t\t\t\t\tEnter Flight ID: ";
        cin >> flightID;
        cout << "\t\t\t\t\t\tEnter Destination: ";
        cin >> destination;
        cout << "\t\t\t\t\t\tEnter Seats Available: ";
        cin >> seats;
        addFlight(flightID, destination, seats);
        system("pause");
        system("cls");
        break;
    case 2:
        displayFlights();
        system("pause");
        system("cls");
        break;
    case 3:
        cout << "\t\t\t\t\t\tEnter Flight ID to Search: ";
        cin >> flightID;
        if (searchFlight(flightID)) {
            cout << "\t\t\t\t\t\tFlight found!\n";
        } else {
            cout << "\t\t\t\t\t\tFlight not found.\n";
        }
        system("pause");
        system("cls");
        break;
    case 4:
        cout << "\t\t\t\t\t\tEnter Flight ID to Book: ";
        cin >> flightID;
        bookSeat(flightID);
        system("pause");
        system("cls");
        break;
    case 5:
        undoBooking();
        system("pause");
        system("cls");
        break;
    case 6:
        sortFlights();
        system("pause");
        system("cls");
        break;
    case 7:
        displayNotifications();
        system("pause");
        system("cls");
        break;
    case 0:
        cout << "\t\t\t\t\t\tExiting program.\n";
        break;
    default:
        cout << "\t\t\t\t\t\tInvalid choice. Try again.\n";
        system("pause");
        system("cls");
        break;
}
    
    } while (choice != 0);
}
