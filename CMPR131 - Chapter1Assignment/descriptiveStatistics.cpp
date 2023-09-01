#include <iostream>
#include <string>
#include <iomanip>
#include "descriptiveStatistics.h"
#include "input.h"
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std; 

void displayDescriptiveStatisticsMenu()
{
	cout << "3> Descriptive Statistics" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "A> Read, store, and display data set   M> Mid Range" << endl;
	cout << "B> Minimum                             N> Quartiles " << endl;
	cout << "C> Maximum                             O> Interquartile Range" << endl;
	cout << "D> Range                               P> Outliers" << endl;
	cout << "E> Size                                Q> Sum of Squares" << endl;
	cout << "F> Sum                                 R> Mean Absolute Deviation" << endl;
	cout << "G> Mean                                S> Root Mean Square" << endl;
	cout << "H> Median                              T> Standard Error of the Mean" << endl;
	cout << "I> Frequencies                         U> Coefficient of Variation" << endl;
	cout << "J> Mode                                V> Relative Standard Deviation" << endl;
	cout << "K> Standard Deviation                  W> Display and write all results to text file" << endl;
	cout << "L> Variance                                         " << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "X. Return" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "Option: ";
}

void insertSorted(int*& arr, int& n, int num) {
	int* newArr = new int[n + 1];

	int i;
	for (i = 0; i < n; ++i) {
		if (arr[i] > num) break;
		newArr[i] = arr[i];
	}

	newArr[i] = num;

	for (; i < n; ++i) {
		newArr[i + 1] = arr[i];
	}

	delete[] arr;
	arr = newArr;
	++n;
}

void readIntsFromFile(const string& filename, int*& arrayInts, int& count) {
	ifstream file(filename);

	if (!file.is_open()) {
		throw runtime_error("Unable to open the file");
	}

	count = 0;
	int number;

	while (file >> number) {
		insertSorted(arrayInts, count, number);
	}

	file.close();
}

int findMinimum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find minimum.");
	}

	int minVal = numeric_limits<int>::max();
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] < minVal) {
			minVal = arrayInts[i];
		}
	}

	return minVal;
}

int findMaximum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find maximum.");
	}

	int maxVal = numeric_limits<int>::min();
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] > maxVal) {
			maxVal = arrayInts[i];
		}
	}

	return maxVal;
}

double calculateAverage(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot calculate average.");
	}

	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return static_cast<double>(sum) / count;
}

double calculateStandardDeviation(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot calculate standard deviation.");
	}

	double mean = calculateAverage(arrayInts, count);
	double sumOfSquares = 0;

	for (int i = 0; i < count; ++i) {
		sumOfSquares += (arrayInts[i] - mean) * (arrayInts[i] - mean);
	}

	return sqrt(sumOfSquares / count);
}

int findSum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find sum.");
	}

	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return sum;
}

double findMean(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find mean.");
	}

	return calculateAverage(arrayInts, count);  // You can directly use calculateAverage
}

double findMedian(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find median.");
	}

	sort(arrayInts, arrayInts + count);

	if (count % 2 == 0) {
		return (arrayInts[count / 2 - 1] + arrayInts[count / 2]) / 2.0;
	}
	else {
		return arrayInts[count / 2];
	}
}

int findRange(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty; cannot find range.");
	}

	int minVal = arrayInts[0];
	int maxVal = arrayInts[0];

	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] < minVal) minVal = arrayInts[i];
		if (arrayInts[i] > maxVal) maxVal = arrayInts[i];
	}

	return maxVal - minVal;
}

int descriptiveStatistics() {
	int* arrayInts = nullptr;
	int count = 0;
	char option;

	do {
		displayDescriptiveStatisticsMenu();
		cin >> option;

		switch (toupper(option)) 
		{

		case 'A': // read, store and display into sorted dynamic array

			system("cls");
		{
			string filename;
			cout << "Please enter the filename: ";
			cin >> filename;
			readIntsFromFile(filename, arrayInts, count);
			system("pause");
			system("cls");
			break;
		}

		case 'B': // minimum

			system("cls");
			try {
				int minVal = findMinimum(arrayInts, count);
				cout << "The minimum value of the given data set is: " << minVal << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'C': // maximum

			system("cls");
			try {
				int maxVal = findMaximum(arrayInts, count);
				cout << "The maximum value of the given data set is: " << maxVal << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'D': // range

			system("cls");
			try {
				int range = findRange(arrayInts, count);
				cout << "The range of the given data set is: " << range << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'E': // size

			system("cls");
			cout << "The size of the given data set is: " << count << endl;
			system("pause");
			system("cls");
			break;

		case 'F': // sum

			system("cls");
			try {
				int sum = findSum(arrayInts, count);
				cout << "The sum of the given data set is: " << sum << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'G': // mean

			system("cls");
			try {
				double meanVal = findMean(arrayInts, count);
				cout << "The mean of the given data set is: " << meanVal << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'H': // median

			system("cls");
			try {
				double median = findMedian(arrayInts, count);
				cout << "The median of the given data set is: " << median << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'I': // frequencies

			system("cls");
			cout << "frequencies" << endl;
			system("pause");
			system("cls");
			break;

		case 'J': // mode

			system("cls");
			cout << "mode" << endl;
			system("pause");
			system("cls");
			break;

		case 'K': // standard deviation

			system("cls");
			try {
				double stddev = calculateStandardDeviation(arrayInts, count);
				cout << "The standard deviation of the given data set is: " << stddev << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			break;
			system("pause");
			system("cls");
			break;

		case 'L': // variance

			system("cls");
			cout << "variance" << endl;
			system("pause");
			system("cls");
			break;

		case 'M': // midrange

			system("cls");
			cout << "mid range" << endl;
			system("pause");
			system("cls");
			break;

		case 'N': // quartiles

			system("cls");
			cout << "quartiles" << endl;
			system("pause");
			system("cls");
			break;

		case 'O': // interquartile range

			system("cls");
			cout << "interquartile range" << endl;
			system("pause");
			system("cls");
			break;

		case 'P': // outliers

			system("cls");
			cout << "outliers" << endl;
			system("pause");
			system("cls");
			break;

		case 'Q': // sum of squares

			system("cls");
			cout << "sum of squares" << endl;
			system("pause");
			system("cls");
			break;

		case 'R': // mean absolute deviation

			system("cls");
			cout << "mean absolute deviation" << endl;
			system("pause");
			system("cls");
			break;

		case 'S': // root mean square

			system("cls");
			cout << "root mean square" << endl;
			system("pause");
			system("cls");
			break;

		case 'T': // standard error of the mean

			system("cls");
			cout << "standard error of the mean" << endl;
			system("pause");
			system("cls");
			break;

		case 'U': // coefficient of variation

			system("cls");
			cout << "coefficient of varitaion" << endl;
			system("pause");
			system("cls");
			break;

		case 'V': // relative standard deviation

			system("cls");
			cout << "relative standard deviation" << endl;
			system("pause");
			system("cls");
			break;

		case 'W': // display all results and write to an output text file

			system("cls");
			cout << "display all results and write to an output text file" << endl;
			system("pause");
			system("cls");
			break;

		case 'X': // exit

			cout << "Exiting to previous menu." << endl;
			break;

		default: // invalid option

			cout << "Invalid option. Please try again." << endl;
			system("pause");
			system("cls");
			break;

		}

	} 
	while (toupper(option) != 'X');
	delete[] arrayInts;
	return 0;
}