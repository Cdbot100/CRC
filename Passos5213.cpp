//Passos5213.cpp : Defines the entry point for the console application.
//Scott Gordon  
//CMPS 5213, Wireless Networks, Dr. Nelson Passos
//This Program computes CRC-16 appends checkbits and then computes CRC-12 
#include "stdafx.h"										//standard includes & empty header
#include <iostream>
#include <string>
using namespace std;
int poly16 = 0x8005, seed16 = 0xFFFF, coef16 = 0x8000, add16 = 8;//Polynomial, seed = all ones for final AND
int poly12 = 0x80F, seed12 = 0xFFF, coef12 = 0x800, add12 = 4;//coef = left most 1 in correct size hex value  
unsigned check(unsigned *data, int length, int poly, int coef, int seed, int add){
	unsigned bits = 0;									//start with 0
	for (int s = length; s >= 1; s--) {		//for each letter
		bits ^= (*data++ << add);						//advance to the end of 8 bits & add for 16 or 12 
		for (int c = 1; c <= 8; c++)				//for all 8 bits check
			bits = (bits & coef) ? (bits << 1) ^ poly : (bits << 1);
	}													          //if coeffiecent is 1 then XOR 
	return bits & seed;									//final AND with seed value (all ones)
}														
int _tmain(int argc, _TCHAR* argv[]){
	string in;										    	//handle for input
	unsigned A, T[160];									//placeholders for Data && CRC checkbits
	cout << "Enter Message:" << uppercase << hex;
	getline(cin, in);									  //read in string
		for (int c = 0; c < in.length(); c++){
			T[c] = in.at(c);
		}												          //place char values into int array	
	A = check(T, in.length(), poly16, coef16, seed16, add16);//CRC16("A") = 186
	T[in.length() + 1] = A & 0xff;						//break CRC16(in) = A into two hex values
	T[in.length()] = (A >> 8) & 0xff;					//IE: 0x1813 = 0x18, 0x13
	cout << "Transmission:";							    //CRC12("C") = A9B
	T[(in.length() + 2)] = check(T, (in.length() + 2), poly12, coef12, seed12, add12);
		for (int c = 0; c <= in.length() + 2; c++){		//CRC12("NELSON") = DBD
			cout << int(T[c]);							//print
		}												//CRC12(CRC16("NELSON")) = 1813 2A1											
	cout << endl;									
	system("pause");									
	return 0;
}


