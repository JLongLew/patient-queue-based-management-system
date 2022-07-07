#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <cctype>

using namespace std;

struct DoctorAndNurse {
	string userID;
	string password;
};

struct Patient {
	string patientID;
	string firstName;
	string lastName;
	int age;
	char gender;
	string phoneNo;
	string address;
	string sicknessDescription;
	string visitDate;
	string visitTime;
	char disabilityOption;
	string doctorName;
	string medicineInformation;
	Patient* nextAddress;
	Patient* prevAddress;
}*waitingHead, * visitHistoryHead, * newNode, * current, * waitingTail, * visitHistoryTail;

int index = 0;
int waitingPatientSize = 0;
int visitHistorySize = 0;

void insertWaitingPatient(string patientID, string firstName, string lastName,
	int age, char gender, string phoneNo, string address, string sicknessDescription,
	string visitDate, string visitTime, char disabilityOption)
{
	newNode = new Patient;
	newNode->patientID = patientID;
	newNode->firstName = firstName;
	newNode->lastName = lastName;
	newNode->age = age;
	newNode->gender = gender;
	newNode->phoneNo = phoneNo;
	newNode->address = address;
	newNode->sicknessDescription = sicknessDescription;
	newNode->visitDate = visitDate;
	newNode->visitTime = visitTime;
	newNode->disabilityOption = disabilityOption;
	newNode->doctorName = "NULL";
	newNode->medicineInformation = "NULL";
	newNode->nextAddress = NULL;
	newNode->prevAddress = NULL;

	//situation 1: list is empty (adding any patients)
	if (waitingHead == NULL)
	{
		waitingHead = waitingTail = newNode;
	}
	else
	{
		// Check whether the new patient is disabled or not
		if (newNode->disabilityOption == 'Y') {
			if (waitingHead->disabilityOption == 'Y') {
				//situation 2: list with disabled patients (adding disabled patients)
				current = waitingHead->nextAddress;
				// Loop the waiting list until find the non-disabled patient
				while (current->disabilityOption == 'Y') {
					current = current->nextAddress;
				}
				current->prevAddress->nextAddress = newNode;
				newNode->prevAddress = current->prevAddress;
				current->prevAddress = newNode;
				newNode->nextAddress = current;
			}
			else {
				//situation 3: list without disabled patients (adding disabled patients)
				// If the first patient is not disabled, directly add the new disabled patient in the first node
				newNode->nextAddress = waitingHead;
				waitingHead->prevAddress = newNode;
				waitingHead = newNode;
			}
		}
		else {
			//situation 4: list not empty (adding normal patients)
			//Insert from the end in waiting list
			newNode->prevAddress = waitingTail;
			waitingTail->nextAddress = newNode;
			waitingTail = newNode;
		}
	}
	::index++;
	::waitingPatientSize++;
}

void insertVisitHistoryPatient(string patientID, string firstName, string lastName,
	int age, char gender, string phoneNo, string address, string sicknessDescription,
	string visitDate, string visitTime, char disabilityOption, string doctorName, string medicineInformation)
{
	newNode = new Patient;
	newNode->patientID = patientID;
	newNode->firstName = firstName;
	newNode->lastName = lastName;
	newNode->age = age;
	newNode->gender = gender;
	newNode->phoneNo = phoneNo;
	newNode->address = address;
	newNode->sicknessDescription = sicknessDescription;
	newNode->visitDate = visitDate;
	newNode->visitTime = visitTime;
	newNode->disabilityOption = disabilityOption;
	newNode->doctorName = doctorName;
	newNode->medicineInformation = medicineInformation;
	newNode->nextAddress = NULL;
	newNode->prevAddress = NULL;

	//situation 1: list is empty
	if (visitHistoryHead == NULL)
	{
		visitHistoryHead = visitHistoryTail = newNode;
	}
	else
	{
		//situation 2: list not empty
		//Insert from the end in visit history list
		newNode->prevAddress = visitHistoryTail;
		visitHistoryTail->nextAddress = newNode;
		visitHistoryTail = newNode;
	}
	::index++;
	::visitHistorySize++;
}

void addPatient() {
	int decision = 1;

	string patientID;
	string firstName;
	string lastName;
	int age;
	char gender;
	string phoneNo;
	string address;
	string sicknessDescription;
	string visitDate;
	string visitTime;
	char disabilityOption;

	regex n("[A-Za-z]+");
	regex p("^(\\d{3}[- .]?){2}\\d{4}$");
	regex d("([0-9]{2})/([0-9]{2})/([0-9]{4})");
	regex t("([01]?[0-9]|2[0-3]).[0-5][0-9]");
	regex k("[A-Za-z1-9., ]+");

	while (decision != 0)
	{
		patientID = "P" + to_string((::index + 1));
		cout << "Enter the Patient's First Name: ";
		cin >> firstName;
		while (!regex_match(firstName, n) || firstName.empty()) {
			cout << endl << "Invalid Name !!!" << endl;
			cout << "Enter the Patient's First Name: ";
			cin.ignore();
			cin >> firstName;
		}
		cin.ignore();

		cout << endl << "Enter the Patient's Last Name: ";
		cin >> lastName;
		while (!regex_match(lastName, n) || lastName.empty()) {
			cout << endl << "Invalid Name !!!" << endl;
			cout << "Enter the Patient's Last Name: ";
			cin.ignore();
			cin >> lastName;
		}
		cin.ignore();

		cout << endl << "Enter the Patient's Age: ";
		bool valid = false;
		do {
			cin >> age;
			if (cin.fail() || age <= 0) {
				cout << endl << "Invalid Age!!!" << endl;
				cout << "Enter the Patient's Age: ";
				cin.clear();
				cin.ignore();
			}
			else {
				valid = true;
			}
		} while (!valid);
		cin.ignore();


		cout << endl << "Enter the Patient's Gender ('M' for Male, 'F' for Female): ";
		cin >> gender;
		gender = toupper(gender);
		while (!((gender == 'M') || (gender == 'F'))) {
			cout << endl << "Invalid Gender !!!" << endl;
			cout << "Enter the Patient's Gender ('M' for Male, 'F' for Female): ";
			cin.ignore();
			cin >> gender;
			gender = toupper(gender);
		}
		cin.ignore();

		cout << endl << "Enter the Patient's Phone Number: ";
		cin >> phoneNo;
		while (!regex_match(phoneNo, p) || phoneNo.empty()) {
			cout << endl << "Invalid Phone Number !!!" << endl;
			cout << "Enter the Patient's Phone Number: ";
			cin.ignore();
			cin >> phoneNo;
		}
		cin.ignore();

		cout << endl << "Enter the Patient's Address: ";
		getline(cin, address);
		while (address.empty() || !regex_match(address, k)) {
			cout << endl << "Invalid Address !!!" << endl;
			cout << "Enter the Patient's Address: ";
			getline(cin, address);
		}

		cout << endl << "Enter Description about Patient's Sickness: ";
		getline(cin, sicknessDescription);
		while (sicknessDescription.empty() || !regex_match(sicknessDescription, k)) {
			cout << endl << "Invalid sickness description !!!" << endl;
			cout << "Enter Description about Patient's Sickness: ";
			getline(cin, sicknessDescription);
		}

		cout << endl << "Enter the Patient's Visit Date (Example = 01/02/2000): ";
		cin >> visitDate;
		while (!regex_match(visitDate, d) || visitDate.empty()) {
			cout << endl << "Invalid Date !!!" << endl;
			cout << "Enter the Patient's Visit Date (Example = 01/02/2000): ";
			cin.ignore();
			cin >> visitDate;
		}
		cin.ignore();

		cout << endl << "Enter the Patient's Visit Time (Example = 22.22): ";
		cin >> visitTime;
		while (!regex_match(visitTime, t) || visitTime.empty()) {
			cout << endl << "Invalid Time !!!" << endl;
			cout << "Enter the Patient's Visit Time (Example = 22.22): ";
			cin.ignore();
			cin >> visitTime;
		}
		cin.ignore();

		cout << endl << "Is the Patient disabled ? ('Y' for Yes, 'N' for No): ";
		cin >> disabilityOption;
		disabilityOption = toupper(disabilityOption);
		while (!((disabilityOption == 'Y') || (disabilityOption == 'N'))) {
			cout << endl << "Invalid Option !!!" << endl;
			cout << "Is the Patient disabled ? ('Y' for Yes, 'N' for No): ";
			cin.ignore();
			cin >> disabilityOption;
			disabilityOption = toupper(disabilityOption);
		}
		cin.ignore();


		insertWaitingPatient(patientID, firstName, lastName, age, gender, phoneNo, address, sicknessDescription, visitDate, visitTime, disabilityOption);
		cout << endl;

		cout << "Would you like to add another patient? Type: 1 for Yes, 0 for No. \n";
		cin >> decision;
		cin.ignore();
	}
	system("cls");
}

void viewWaitingPatients()
{
	current = waitingHead;

	cout << "***************\n";
	cout << " View Patients\n";
	cout << "***************\n\n";

	while (current != NULL)
	{

		cout << "===============" << endl;
		cout << "Patient ID: " << current->patientID << endl;
		cout << "===============" << endl;
		cout << "First Name: " << current->firstName << "  " << "Last Name: " << current->lastName << endl;
		cout << "Age: " << current->age << endl;
		cout << "Gender: " << current->gender << endl;
		cout << "Phone Number: " << current->phoneNo << endl;
		cout << "Address: " << current->address << endl;
		cout << "Sickness Description: " << current->sicknessDescription << endl;
		cout << "Visit Date: " << current->visitDate << "  " << "Visit Time: " << current->visitTime << endl;
		cout << "Disability: " << current->disabilityOption << endl;
		cout << "Doctor's Name: " << current->doctorName << endl;
		cout << "Medicine Information: " << current->medicineInformation << endl << endl;

		current = current->nextAddress;
	}

	cout << "End of Patient List!" << endl;
	system("pause");
	system("cls");
}

void viewVisitHistoryPatients()
{
	current = visitHistoryHead;

	cout << "***************\n";
	cout << " View Patients\n";
	cout << "***************\n\n";

	while (current != NULL)
	{

		cout << "===============" << endl;
		cout << "Patient ID: " << current->patientID << endl;
		cout << "===============" << endl;
		cout << "First Name: " << current->firstName << "  " << "Last Name: " << current->lastName << endl;
		cout << "Age: " << current->age << endl;
		cout << "Gender: " << current->gender << endl;
		cout << "Phone Number: " << current->phoneNo << endl;
		cout << "Address: " << current->address << endl;
		cout << "Sickness Description: " << current->sicknessDescription << endl;
		cout << "Visit Date: " << current->visitDate << "  " << "Visit Time: " << current->visitTime << endl;
		cout << "Disability: " << current->disabilityOption << endl;
		cout << "Doctor's Name: " << current->doctorName << endl;
		cout << "Medicine Information: " << current->medicineInformation << endl << endl;

		current = current->nextAddress;
	}

	cout << "End of Patient List!" << endl;
	system("pause");
	system("cls");
}

void callPatients() {
	//Delete from the front in waiting list
	//situation 1: list is empty
	if (waitingHead == NULL) {
		cout << "There is no patient on the waiting list." << endl;
		system("pause");
		return;
	}
	//situation 2: list not empty
	current = waitingHead;
	waitingHead = waitingHead->nextAddress;

	//situation3: determine whether the current head is it equal to NULL value
	if (waitingHead == NULL) {
		waitingTail = NULL;
	}
	else {
		waitingHead->prevAddress = NULL;
	}
	current->nextAddress = NULL;
	current->prevAddress = NULL;

	//Insert from the end in visit history list
	//situation 1: list empty
	if (visitHistoryHead == NULL)
	{
		visitHistoryHead = visitHistoryTail = current;
	}
	//situation 2: list not empty
	else
	{
		current->prevAddress = visitHistoryTail;
		visitHistoryTail->nextAddress = current;
		visitHistoryTail = current;
	}

	::waitingPatientSize--;
	::visitHistorySize++;

	cout << "The patient of " << current->patientID << " is called to be treated." << endl;
	cout << "Waiting List Patient: " << waitingPatientSize << endl;
	cout << "Visit History List Patient: " << visitHistorySize << endl;
	system("pause");
}

void searchWaitingList() {
	string search;
	int decision = 1;

	while (decision != 0) {
		//situation 1: list is empty
		if (waitingHead == NULL) {
			cout << "There is no patient on the waiting list.\n";
			system("pause");
			return;
		}

		cout << "*********************************\n";
		cout << " Search Patients on Waiting List\n";
		cout << "*********************************\n";
		cout << "1. Patient ID\n";
		cout << "2. First Name\n";
		cout << "0. Exit\n\n";
		cout << "Select your option: ";
		cin >> decision;
		cin.ignore();

		int flag = 1;
		int position = 1;
		switch (decision)
		{
		case 0:
			return;
		case 1:
			cout << "Enter Patient ID:";
			cin >> search;
			cin.ignore();

			//situation 2: list not empty
			current = waitingHead;
			while (current != NULL) {
				if (search == current->patientID) {
					cout << "===============" << endl;
					cout << position << " - " << current->patientID << endl;
					cout << "===============" << endl;
					cout << "First Name: " << current->firstName << "  " << "Last Name: " << current->lastName << endl;
					cout << "Age: " << current->age << endl;
					cout << "Gender: " << current->gender << endl;
					cout << "Phone Number: " << current->phoneNo << endl;
					cout << "Address: " << current->address << endl;
					cout << "Sickness Description: " << current->sicknessDescription << endl;
					cout << "Visit Date: " << current->visitDate << "  " << "Visit Time: " << current->visitTime << endl;
					cout << "Disability: " << current->disabilityOption << endl;
					cout << "Doctor's Name: " << current->doctorName << endl;
					cout << "Medicine Information: " << current->medicineInformation << endl << endl;
					flag = 0;
				}
				current = current->nextAddress;
				position++;
			}
			if (flag == 1) {
				cout << "Patient was not found in the waiting list.\n";
			}
			break;
		case 2:
			cout << "Enter First Name:";
			cin >> search;
			cin.ignore();

			//situation 2: list not empty
			current = waitingHead;
			while (current != NULL) {
				if (search == current->firstName) {
					cout << "===============" << endl;
					cout << position << " - " << current->patientID << endl;
					cout << "===============" << endl;
					cout << "First Name: " << current->firstName << "  " << "Last Name: " << current->lastName << endl;
					cout << "Age: " << current->age << endl;
					cout << "Gender: " << current->gender << endl;
					cout << "Phone Number: " << current->phoneNo << endl;
					cout << "Address: " << current->address << endl;
					cout << "Sickness Description: " << current->sicknessDescription << endl;
					cout << "Visit Date: " << current->visitDate << "  " << "Visit Time: " << current->visitTime << endl;
					cout << "Disability: " << current->disabilityOption << endl;
					cout << "Doctor's Name: " << current->doctorName << endl;
					cout << "Medicine Information: " << current->medicineInformation << endl << endl;
					flag = 0;
				}
				current = current->nextAddress;
				position++;
			}
			if (flag == 1) {
				cout << "Patient was not found in the waiting list.\n";
			}
			break;
		default:
			cout << "Invalid option!\n";
		}
		system("pause");
		system("cls");
	}
}

void viewPatientsPageByPage(Patient* listHead) {

	system("cls");
	current = listHead;

	int decision = 1;
	while (decision != 0)
	{
		cout << "Patient Details as below:" << endl;
		cout << "\n=========================================================================================================\n";
		cout << "Patient ID: " << current->patientID << endl;
		cout << "\n=========================================================================================================\n";
		cout << "First Name: " << current->firstName << "  " << "Last Name: " << current->lastName << endl;
		cout << "Age: " << current->age << endl;
		cout << "Gender: " << current->gender << endl;
		cout << "Phone Number: " << current->phoneNo << endl;
		cout << "Address: " << current->address << endl;
		cout << "Sickness Description: " << current->sicknessDescription << endl;
		cout << "Visit Date: " << current->visitDate << "  " << "Visit Time: " << current->visitTime << endl;
		cout << "Disability: " << current->disabilityOption << endl;
		cout << "Doctor's Name: " << current->doctorName << endl;
		cout << "Medicine Information: " << current->medicineInformation << endl;
		cout << "\n=========================================================================================================\n";
		cout << "1. Next Patient\t 2.Previous Patient\t 0.Exit to Menu Page \t";
		cout << "\n=========================================================================================================\n";
		cout << "Select an option:";
		cin >> decision;
		cin.ignore();

		if (decision == 1 && current->nextAddress != NULL)
		{
			current = current->nextAddress;
		}
		else if (decision == 2 && current->prevAddress != NULL)
		{
			current = current->prevAddress;
		}
		else if (decision == 0)
		{
			return;
		}
		else if (decision != 1 && decision != 2 && decision != 0)
		{
			cout << "Invalid option!\n";
			system("pause");
		}
		else
		{
			cout << "There is no more patient!" << endl;
			system("pause");
		}

		system("cls");
	}
}

void sortWaitingList() {
	Patient* index = NULL;
	int swapping;
	//situation 1: list is empty
	if (waitingHead == NULL || waitingHead->nextAddress == NULL) {
		cout << "There is no patient on the waiting list.\n";
		cout << "Cannot sort!" << endl;
		system("pause");
		return;
	}

	//situation 2: list not empty
	//bubble sort
	do {
		swapping = 0;
		for (current = waitingHead; current->nextAddress != NULL; current = current->nextAddress) {
			index = current->nextAddress;
			if (stod(current->visitTime) > stod(index->visitTime)) {
				swap(current->patientID, index->patientID);
				swap(current->firstName, index->firstName);
				swap(current->lastName, index->lastName);
				swap(current->age, index->age);
				swap(current->gender, index->gender);
				swap(current->phoneNo, index->phoneNo);
				swap(current->address, index->address);
				swap(current->sicknessDescription, index->sicknessDescription);
				swap(current->visitDate, index->visitDate);
				swap(current->visitTime, index->visitTime);
				swap(current->disabilityOption, index->disabilityOption);
				swapping = 1;
			}
		}
	} while (swapping);
	viewPatientsPageByPage(waitingHead);
}

void searchAndModifyVisitHistory() {
	bool r = true;
	while (r == true) {
		bool found = false;
		while (found == false) {
			string patientID;
			cout << "Enter Patient ID: ";
			getline(cin, patientID);
			// Start searching for matching ID
			if (visitHistoryHead == NULL) {
				cout << "The patient visit history is empty!";
				return;
			}

			current = visitHistoryHead;

			while (current != NULL) {
				if (patientID == current->patientID) {
					found = true;
					// display
					cout << "===============" << endl;
					cout << "Patient ID: " << current->patientID << endl;
					cout << "===============" << endl;
					cout << "First Name: " << current->firstName << " " << "Last Name: " << current->lastName << endl;
					cout << "Age: " << current->age << endl;
					cout << "Gender: " << current->gender << endl;
					cout << "Phone Number: " << current->phoneNo << endl;
					cout << "Address: " << current->address << endl;
					cout << "Sickness Description: " << current->sicknessDescription << endl;
					cout << "Visit Date: " << current->visitDate << " " << "Visit Time: " << current->visitTime << endl;
					cout << "Disability: " << current->disabilityOption << endl;
					cout << "Doctor's Name: " << current->doctorName << endl;
					cout << "Medicine Information: " << current->medicineInformation << endl << endl;
					break;
				}
				else {
					current = current->nextAddress;
				}
			}
			if (!found) {
				cout << "Patient ID not found!" << endl;
			}
		}
		string firstName;
		string lastName;
		int age;
		char gender;
		string phoneNo;
		string address;
		string sicknessDescription;
		string visitDate;
		string visitTime;
		char disabilityOption;
		string doctorName;
		string medicineInformation;
		char option;
		regex n("[A-Za-z]+");
		regex p("^(\\d{3}[- .]?){2}\\d{4}$");
		regex d("([0-9]{2})/([0-9]{2})/([0-9]{4})");
		regex t("([0-9]{2}).([0-9]{2})");
		regex k("[A-Za-z1-9.,]+");
		do {
			cout << "First Name: ";
			getline(cin, firstName);
			if (!(regex_match(firstName, n) || firstName.empty())) {
				cout << "Invalid first name!!!" << endl;
			}
		} while (!(regex_match(firstName, n) || firstName.empty()));
		current->firstName = firstName;

		do {
			cout << "Last Name: ";
			getline(cin, lastName);
			if (!(regex_match(lastName, n) || lastName.empty())) {
				cout << "Invalid last name!!!" << endl;
			}
		} while (!(regex_match(lastName, n) || lastName.empty()));
		current->lastName = lastName;
		bool valid = false;
		do {
			cout << "Age: ";
			cin >> age;
			if (cin.fail()) {
				cout << "Invalid age!!!" << endl;
				cin.clear();
				cin.ignore();
			}
			else {
				valid = true;
			}
		} while (!valid);
		current->age = age;

		do {
			cout << "Gender ('M' for Male, 'F' for Female): ";
			cin >> gender;
			if (!((gender == 'M') || (gender == 'F') || (gender == 'm') || (gender == 'f'))) {
				cout << endl << "Invalid Gender !!!" << endl;
				cout << "Gender ('M' for Male, 'F' for Female): ";
				cin >> gender;
			}
		} while (!((gender == 'M') || (gender == 'F') || (gender == 'm') || (gender == 'f')));
		current->gender = gender;

		cin.ignore();

		do {
			cout << "Phone Number: ";
			getline(cin, phoneNo);
			if (!(regex_match(phoneNo, p) || phoneNo.empty())) {
				cout << "Invalid phone number!!!" << endl;
			}
		} while (!regex_match(phoneNo, p) || phoneNo.empty());
		current->phoneNo = phoneNo;

		do {
			cout << "Address: ";
			getline(cin, address);
			if (address.empty() || !regex_match(address, k)) {
				cout << "Invalid address!!!" << endl;
			}
		} while (address.empty() || !regex_match(address, k));
		current->address = address;

		do {
			cout << "Sickness Description: ";
			getline(cin, sicknessDescription);
			if (sicknessDescription.empty() || !regex_match(sicknessDescription, k)) {
				cout << "Invalid sickness description!!!" << endl;
			}
		} while (sicknessDescription.empty() || !regex_match(sicknessDescription, k));
		current->sicknessDescription = sicknessDescription;

		do {
			cout << "Visit Date (e.g. 01/01/2020): ";
			getline(cin, visitDate);
			if (visitDate.empty() || !regex_match(visitDate, d)) {
				cout << "Invalid visit date!!!" << endl;
			}
		} while (!regex_match(visitDate, d) || visitDate.empty());
		current->visitDate = visitDate;

		do {
			cout << "Visit Time (e.g. 13.00): ";
			getline(cin, visitTime);
			if (!regex_match(visitTime, t) || visitTime.empty()) {
				cout << "Invalid visit date!!!" << endl;
			}
		} while (!regex_match(visitTime, t) || visitTime.empty());
		current->visitTime = visitTime;

		do {
			cout << "Disability (Y/N): ";
			cin >> disabilityOption;
			if (!((disabilityOption == 'Y') || (disabilityOption == 'y') || (disabilityOption == 'N') || (disabilityOption == 'n'))) {
				cout << "Invalid disability option!!!" << endl;
			}
		} while (!((disabilityOption == 'Y') || (disabilityOption == 'y') || (disabilityOption == 'N') || (disabilityOption == 'n')));
		current->disabilityOption = disabilityOption;

		cin.ignore();
		do {
			cout << "Doctor's Name: ";
			getline(cin, doctorName);
			if (!regex_match(doctorName, n) || doctorName.empty()) {
				cout << "Invalid doctor name!!!" << endl;
			}
		} while (!regex_match(doctorName, n) || doctorName.empty());
		current->doctorName = doctorName;

		do {
			cout << "Medicine Information: ";
			getline(cin, medicineInformation);
			if (medicineInformation.empty() || !regex_match(medicineInformation, k)) {
				cout << "Invalid doctor name!!!" << endl;
			}
		} while (medicineInformation.empty() || !regex_match(medicineInformation, k));
		current->medicineInformation = medicineInformation;

		cout << "===============" << endl;
		cout << "Patient ID: " << current->patientID << endl;
		cout << "===============" << endl;
		cout << "First Name: " << current->firstName << " " << "Last Name: " << current->lastName << endl;
		cout << "Age: " << current->age << endl;
		cout << "Gender: " << current->gender << endl;
		cout << "Phone Number: " << current->phoneNo << endl;
		cout << "Address: " << current->address << endl;
		cout << "Sickness Description: " << current->sicknessDescription << endl;
		cout << "Visit Date: " << current->visitDate << " " << "Visit Time: " << current->visitTime << endl;
		cout << "Disability: " << current->disabilityOption << endl;
		cout << "Doctor's Name: " << current->doctorName << endl;
		cout << "Medicine Information: " << current->medicineInformation << endl << endl;

		do {
			cout << "Continue searching? (Y/N): ";
			cin >> option;
			if (!((option == 'Y') || (option == 'y') || (option == 'N') || (option == 'n'))) {
				cout << "Invalid option!!!" << endl;
			}
		} while (!((option == 'Y') || (option == 'y') || (option == 'N') || (option == 'n')));

		if (option == 'N' || option == 'n') {
			r = false;
		}
	}
	system("cls");
}

void searchVisitHistory() {
	bool r = true;
	char input;
	while (r == true) {
		bool found = false;
		bool contain = false;
		string keyWord;
		int option;
		bool valid = false;
		do {
			cout << "Search by: (0 for Sickness Description, 1 for First Name)";
			cin >> option;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "Invalid input. Enter only 0 or 1." << endl << endl;
				continue;
			}
			else {
				valid = true;
			}
			switch (option) {
			case 0:
				cout << "Enter Sickness Description: ";
				cin.ignore();
				getline(cin, keyWord);
				break;
			case 1:
				cout << "Enter first name: ";
				cin.ignore();
				getline(cin, keyWord);
				break;
			default:
				cout << "Invalid input. Enter only 0 or 1." << endl << endl;
				valid = false;
			}
		} while (!valid || (option != 0 && option != 1));

		// Start searching for matching keyword
		if (visitHistoryHead == NULL) {
			cout << "The patient visit history is empty!";
			return;
		}

		current = visitHistoryHead;

		while (current != NULL) {
			switch (option) {
			case 0:
				if (current->sicknessDescription.find(keyWord) != string::npos) {
					found = true;
					contain = true;
				}
				break;
			case 1:
				if (current->firstName.find(keyWord) != string::npos) {
					found = true;
					contain = true;
				}
			}

			if (contain == true) {
				cout << "===============" << endl;
				cout << "Patient ID: " << current->patientID << endl;
				cout << "===============" << endl;
				cout << "First Name: " << current->firstName << " " << "Last Name: " << current->lastName << endl;
				cout << "Age: " << current->age << endl;
				cout << "Gender: " << current->gender << endl;
				cout << "Phone Number: " << current->phoneNo << endl;
				cout << "Address: " << current->address << endl;
				cout << "Sickness Description: " << current->sicknessDescription << endl;
				cout << "Visit Date: " << current->visitDate << " " << "Visit Time: " << current->visitTime << endl;
				cout << "Disability: " << current->disabilityOption << endl;
				cout << "Doctor's Name: " << current->doctorName << endl;
				cout << "Medicine Information: " << current->medicineInformation << endl << endl;
				contain = false;
			}
			current = current->nextAddress;
		}

		if (!found) {
			cout << "No results found" << endl;
		}

		do {
			cout << "Continue searching? (Y/N): " << endl;
			cin >> input;
			cin.ignore();
			if (!(input == 'Y' || input == 'y' || input == 'N' || input == 'n')) {
				cout << "Invalid input. Enter only Y/N.";
			}
		} while (!(input == 'Y' || input == 'y' || input == 'N' || input == 'n'));
		if (input == 'N' || input == 'n') {
			r = false;
		}
	}
	system("cls");
}

void sortVisitHistory() {
	Patient* index = NULL;
	int swapping;
	//situation 1: list is empty
	if (visitHistoryHead == NULL) {
		cout << "There is no patient on the visit history list.\n";
		cout << "Cannot sort!" << endl;
		system("pause");
		return;
	}

	int currentDate[3];
	int indexDate[3];

	//situation 2: list not empty
	do {
		swapping = 0;
		current = visitHistoryHead;

		for (current = visitHistoryHead; current->nextAddress != NULL; current = current->nextAddress) {
			currentDate[0] = stoi(current->visitDate.substr(0, 2).erase(0, current->visitDate.substr(0, 2).find_first_not_of('0')));
			currentDate[1] = stoi(current->visitDate.substr(3, 2).erase(0, current->visitDate.substr(3, 2).find_first_not_of('0')));
			currentDate[2] = stoi(current->visitDate.substr(6, 4).erase(0, current->visitDate.substr(6, 4).find_first_not_of('0')));
			index = current->nextAddress;
			indexDate[0] = stoi(index->visitDate.substr(0, 2).erase(0, index->visitDate.substr(0, 2).find_first_not_of('0')));
			indexDate[1] = stoi(index->visitDate.substr(3, 2).erase(0, index->visitDate.substr(3, 2).find_first_not_of('0')));
			indexDate[2] = stoi(index->visitDate.substr(6, 4).erase(0, index->visitDate.substr(6, 4).find_first_not_of('0')));
			if ((currentDate[2] < indexDate[2]) || ((currentDate[2] == indexDate[2]) &&
				(currentDate[1] < indexDate[1])) || (((currentDate[2] == indexDate[2]) &&
					(currentDate[1] == indexDate[1])) && (currentDate[0] < indexDate[0])) ||
					((((currentDate[2] == indexDate[2]) && (currentDate[1] == indexDate[1])) &&
						(currentDate[0] == indexDate[0])) && (stod(current->visitTime) <= stod(index->visitTime)))) {
				swap(current->patientID, index->patientID);
				swap(current->firstName, index->firstName);
				swap(current->lastName, index->lastName);
				swap(current->age, index->age);
				swap(current->gender, index->gender);
				swap(current->phoneNo, index->phoneNo);
				swap(current->address, index->address);
				swap(current->sicknessDescription, index->sicknessDescription);
				swap(current->visitDate, index->visitDate);
				swap(current->visitTime, index->visitTime);
				swap(current->disabilityOption, index->disabilityOption);
				swap(current->doctorName, index->doctorName);
				swap(current->medicineInformation, index->medicineInformation);
				swapping = 1;
			}
		}
	} while (swapping);
	viewPatientsPageByPage(visitHistoryHead);
	system("cls");
}

void login() {
	system("cls");
	int log = 1;
	int choice = 1;

	string user;
	string pass;
	struct DoctorAndNurse doctor { "a", "b" };
	struct DoctorAndNurse nurse { "c", "d" };

	cout << "*****************************\n";
	cout << " Welcome to Klinik Sulaiman!\n";
	cout << "*****************************";
	cout << endl;
	cout << "Enter username: ";
	cin >> user;
	while (!(user == doctor.userID || user == nurse.userID)) {
		cin.ignore();
		cout << "User does not exist!!!" << endl;
		cout << "Enter username: ";
		cin >> user;
	}
	cin.ignore();

	cout << "Enter password: ";
	cin >> pass;
	while (!((user == doctor.userID && pass == doctor.password) || (user == nurse.userID && pass == nurse.password))) {
		cin.ignore();
		cout << "Invalid password !!!" << endl;
		cout << "Enter password: ";
		cin >> pass;
	}
	if (user == nurse.userID && pass == nurse.password) {
		log = 1;
	}
	else if (user == doctor.userID && pass == doctor.password) {
		log = 2;
	}
	cin.ignore();

	switch (log)
	{
	case 1:
		system("cls");
		while (choice != 0)
		{
			cout << " ____________________________________________________________________________________\n";
			cout << "|     Klinik Sulaiman Patient's Queue Bases Management System: Nurse Access          |\n";
			cout << "|------------------------------------------------------------------------------------|\n";
			cout << "|                                    Menu Options:                                   |" << endl;
			cout << "|------------------------------------------------------------------------------------|\n";
			cout << "|                                                                                    |\n";
			cout << "|1. Add a new patient on the waiting list                                            |" << endl;
			cout << "|2. View all patients on the original waiting list                                   |" << endl;
			cout << "|3. View all patients on the original visit history list                             |" << endl;
			cout << "|4. Calling the patient to be treated                                                |" << endl;
			cout << "|5. Search patient from the waiting list based on Patient ID or First Name           |" << endl;
			cout << "|6. Sort the waiting list by patient's current visit time, display in ascending order|" << endl;
			cout << "|7. Logout                                                                           |" << endl;
			cout << "|____________________________________________________________________________________|\n";
			cout << "\nSelect your option: ";
			cin >> choice;
			cin.ignore();

			switch (choice)
			{
			case 1:
				system("cls");
				cout << "**************\n";
				cout << " Add Patients\n";
				cout << "**************\n";
				addPatient();
				break;
			case 2:
				system("cls");
				viewWaitingPatients();
				break;
			case 3:
				system("cls");
				viewVisitHistoryPatients();
				break;
			case 4:
				system("cls");
				callPatients();
				break;
			case 5:
				system("cls");
				searchWaitingList();
				break;
			case 6:
				system("cls");
				sortWaitingList();
				break;
			case 7:
				login();
				break;
			}
			system("cls");
		}
		break;
	case 2:
		system("cls");
		while (choice != 0)
		{
			cout << " ______________________________________________________________________________________________________\n";
			cout << "|     Klinik Sulaiman Patient's Queue Bases Management System: Doctor Access                           |\n";
			cout << "|------------------------------------------------------------------------------------------------------|\n";
			cout << "|                                    Menu Options:                                                     |" << endl;
			cout << "|------------------------------------------------------------------------------------------------------|\n";
			cout << "|                                                                                                      |\n";
			cout << "|1. View all patients on the original waiting list                                                     |" << endl;
			cout << "|2. View all patients on the original visit history list                                               |" << endl;
			cout << "|3. Search Specific Patient from the patient's visit history and modify patient records                |" << endl;
			cout << "|4. Sort and display all records from the patient's visit history list in descending order             |" << endl;
			cout << "|5. Search patients from the patient's visit history list based on sickness description or firstname   |" << endl;
			cout << "|6. Logout                                                                                             |" << endl;
			cout << "|______________________________________________________________________________________________________|\n";
			cout << "\nSelect your option: ";
			cin >> choice;
			cin.ignore();


			switch (choice) {
			case 1:
				system("cls");
				viewWaitingPatients();
				break;
			case 2:
				system("cls");
				viewVisitHistoryPatients();
				break;
			case 3:
				system("cls");
				searchAndModifyVisitHistory();
				break;
			case 4:
				system("cls");
				sortVisitHistory();
				break;
			case 5:
				system("cls");
				searchVisitHistory();
				break;
			case 6:
				login();
				break;
			default:
				cout << "Invalid option";
				system("cls");
			}

		}
		break;

	}

}

int main() {
	waitingHead = waitingTail = visitHistoryHead = visitHistoryTail = NULL;

	// Adding default patients into waiting list
	string defaultWaitingPatients[3][11] =
	{
		{"P4", "Lim", "Ah Kao", "28", "M", "0123456789", "No4, Jalan 4, Taman JKL", "None", "13/09/2021", "09.50", "N"},
		{"P5", "Mohammad", "Ali", "40", "M", "0129876543", "No5, Jalan 5, Taman MNO", "None", "13/09/2021", "09.40", "N"},
		{"P6", "Devi", "Darika", "12", "F", "0198765432", "No6, Jalan 6, Taman PQR", "None", "13/09/2021", "09.30", "Y"}
	};
	for (int i = 0; i < 3; i++)
	{
		insertWaitingPatient(defaultWaitingPatients[i][0], defaultWaitingPatients[i][1], defaultWaitingPatients[i][2], stoi(defaultWaitingPatients[i][3]),
			defaultWaitingPatients[i][4][0], defaultWaitingPatients[i][5], defaultWaitingPatients[i][6], defaultWaitingPatients[i][7],
			defaultWaitingPatients[i][8], defaultWaitingPatients[i][9], defaultWaitingPatients[i][10][0]);
	}

	// Adding default patients into visit history list
	string defaultVisitHistoryPatients[3][13] =
	{
		{"P1", "Tan", "Ah Mei", "58", "F", "0154887559", "No1, Jalan 1, Taman ABC", "None", "12/09/2021", "19.00", "N", "Doctor Tay", "Antibiotics"},
		{"P2", "Ahmad", "Faliq", "2", "M", "0167844877", "No2, Jalan 2, Taman DEF", "None", "12/09/2021", "09.14", "N", "Doctor Mutu", "Antibiotics"},
		{"P3", "Suresh", "Sarda", "62", "M", "0128549678", "No3, Jalan 3, Taman GHI", "None", "12/09/2021", "15.19", "N", "Doctor Tay", "Antibiotics"}
	};
	for (int i = 0; i < 3; i++)
	{
		insertVisitHistoryPatient(defaultVisitHistoryPatients[i][0], defaultVisitHistoryPatients[i][1], defaultVisitHistoryPatients[i][2],
			stoi(defaultVisitHistoryPatients[i][3]), defaultVisitHistoryPatients[i][4][0], defaultVisitHistoryPatients[i][5],
			defaultVisitHistoryPatients[i][6], defaultVisitHistoryPatients[i][7], defaultVisitHistoryPatients[i][8], defaultVisitHistoryPatients[i][9],
			defaultVisitHistoryPatients[i][10][0], defaultVisitHistoryPatients[i][11], defaultVisitHistoryPatients[i][12]);
	}

	login();
	return 0;
}
