/*
 * Driver.cpp
 *
 *  Created on: 2017-11-10
 *      Author: David (DPigeon)
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "stdlib.h"
#include <sstream>
#include <string>
#include "Date.h"

using namespace std;

//Variables
int oldSizeI, oldSizeF, oldSizeC, oldSizeD = 0; //all of the old size variables that needs to be updated
int maxDates = 100; //Max size of the date list array
string dType = ""; //Field 1
int dSize = 0; //Field 2
int *iPtr = NULL; //array for the integers
float *fPtr = NULL; //array for the floats
char *cPtr = NULL; //array for the characters
Date *dPtr = new Date[maxDates]; //array for the dates using the teachers class Date

//Functions
void getRecords(ifstream&, ofstream&);

int main(int argc, char *argv[]){
	if(argc < 1){ //looks if there is a path to the file
		cout<<"Please provide the full file path correctly."<<endl;
		exit(1);
	}
	for(int i = 0; i < argc; i++){
		cout<<"argv["<<i<<"] "<<argv[i]<<endl; //displays the path and file name
	}
    ifstream myFile;
    myFile.open(argv[1]); //opens the file
    if (!myFile) { //if its not open
       cout<<"My file could not be opened."<<endl;
       exit(1); //terminate
    }
    ofstream reversedFile;
    reversedFile.open(argv[2]); //opens the other file by creating it to copy
    if (!reversedFile) { //if its not open
       cout<<"Reversed file could not be opened."<<endl;
       exit(1); //terminate
    }
    getRecords(myFile, reversedFile); //calling the function
    //Deletes everything at the end
    delete[] dPtr;
    delete[] iPtr;
    delete[] cPtr;
    delete[] fPtr;
    myFile.close(); //close the file
    reversedFile.close();
	return 0;
}

//look if the size is not the right one with the field 3 with throw exception & catch

void getRecords(ifstream& myFile, ofstream& reversedFile){ //file already opened
	while(myFile>>dType){ //while we get a string (int, char, date or float)
		if(dType == "int"){ //if the first line value is an integer
			if(iPtr == 0){ //empty
				myFile>>dSize;
				oldSizeI = dSize;
				iPtr = new int[dSize]; //initializing the array
				//The next step looks if the size (field 2) is equal to the amount of number(s)
				//on its right. If not, throw exception handling.
				int count = 0; //integer count to know the real amount of integers in field 3
				int n;
				int pos = myFile.tellg(); //gets current file pointer position
				while(myFile>>n)
					count++; //counts number of integers in field 3
				myFile.clear();
				myFile.seekg(pos); //goes back to the position before to get the numbers into the array
				try {
					if(count != dSize)
						throw dSize;
					for(int i = 0; i < dSize; i++)
						myFile>>iPtr[i]; //inserts the float in the array
				} catch (int i){
					cout<<"Exception: The current size is "<<i<<" but field 3 contains "<<count<<" numbers so it has the wrong size."<<endl;
				}
			} else if(iPtr != 0) { //if not empty
				myFile>>dSize;
				int s = dSize + oldSizeI; //updating the size
				int *temp = NULL;
				temp = new int[s];
				int count = 0; //integer count to know the real amount of integers in field 3
				int n;
				int pos = myFile.tellg(); //gets current file pointer position
				while(myFile>>n)
					count++;
				myFile.clear();
				myFile.seekg(pos); //goes back to the position before to get the numbers into the array
				try {
					if(count != dSize)
						throw dSize;
					for(int i = 0; i < oldSizeI; i++)
						temp[i] = iPtr[i]; //inserts the old array into temp one
					for(int j = oldSizeI; j < s; j++)
						myFile>>temp[j]; //inserts the rest into temp
					iPtr = new int[s];
					for(int k = 0; k < s; k++)
						iPtr[k] = temp[k]; //copy everything back to the old array
					oldSizeI = s; //updating the old size after
				} catch (int i){
					cout<<"Exception: The current size is "<<i<<" but field 3 contains "<<count<<" numbers so it has the wrong size."<<endl;
				}
			}
			//This part reverses the integers in the other file called reserve.dat
			reversedFile<<dType<<" "<<dSize<<" ";
			if(dSize == oldSizeI){ //array was empty originally
				for(int i = dSize-1; i >= 0; i--)
					reversedFile<<iPtr[i]<<" "; //writes to the file backwards
				reversedFile<<endl; //skips to next line
			} else if(dSize != oldSizeI){
				for(int i = oldSizeI-1; i >= oldSizeI-dSize; i--) //we need from the oldSize to oldSize - its original dSize at beginning
					reversedFile<<iPtr[i]<<" ";
				reversedFile<<endl;
			}
		}
		else if(dType == "float"){ //if the first line value is a float
			if(fPtr == 0){ //empty
				myFile>>dSize;
				oldSizeF = dSize;
				fPtr = new float[dSize]; //initializing the array
				int count = 0; //integer count to know the real amount of integers in field 3
				float n;
				int pos = myFile.tellg(); //gets current file pointer position
				while(myFile>>n)
					count++; //counts the number of float in field 3
				myFile.clear();
				myFile.seekg(pos); //goes back to the position before to get the numbers into the array
				try {
					if(count != dSize)
						throw dSize;
					for(int i = 0; i < dSize; i++)
						myFile>>fPtr[i]; //inserts the float in the array
				} catch (int i){
					cout<<"Exception: The current size is "<<i<<" but field 3 contains "<<count<<" numbers so it has the wrong size."<<endl;
				}
			} else if(fPtr != 0) { //if not empty
				myFile>>dSize;
				int s = dSize + oldSizeF; //updating the size
				float *temp = NULL;
				temp = new float[s];
				int count = 0; //integer count to know the real amount of integers in field 3
				float n;
				int pos = myFile.tellg(); //gets current file pointer position
				while(myFile>>n)
					count++;
				myFile.clear();
				myFile.seekg(pos); //goes back to the position before to get the numbers into the array
				try {
					if(count != dSize)
						throw dSize;
					for(int i = 0; i < oldSizeF; i++)
						temp[i] = fPtr[i]; //inserts the old array into temp one
					for(int j = oldSizeF; j < s; j++)
						myFile>>temp[j]; //inserts the rest into temp
					fPtr = new float[s];
					for(int k = 0; k < s; k++)
						fPtr[k] = temp[k]; //copy everything back to the old array
					oldSizeF = s; //updating the old size after
				} catch (int i){
					cout<<"Exception: The current size is "<<i<<" but field 3 contains "<<count<<" numbers so it has the wrong size."<<endl;
				}
			}
			//This part reverses the floats in the other file called reserve.dat
			reversedFile<<dType<<" "<<dSize<<" ";
			if(dSize == oldSizeF){ //array was empty originally
				for(int i = dSize-1; i >= 0; i--)
					reversedFile<<fPtr[i]<<" "; //writes to the file backwards
				reversedFile<<endl; //skips to next line
			} else if(dSize != oldSizeF){
				for(int i = oldSizeF-1; i >= oldSizeF-dSize; i--) //we need from the oldSize to oldSize - its original dSize at beginning
					reversedFile<<fPtr[i]<<" ";
				reversedFile<<endl;
			}
		}
		else if(dType == "char"){ //if the first line value is a character
			if(cPtr == 0){ //empty
				myFile>>dSize;
				oldSizeC = dSize;
				cPtr = new char[dSize]; //initializing the array
				int count = 0; //integer count to know the real amount of integers in field 3
				char n;
				string s;
				int pos = myFile.tellg(); //gets current file pointer position
				while(myFile>>n){
					int pos2 = myFile.tellg(); //gets the file pointer position to come back to the char
					myFile>>s;
					if(s == "int" || s == "char" || s == "Date" || s == "float"){ //if encounter next line, count and stop
						count++;
						break;
					}
					myFile.clear();
					myFile.seekg(pos2);
					count++;
				}
				myFile.clear();
				myFile.seekg(pos); //goes back to the position before to get the numbers into the array
				try {
					if(count != dSize)
						throw dSize;
					for(int i = 0; i < dSize; i++)
						myFile>>cPtr[i]; //inserts the float in the array
				} catch (int i){
					cout<<"Exception: The current size is "<<i<<" but field 3 contains "<<count<<" numbers so it has the wrong size."<<endl;
				}
				} else if(cPtr != 0) { //if not empty
					myFile>>dSize;
					int s = dSize + oldSizeC; //updating the size
					char *temp = NULL;
					temp = new char[s];
					for(int i = 0; i < oldSizeC; i++)
						temp[i] = cPtr[i]; //inserts the old array into temp one
					for(int j = oldSizeC; j < s; j++)
						myFile>>temp[j]; //inserts the rest into temp
					cPtr = new char[s];
					for(int k = 0; k < s; k++)
						cPtr[k] = temp[k]; //copy everything back to the old array
					oldSizeC = s; //updating the old size after
				}
			//This part reverses the characters in the other file called reserve.dat
			reversedFile<<dType<<" "<<dSize<<" ";
			if(dSize == oldSizeC){ //array was empty originally
				for(int i = dSize-1; i >= 0; i--)
					reversedFile<<cPtr[i]<<" "; //writes to the file backwards
				reversedFile<<endl; //skips to next line
			} else if(dSize != oldSizeC){
				for(int i = oldSizeC-1; i >= oldSizeC-dSize; i--) //we need from the oldSize to oldSize - its original dSize at beginning
					reversedFile<<cPtr[i]<<" ";
				reversedFile<<endl;
			}
		}
		else if(dType == "Date"){ //if the first line value is a Date
			 if(oldSizeD == 0){ //if empty
				myFile>>dSize;
				oldSizeD = dSize;
				dPtr = new Date[dSize]; //initializing the array
				int count = 0; //integer count to know the real amount of integers in field 3
				int y, m, d;
				char da;
				int pos = myFile.tellg(); //gets current file pointer position
				while(myFile>>y>>da>>m>>da>>d) //reads the date Y-M-D and counts it
					count++; //counts number of integers in field 3
				myFile.clear();
				myFile.seekg(pos); //goes back to the position before to get the numbers into the array
				try {
					if(count != dSize)
						throw dSize;
					for(int i = 0; i < dSize; i++){ //need to read integer, skip -, read integer, skip dash and read last integer
						int year;
						int month;
						int day;
						char dash;
						myFile>>year>>dash>>month>>dash>>day;
						Date d(year, month, day);
						dPtr[i] = d;
					}
				} catch (int i){
					cout<<"Exception: The current size is "<<i<<" but field 3 contains "<<count<<" numbers so it has the wrong size."<<endl;
				}
			 } else if(oldSizeD > 0) { //if not empty
					myFile>>dSize;
					int s = dSize + oldSizeD; //updating the size
					Date *temp = new Date[s];
					int count = 0; //integer count to know the real amount of integers in field 3
					int y, m, d;
					char da;
					int pos = myFile.tellg(); //gets current file pointer position
					while(myFile>>y>>da>>m>>da>>d) //reads the date Y-M-D and counts it
						count++; //counts number of integers in field 3
					myFile.clear();
					myFile.seekg(pos); //goes back to the position before to get the numbers into the array
					try {
						if(count != dSize)
							throw dSize;
						for(int i = 0; i < oldSizeD; i++)
							temp[i] = dPtr[i]; //inserts the old array into temp one
						for(int j = oldSizeD; j < s; j++){
							int year;
							int month;
							int day;
							char dash;
							myFile>>year>>dash>>month>>dash>>day;
							Date d(year, month, day);
							temp[j] = d;
						}
						dPtr = new Date[s];
						for(int k = 0; k < s; k++)
							dPtr[k] = temp[k]; //copy everything back to the old array
						oldSizeD = s; //updating the old size after
					} catch (int i){
						cout<<"Exception: The current size is "<<i<<" but field 3 contains "<<count<<" numbers so it has the wrong size."<<endl;
			 		}
				}
			 //This part reverses the Dates in the other file called reserve.dat
			 reversedFile<<dType<<" "<<dSize<<" ";
			 if(dSize == oldSizeD){ //array was empty originally
			 	for(int i = dSize-1; i >= 0; i--)
			 		reversedFile<<dPtr[i]<<" "; //writes to the file backwards with the << operator
			 	reversedFile<<endl; //skips to next line
			 } else if(dSize != oldSizeD){
			 	for(int i = oldSizeD-1; i >= oldSizeD-dSize; i--) //we need from the oldSize to oldSize - its original dSize at beginning
			 		reversedFile<<dPtr[i]<<" ";
			 	reversedFile<<endl;
			 }
		}
		else if(dType != "int" || dType != "float" || dType != "char" || dType != "Date"){ //otherwise
			cout<<"Your file cannot be used because it is using an invalid field 1 type and this type's name is '"<<dType<<"'."<<endl;
			exit(1); //terminates
		}
	}
	myFile.clear();
	myFile.seekg(0, ios::beg); //goes back to the beginning of the file
}

