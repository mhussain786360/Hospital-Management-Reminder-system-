#include <iostream>
#include <string>
#include <cstdlib>  // Include this for system("CLS")
using namespace std;

// Define struct to store information about Doctor
struct Doctor {
    string name, specialization;
    int room_no;
    bool isAvailable;
};

// Define struct to store information about patient
struct Patient {
    string name, disease, dateOfVisit;
    int wardNumber; // Assigned ward number
    int bedNumber;  // Assigned bed number
    string medicationMessage; // Message for medication based on disease
};

// Initialize all beds to false (unoccupied)
struct Ward {
    bool beds[5] = {false};
};

// Function declarations
void mainScreen();
void patientInfoScreen();
void patientDetailsScreen(Patient patients[], Doctor doctors[], int noOfPatients, int noOfDoctors);
void sendReminderToDoctor(const string& doctorName, const string& patientName);

// Global variable to control the program flow
bool running = true;  

// Clear the screen
void mainScreen() {
    while (running) {
        system("CLS");  
        cout << "Welcome to the Main Screen" << endl;
        cout << "1. Enter Patient Information" << endl;
        cout << "2. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                patientInfoScreen();
                break;
            case 2:
                cout << "Exiting..." << endl;
                running = false;  // Set running to false to exit the loop
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }
}

void patientInfoScreen() {
    system("CLS");  // Clear the screen
    cout << "Enter information for three patients" << endl;

    int noOfDoctors = 4;
    int noOfPatients = 3;

    // Create array to store data of doctors
    Doctor doctors[noOfDoctors] = {
        {"Dr. Zahid", "ENT", 101, true},
        {"Dr. Aslam", "Neurology", 102, true},
        {"Dr. Ali", "Diabetes", 103, true},
        {"Dr. Altaf", "Dermatology", 104, false}
    };

    // Create an array to store information about patients
    Patient patients[noOfPatients];

    // Loop to get information about each patient
    for (int i = 0; i < noOfPatients; i++) {
        cout << "\nPatient " << i + 1 << endl;
        cout << "Enter Name: ";
        cin >> patients[i].name;
        cout << "Enter Disease: ";
        cin >> patients[i].disease;
        cout << "Enter Date of visit format (dd/mm/yyyy): ";
        cin >> patients[i].dateOfVisit;

        // Assign medication message based on disease
        if (patients[i].disease == "ENT") {
            patients[i].medicationMessage = "Please take an ultrasound of your throat.";
        } else if (patients[i].disease == "Diabetes") {
            patients[i].medicationMessage = "Please take sugar in low quantity.";
        } else if (patients[i].disease == "Neurology") {
            patients[i].medicationMessage = "Take this medicine and come earlier for next checkup.";
        } else {
            patients[i].medicationMessage = "Please follow your doctor's instructions.";
        }
    }

    // Move to the patient details screen
    patientDetailsScreen(patients, doctors, noOfPatients, noOfDoctors);
}

void patientDetailsScreen(Patient patients[], Doctor doctors[], int noOfPatients, int noOfDoctors) {
	
    // Clear the screen only once before displaying all patients' details
    system("CLS");

    // Loop through each patient
    for (int i = 0; i < noOfPatients; i++) {
        cout << "\nPatient Name: " << patients[i].name << ", Disease: " << patients[i].disease << ", Date of visit: " << patients[i].dateOfVisit << endl;

        bool doctorFound = false; // Flag to check if a doctor was found for this patient

        // Find an available doctor
        for (int j = 0; j < noOfDoctors; j++) {
            if (!doctors[j].isAvailable && doctors[j].specialization == patients[i].disease) {
                cout << "Currently " << doctors[j].name << " is not available, Please visit later." << endl;
                doctorFound = true;
				break;
            } else if (doctors[j].specialization == patients[i].disease) {
                cout << "Please visit " << doctors[j].name << " in room number " << doctors[j].room_no << endl;
                doctorFound = true;

                // Send reminder to the doctor
                sendReminderToDoctor(doctors[j].name, patients[i].name);
                break; // Stop after finding the first available doctor
            }
        }

        // If no doctor was available
        if (!doctorFound) {
            cout << "No doctor available for the disease: " << patients[i].disease << ", Please visit a nearby hospital in urgency!" << endl;
        }

        // Display medication block
        cout << "\nMedication:\n" << patients[i].medicationMessage << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
    }

    cout << "\n1. Return to Main Screen" << endl;
    cout << "2. Exit" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            return;  // Return to main screen
        case 2:
            running = false;  // Set running to false to exit the loop
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            
            // Call the screen again for a valid choice
            patientDetailsScreen(patients, doctors, noOfPatients, noOfDoctors);  
            break;
    }
}

void sendReminderToDoctor(const string& doctorName, const string& patientName) {
    // Display a reminder message for the doctor
    
    cout << "\n----------------------------------------------------------------------------------" << endl;
    cout << "Reminder: Doctor " << doctorName << ", please check patient " << patientName << "." << endl;
    cout << "----------------------------------------------------------------------------------\n" << endl;
}

int main() {
    system("Color 4F");
    mainScreen();
    return 0;
}

