/*
Group Member
1.	Sue Chen Xiang - B032010034
2.	Fatin Najdah Binti Najmi Ismail - B032010201
3.	Muhammad Nuzula - B031920509
4.	Poh Soon Heng - B032010010

*/
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int MAXNAME=30;		// max number of name
const int MAXADDRESS=35;	// max number of address
const int MAXSIZE=20;		// max number of size
const int MAXGENDER=10;		// max number of gender
const int MAXPATIENT=100;	// max number of patient

struct Patient{				// declaration of struct
	char patient_name[MAXNAME+1];
	int patient_ID;
	char patient_address[MAXADDRESS+1];
	char patient_gender[MAXGENDER+1];
	int patient_age;
	char patient_confirmed_positive_date[MAXSIZE+1];
	char patient_status[MAXSIZE+1];
	bool del;
};

// function prototype
void getPatient(Patient [], int& );
void addPatient(Patient [], int& );
void storeFile(const Patient [], int );
void deleting(Patient [], int );
void listPatient(const Patient [], int );

int main()
{
	Patient patientList[MAXPATIENT];	// declare array of struture Patient
	int sizeData;						// size of array
	char ch, choice;
	
	getPatient(patientList, sizeData);
	
	do	// allow user doing more than 1 operation
	{
	cout<<"************************************************************************"<<endl;
	cout<<"Welcome to the program"<<endl;
	cout<<"What do you want to do with this program?"<<endl;
	cout<<"1. Add a new patient"<<endl;
	cout<<"2. Delete a patient (If swap is negative or is admitted to CPRC unit)"<<endl;
	cout<<"3. Exit the program"<<endl;
	cout<<"************************************************************************"<<endl;
	cout<<"Please enter number 1, 2 or 3 to proceed: ";
	cin>>choice;
	
	while(choice!='1'&&choice!='2'&&choice!='3')	// input validation
	{
		cout<<"\nI'm sorry but the valid choice is only 1, 2 or 3. Please try again"<<endl;
		cout<<"Please enter number 1, 2 or 3 to proceed: ";
		cin>>choice;
	}
	
	cout<<endl;

	switch(choice)	// call function that the user select
	{
		case '1':
			    addPatient(patientList, sizeData);	// function call for add patient
			    sizeData++;
			    break;
		case '2':
				deleting(patientList, sizeData);	// function call for remove patient
				storeFile(patientList, sizeData);	// function call for rewrite text file
				break;
		case '3':
				exit(EXIT_SUCCESS);					// exit program
				break;
	}	
	
	do
	{
		cout<<"\nDo you want to do another operation? If yes, please enter Y, if not please enter N: ";
		cin>>ch;
		
	}while(toupper(ch)!='Y'&&toupper(ch)!='N');		
	
	cout<<endl;
	
	}while(toupper(ch)=='Y');	
	
	return 0;
}

// *******************************************************************
// getPatient
// task		: to read in the data from a text file to a struct
// data in	: a Patient structure and size of the array structure
// data out	: none
// *******************************************************************

void getPatient (Patient p[], int& size)
{
    ifstream inFile; 				// declaring an in filestream called infile
    inFile.open ("patient.txt");  	// opening file named patient.txt
    int i;
    	
    inFile.ignore(200, '\n');		// ignore first line
    
    for (i = 0; inFile; i++) 		// loop your array of patient
    {
     	inFile.get(p[i].patient_name, MAXNAME+1);
		inFile>>p[i].patient_ID;
		inFile.ignore(5);
		inFile.get(p[i].patient_address, MAXADDRESS+1);
		inFile.get(p[i].patient_gender, MAXGENDER+1);
		inFile>>p[i].patient_age;
		inFile.ignore(8);
		inFile.get(p[i].patient_confirmed_positive_date, MAXSIZE+1);
		inFile.ignore(3);
		inFile.get(p[i].patient_status, MAXSIZE+1);
		
		p[i].del=false;
		
		inFile.ignore(80, '\n');
    }
    	
    size=i-1;

    inFile.close();
    
    return;
}

// *******************************************************************
// addPatient
// task		: to add a new patient to the Patient struct
// data in	: a Patient structure and size of the array structure
// data out	: none
// *******************************************************************

void addPatient(Patient p[], int& size)
{
	cout<<"Please enter the information of the new patient."<<endl;
	
	cout<<"Name\t\t\t\t\t: ";
	cin.ignore();
	cin.getline(p[size].patient_name, MAXNAME+1);
	
	cout<<"ID number (eg: 223)\t\t\t: ";
	cin>>p[size].patient_ID; 
	
	cout<<"Address\t\t\t\t\t: ";
	cin.ignore();
	cin.getline(p[size].patient_address, MAXADDRESS+1);
	
	cout<<"Gender (Male or Female)\t\t\t: ";
	cin.getline(p[size].patient_gender, MAXGENDER+1);
	
	cout<<"Age\t\t\t\t\t: ";
	cin>>p[size].patient_age;
	
	cout<<"Confirmed positive date (dd/mm/yyyy)\t: ";
	cin.ignore();
	cin.getline(p[size].patient_confirmed_positive_date, MAXSIZE+1);
	
	cout<<"Severity status\t\t\t\t: ";
	cin.getline(p[size].patient_status, MAXSIZE+1);
	
	// write title
	if(size==0)
	{
	ofstream outFile("patient.txt");
	outFile<<left<<"     "<<setw(25)<<"Name"<<"ID"<<"          "<<setw(30)<<"Address";
	outFile<<setw(10)<<"Gender"<<setw(5)<<"Age"<<setw(20)<<"ConfirmedPositiveDate";
	outFile<<"     "<<setw(20)<<"Severity Satus"<<endl;
	outFile.close();
	}
	
	// write in the file
	ofstream outFile("patient.txt", ios::app);	// open file patient
	
	outFile<<left<<setw(30)<<p[size].patient_name;
	outFile<<p[size].patient_ID<<"     ";
	outFile<<setw(35)<<p[size].patient_address;
	outFile<<setw(10)<<p[size].patient_gender;
	outFile<<p[size].patient_age<<"        ";
	outFile<<setw(20)<<p[size].patient_confirmed_positive_date;
	outFile<<"   "<<setw(20)<<p[size].patient_status;
	outFile<<endl;
	
	outFile.close();
	
	return;
}

// *******************************************************************
// deleting
// task		: to remove a patient 
// data in	: a Patient structure and size of the array structure
// data out	: none
// *******************************************************************

void deleting(Patient p[], int size)
{
	int tempId, a;
	
	cout<<"Please enter the ID number of the patient you want to delete: ";
	cin>>tempId;
	
	cout<<"Deleting..."<<endl;
	
	for(int i=0;i<size;i++)
	{
		if(p[i].patient_ID==tempId)
		{
			p[i].del=true;	// set the record in status deleted
			a=i;
		}
	}
	
	cout<<"The record of the patient have been deleted if it exist"<<endl;
	
	return;
}

// *******************************************************************
// storeFile
// task		: to write the data of struct into text file
// data in	: a Patient structure and size of the array structure
// data out	: none
// *******************************************************************

void storeFile(const Patient p[], int size)
{
	ofstream outFile;
	
	outFile.open("patient.txt"); // open file patient
	
	outFile<<left<<"     "<<setw(25)<<"Name"<<"ID"<<"          "<<setw(30)<<"Address";
	outFile<<setw(10)<<"Gender"<<setw(5)<<"Age"<<setw(20)<<"ConfirmedPositiveDate";
	outFile<<"     "<<setw(20)<<"Severity Satus"<<endl;
	
	for(int i=0;i<size;i++)
	{
		if(p[i].del)			// skip the deleted record of patient
			continue;	
			
		outFile<<setw(30)<<p[i].patient_name;
		outFile<<p[i].patient_ID<<"     ";
		outFile<<setw(35)<<p[i].patient_address;
		outFile<<setw(10)<<p[i].patient_gender;
		outFile<<p[i].patient_age<<"        ";
		outFile<<setw(20)<<p[i].patient_confirmed_positive_date;
		outFile<<"   "<<setw(20)<<p[i].patient_status;
		outFile<<endl;
	}
	
	outFile.close();
	
	return;
}
