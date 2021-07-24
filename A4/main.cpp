//
//  main.cpp
//  A4
//
//  Created by Nicholas Buras on 7/19/21.
//

#include <iostream>
#include <cmath>
#include <fstream>

//40 indexes
// 0
// 50000
// 100000
// 150000 etc

void mergeSort(int*,int,int);
void merge(int*,int,int,int);
void findIndexes(int*,int*,int,int);

int main(int argc, const char * argv[]) {
    
    const char* inputFileName = argv[1];
    std::ifstream inputFile;
    std::fstream outputBinaryFile;
    int totalNums = 2000000;
    int increment = 50000;
    int* myIndexes;
    int myNumbers[totalNums];
    int tempNum;
    
    //open file and populate array
    inputFile.open(inputFileName);
    if(!inputFile.is_open()){
        std::cout << "File could not be opened sorry." << std::endl;
    } else {
        //populate array
        for(int index = 0; index < totalNums; index++){
            inputFile >> tempNum;
            myNumbers[index] = tempNum;
        }
        //close file
        inputFile.close();
    }
    
    //sort array
    mergeSort(myNumbers, 0, totalNums-1);
    
    //find indexes
    myIndexes = new int[totalNums/increment]; //array to hold in
    findIndexes(myNumbers,myIndexes,increment,totalNums);
    
    //open and write to binary file
    outputBinaryFile.open("sortedBinaryData.dat", std::ios::in|std::ios::out|std::ios::binary); //open for binary, input and output
    outputBinaryFile.write((char*)myNumbers, sizeof(int)*totalNums);
    
    /* ############################   OUTPUT   ############################ */
    
    //get output from binary file using indexes
    //int numOffset = 4;
    int desiredIndex;
    int jump;
    int outputNumber = 0;
    
    //102nd num from 1st index (50,101st number)
    outputBinaryFile.seekg(std::ios::beg); //reset file pointer to beg
    desiredIndex = 1;
    //find where to set file pointer
    jump = (desiredIndex*increment) + 102;
    //move file pointer
    outputBinaryFile.seekg(std::ios::beg+jump);
    //read into variable
    outputBinaryFile.read((char*)outputNumber, sizeof(int));
    //print to screen
    std::cout << "102nd number from 1st index: " <<outputNumber << std::endl;
    
    //31st num from 10th index (500,0031st number)
    outputBinaryFile.seekg(std::ios::beg); //reset file pointer to beg
    desiredIndex = 10;
    //find where to set file pointer
    jump = (desiredIndex*increment) + 31;
    //move file pointer
    outputBinaryFile.seekg(std::ios::beg+jump);
    //read into variable
    outputBinaryFile.read((char*)&outputNumber, sizeof(int));
    //print to screen
    std::cout << "31st number from 10th index: " <<outputNumber << std::endl;
    
    //3,105th num from 34th index (1,703,105th number)
    outputBinaryFile.seekg(std::ios::beg); //reset file pointer to beg
    desiredIndex = 34;
    //find where to set file pointer
    jump = (desiredIndex*increment) + 3105;
    //move file pointer
    outputBinaryFile.seekg(std::ios::beg+jump);
    //read into variable
    outputBinaryFile.read((char*)&outputNumber, sizeof(int));
    //print to screen
    std::cout << "3105st number from 34th index: " <<outputNumber << std::endl;
    
    //431st num from 21st index (1,050,431st number)
    outputBinaryFile.seekg(std::ios::beg); //reset file pointer to beg
    desiredIndex = 21;
    //find where to set file pointer
    jump = (desiredIndex*increment) + 431;
    //move file pointer
    outputBinaryFile.seekg(std::ios::beg+jump);
    //read into variable
    outputBinaryFile.read((char*)&outputNumber, sizeof(int));
    //print to screen
    std::cout << "431st number from 21st index: " <<outputNumber << std::endl;
    
    //42,971st num from 18th index (50,101st number)
    outputBinaryFile.seekg(std::ios::beg); //reset file pointer to beg
    desiredIndex = 18;
    //find where to set file pointer
    jump = (desiredIndex*increment) + 42971;
    //move file pointer
    outputBinaryFile.seekg(std::ios::beg+jump);
    //read into variable
    outputBinaryFile.read((char*)&outputNumber, sizeof(int));
    //print to screen
    std::cout << "102nd number from 1st index: " <<outputNumber << std::endl;
    
    //close file
    outputBinaryFile.close();
}

/* ############################   FUNCTIONS   ############################ */

/*
 **    Author: Nick Buras
 **    Function Purpose: sort array using mergesort algo
 **
 **    Function Output: sorted array in ascending order
 **    Side Effects: None
 */
//Not in place, lots of memory used :( still looking at the algo book for that one
void mergeSort(int* inArray, int left, int right) {
    if(left >= right){
        return;
    }
    int middle = floor((left+right)/2);
    mergeSort(inArray, left, middle); //left side
    mergeSort(inArray, middle+1, right); //right side
    merge(inArray, left, middle, right); //merge back
}

/*
 **    Author: Nick Buras
 **    Function Purpose: merge sorted sublists back together
 **
 **    Function Output: sorted array
 **    Side Effects: temporary array is created/destroyed to help with algo
 */
void merge(int* inArray, int left, int middle, int right) {
    //temp array for sorting
    int* tempArray = new int[(right-left)+1];
    int leftStart = left;
    int rightStart = middle + 1;
    int tempArrayIndex = 0;
    
    while (leftStart <= middle && rightStart <= right) {
        if(inArray[leftStart] <= inArray[rightStart]){
            tempArray[tempArrayIndex] = inArray[leftStart];
            leftStart++;
            tempArrayIndex++;
        } else {
            tempArray[tempArrayIndex] = inArray[rightStart];
            rightStart++;
            tempArrayIndex++;
        }
    }
    //add any remaining from left
    while (leftStart <= middle) {
        tempArray[tempArrayIndex] = inArray[leftStart];
        leftStart++;
        tempArrayIndex++;
    }
    //add any remaining from right
    while (rightStart <= right) {
        tempArray[tempArrayIndex] = inArray[rightStart];
        rightStart++;
        tempArrayIndex++;
    }
    //reset index for reuse
    tempArrayIndex = 0;
    //copy back to original array
    for(int index = left; index <= right; index++){
        inArray[index] = tempArray[tempArrayIndex];
        tempArrayIndex++;
    }
    //release memory from allocated temporary array
    delete []tempArray;
}

/*
 **    Author: Nick Buras
 **    Function Purpose: find indexes according to assignment requirements, 50,000 in size
 **
 **    Function Output: populate index array to reference for output
 **    Side Effects: index array is populated
 */
void findIndexes(int* myArray, int* indexArray, int increment, int size) {
    //0s offset is 0
    indexArray[0] = 0;
    //calculate rest
    int index = 1;
    int inc = increment;
    
    for(int ctr = 0; ctr < size; ctr++) {
        if(myArray[ctr] >= inc){
            //place index of that number(1st in new index container) into the index array
            indexArray[index] = ctr;
            //increment index array index
            index++;
            //increment the increment value
            inc += increment;
        }
    }
}
