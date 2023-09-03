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
#include <sstream>

using namespace std; 

// PRECONDITION: none
// POSTCONDITION: the menu options for descriptive statistics are displayed on the standard output.
void displayDescriptiveStatisticsMenu()
{
	// displays the menu options for descriptive statistics
	cout << "3> Descriptive Statistics" << endl;
	cout << "************************************************************" << endl;
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
	cout << "************************************************************" << endl;
	cout << "X. Return" << endl;
	cout << "************************************************************" << endl;
	cout << "Option: ";
}

// PRECONDITION: the 'array' should be a dynamically allocated array sorted in ascending order, 'size' should represent the number of elements in 'array'.
// POSTCONDITION: 'array' will be resized, and 'element' will be inserted in a way that keeps the array sorted, 'size' will be incremented by 1 to reflect the new size of the array.
void insertSorted(int*& array, int& size, int element) {
	int* tempArray = new int[size + 1];
	int pos = 0;

	// find the position to insert the new element in sorted order
	for (pos = 0; pos < size; ++pos) {
		if (array[pos] > element)
			break;
	}

	// copy elements to tempArray up to the insertion position
	for (int i = 0; i < pos; ++i) {
		tempArray[i] = array[i];
	}

	// insert new element
	tempArray[pos] = element;

	// Copy remaining elements
	for (int i = pos + 1; i < size + 1; ++i) {
		tempArray[i] = array[i - 1];
	}

	// free old array memory and update array pointer and size
	delete[] array;
	array = tempArray;
	++size;
}

// PRECONDITION: 'filename' should be a valid file name, 'arrayInts' should be a pointer to an array of integers, 'count' should be an integer representing the number of elements in 'arrayInts'.
// POSTCONDITION: 'arrayInts' will be resized to hold the integers read from the file, 'count' will be updated to reflect the new size of 'arrayInts'.
void readIntsFromFile(const string& filename, int*& arrayInts, int& count) {
	ifstream file(filename);

	if (!file.is_open()) {
		throw runtime_error("Unable to open the file");
	}

	count = 0;
	int number;
	// read the integers from the file and store them in the array
	while (file >> number) {
		insertSorted(arrayInts, count, number);
	}

	file.close();
}

// PRECONDITION: 'array' should be a dynamically allocated array of integers, 'size' should represent the number of elements in 'array'.
// POSTCONDITION: 'array' will be displayed on the standard output.
void displayArray(int* array, int size) {
	// display the integers in the array
	cout << "Stored integers in sorted order: ";
	for (int i = 0; i < size; ++i) {
		cout << array[i];
		if (i < size - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: finds the minimum value in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
int findMinimum(int* arrayInts, int count) {
	if (count == 0) {
		//	throw an error if the array is empty
		throw runtime_error("The array is empty, cannot find minimum.");
	}

	int minVal = numeric_limits<int>::max();
	// find the minimum value in the array
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] < minVal) {
			minVal = arrayInts[i];
		}
	}

	return minVal;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: finds the maximum value in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
int findMaximum(int* arrayInts, int count) {
	if (count == 0) {
		// throw an error if the array is empty
		throw runtime_error("The array is empty, cannot find maximum.");
	}

	int maxVal = numeric_limits<int>::min();
	// find the maximum value in the array
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] > maxVal) {
			maxVal = arrayInts[i];
		}
	}

	return maxVal;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the average of the values in 'arrayInts' and returns it as a double, throws an error if 'arrayInts' is empty.
double calculateAverage(int* arrayInts, int count) {
	if (count == 0) {
		// throw an error if the array is empty
		throw runtime_error("The array is empty, cannot calculate average.");
	}

	int sum = 0;
	// calculate the average of the values in the array
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return static_cast<double>(sum) / count;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0, and count should be at least 2.
// POSTCONDITION: calculates the sample standard deviation of the values in 'arrayInts' and returns it as a double, throws an error if 'arrayInts' contains fewer than two elements.
double calculateStandardDeviation(int* arrayInts, int count) {
	if (count < 2) {
		// throw an error if the array contains fewer than two elements
		throw std::runtime_error("Need at least two data points to calculate sample standard deviation.");
	}

	double mean = calculateAverage(arrayInts, count);  // assuming you have this function defined
	double sumOfSquares = 0;

	// calculate the sum of squares
	for (int i = 0; i < count; ++i) {
		sumOfSquares += (arrayInts[i] - mean) * (arrayInts[i] - mean);
	}

	return sqrt(sumOfSquares / (count - 1));
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the sum of the values in 'arrayInts' and returns it as an integer, throws an error if 'arrayInts' is empty.
int findSum(int* arrayInts, int count) {
	if (count == 0) {
		// throw an error if the array is empty
		throw runtime_error("The array is empty, cannot find sum.");
	}

	int sum = 0;
	// calculate the sum of the values in the array
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return sum;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the mean (average) of the values in 'arrayInts' and returns it as a double, throws an error if 'arrayInts' is empty.
double findMean(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find mean.");
	}

	return calculateAverage(arrayInts, count);  // average and mean are the same
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: sorts the array 'arrayInts' and calculates the median, returning it as a double, throws an error if 'arrayInts' is empty.
double findMedian(int* arrayInts, int count) {
	if (count == 0) {
		//	throw an error if the array is empty
		throw runtime_error("The array is empty, cannot find median.");
	}

	sort(arrayInts, arrayInts + count);
	// if the array has an even number of elements, return the average of the middle two
	if (count % 2 == 0) {
		return (arrayInts[count / 2 - 1] + arrayInts[count / 2]) / 2.0;
	}
	else {
		return arrayInts[count / 2];
	}
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: finds the range of the integers in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
int findRange(int* arrayInts, int count) {
	if (count == 0) {
		// throw an error if the array is empty
		throw runtime_error("The array is empty, cannot find range.");
	}

	int minVal = arrayInts[0];
	int maxVal = arrayInts[0];
	// find the minimum and maximum values in the array
	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] < minVal) minVal = arrayInts[i];
		if (arrayInts[i] > maxVal) maxVal = arrayInts[i];
	}

	return maxVal - minVal;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0, the array should also be sorted for frequency counts to be accurate.
// POSTCONDITION: calculates the frequencies and percentages of each unique integer, in 'arrayInts' and displays them, throws an error if 'arrayInts' is empty, returns nothing.
double findFrequencies(int* arrayInts, int count) {
	if (count == 0) {
		//	 throw an error if the array is empty
		throw runtime_error("The array is empty, cannot find frequencies.");
	}

	cout << "ELEMENT\tFREQUENCY\tPECENTAGE" << endl;
	cout << "=======\t=========\t==========" << endl;

	int frequency = 1;
	// calculate the frequencies and percentages of each unique integer
	for (int i = 0; i < count; ++i) {
		if (i < count - 1 && arrayInts[i] == arrayInts[i + 1]) {
			++frequency;
		}
		else {
			// calculate the percentage of the current integer
			double percentage = ((double)frequency / count) * 100;
			cout << arrayInts[i] << "\t" << frequency << "\t\t" << percentage << "%" << endl;
			frequency = 1;
		}
	}
}

// PRECONDITION:  arrayInts is a non-null pointer, count > 0, 'arrayInts' should be sorted in ascending order for accurate mode calculation.
// POSTCONDITION: finds the mode (most frequent element) in 'arrayInts' and prints it along with its frequency. If no mode is found (i.e., all numbers appear only once),
// a message is printed indicating that no mode exists, throws an error if 'arrayInts' is empty.
void findMode(int* arrayInts, int count) {
	if (count == 0) {
		// throw an error if the array is empty
		throw runtime_error("The array is empty, cannot find mode.");
	}

	int highestFreq = 0;
	int mode = arrayInts[0];
	int freq = 1;
	// find the mode (most frequent element) in the array
	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] == arrayInts[i - 1]) {
			++freq;
		}
		// if the current element is different from the previous one, reset the frequency
		else {
			freq = 1;
		}
		if (freq > highestFreq) {
			highestFreq = freq;
			mode = arrayInts[i];
		}
	}
	// if all numbers appear only once, there is no mode
	if (highestFreq == 1) {
		cout << "No mode found, all numbers appear only once." << endl;
	}
	// otherwise, print the mode and its frequency
	else {
		cout << "Mode: " << mode << " (Frequency: " << highestFreq << ")" << endl;
	}
}

// PRECONDITION:  arrayInts is a non-null pointer, count > 0, 'count' should be greater than or equal to 2 for a valid variance calculation.
// POSTCONDITION: calculates the sample variance of the integers in 'arrayInts' and returns it, hrows an error if 'arrayInts' has fewer than two elements.
double findVariance(int* arrayInts, int count) {
	if (count < 2) {
		// throw an error if the array has fewer than two elements
		throw std::runtime_error("Need at least two data points to calculate sample variance.");
	}

	// first calculate the mean
	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}
	double mean = static_cast<double>(sum) / count;

	// cow calculate the variance
	double variance = 0;
	for (int i = 0; i < count; ++i) {
		variance += std::pow(arrayInts[i] - mean, 2);
	}
	variance /= (count - 1);

	return variance;
}

// PRECONDITION:  arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates the midrange of the integers in 'arrayInts' and returns it, throws an error if 'arrayInts' is empty.
double findMidrange(int* arrayInts, int count) {
	if (count == 0) {
		// throw an error if the array is empty
		throw std::runtime_error("The array is empty, cannot find midrange.");
	}

	int minVal = arrayInts[0];
	int maxVal = arrayInts[0];
	// find the minimum and maximum values in the array
	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] < minVal) {
			minVal = arrayInts[i];
		}
		if (arrayInts[i] > maxVal) {
			maxVal = arrayInts[i];
		}
	}
	// calculate the midrange
	return static_cast<double>(minVal + maxVal) / 2;
}

// PRECONDITION: assumes findMedian is defined above this code, arrayInts is a non-null pointer, count > 0,
// POSTCONDITION: calcualtes and prints the first, second (median), and third quartiles of the integers in 'arrayInts', throws an error if 'arrayInts' is empty.
void findQuartiles(int* arrayInts, int count) {
	// throw an error if the array is empty
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot find quartiles.");
	}

	// calculate Q2 (second quartile / median)
	double q2 = findMedian(arrayInts, count);
	std::cout << "Q2 (Second Quartile/Median): " << q2 << std::endl;

	// ff the dataset is too small to find Q1 or Q3
	if (count < 4) {
		std::cout << "The dataset is too small for first and third quartile calculation." << std::endl;
		return;
	}

	// initialize sizes for lower and upper halves of the data
	int lowerCount = count / 2;
	int upperCount = lowerCount;

	// if the dataset has an odd number, the upper half will have one more element.
	if (count % 2 != 0) {
		++upperCount;
	}

	// dynamic allocation for lower and upper halves
	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	// populate lower half and sort
	std::copy(arrayInts, arrayInts + lowerCount, lowerHalf);
	std::sort(lowerHalf, lowerHalf + lowerCount);

	// determine the starting index for the upper half
	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);

	// populate upper half and sort
	std::copy(arrayInts + startIdxForUpper, arrayInts + startIdxForUpper + upperCount, upperHalf);
	std::sort(upperHalf, upperHalf + upperCount);

	// calculate Q1 (first quartile) and Q3 (third quartile)
	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	// output the quartiles
	std::cout << "Q1 (First Quartile): " << q1 << std::endl;
	std::cout << "Q3 (Third Quartile): " << q3 << std::endl;

	// free dynamically allocated memory
	delete[] lowerHalf;
	delete[] upperHalf;
}

// PRECONDITION: assumes findMedian is defined above this code.
// arrayInts is a non-null pointer, count > 0, 'count' should be greater or equal to 4 for valid interquartile range calculations.
// POSTCONDITION: calculates and returns the interquartile range of the integers in 'arrayInts', throws an error if 'arrayInts' has fewer than 4 elements.
double findInterquartileRange(int* arrayInts, int count) {
	if (count < 4) {
		throw std::runtime_error("The dataset is too small to calculate the interquartile range.");
	}

	// initialize sizes for lower and upper halves of the data
	int lowerCount = count / 2;
	int upperCount = lowerCount;

	// ff the dataset has an odd number, the upper half will have one more element.
	if (count % 2 != 0) {
		++upperCount;
	}

	// dynamic allocation for lower and upper halves
	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	// populate lower half
	std::copy(arrayInts, arrayInts + lowerCount, lowerHalf);

	// determine the starting index for the upper half
	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);

	// populate upper half
	std::copy(arrayInts + startIdxForUpper, arrayInts + startIdxForUpper + upperCount, upperHalf);

	// calculate Q1 (first quartile) and Q3 (third quartile)
	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	// free dynamically allocated memory
	delete[] lowerHalf;
	delete[] upperHalf;

	// calculate and return the interquartile range
	return q3 - q1;
}

// PRECONDITION: assumes findInterquartileRange and findMedian are defined above this code, arrayInts is a non-null pointer, count > 0, 'count' should be greater or equal to 4 for valid outlier identification.
// POSTCONDITION: calculates and outputs any outliers found in the dataset to the console, throws an error if 'arrayInts' has fewer than 4 elements.
void findOutliers(int* arrayInts, int count) {
	if (count < 4) {
		throw std::runtime_error("The dataset is too small to identify outliers.");
	}

	// calculate the Interquartile Range (IQR)
	double iqr = findInterquartileRange(arrayInts, count);

	// initialize sizes for lower and upper halves of the data
	int lowerCount = count / 2;
	int upperCount = lowerCount;

	// ff the dataset has an odd number, the upper half will have one more element.
	if (count % 2 != 0) {
		++upperCount;
	}

	// dynamic allocation for lower and upper halves
	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	// populate lower half
	for (int i = 0; i < lowerCount; ++i) {
		lowerHalf[i] = arrayInts[i];
	}

	// determine the starting index for the upper half
	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);

	// populate upper half
	for (int i = 0; i < upperCount; ++i) {
		upperHalf[i] = arrayInts[startIdxForUpper + i];
	}

	// calculate Q1 (first quartile) and Q3 (third quartile)
	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	// free dynamically allocated memory
	delete[] lowerHalf;
	delete[] upperHalf;

	// calculate the "fences" for identifying outliers
	double lowerFence = q1 - 1.5 * iqr;
	double upperFence = q3 + 1.5 * iqr;

	cout << "Outliers in the dataset: ";

	bool hasOutliers = false;
	// check each data point to see if it falls outside the fences
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] < lowerFence || arrayInts[i] > upperFence) {
			cout << arrayInts[i] << ' ';
			hasOutliers = true;
		}
	}

	if (!hasOutliers) {
		cout << "No outliers found.";
	}

	cout << endl;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the sum of squares of deviations from the mean
double findSumOfSquares(int* arrayInts, int count) {
	if (count == 0) {
		// if mean is not provided, calculate it
		throw std::runtime_error("Empty array.");
	}

	double mean = findMean(arrayInts, count); // calculate mean

	double sumOfSquares = 0.0;
	// calculate sum of squares
	for (int i = 0; i < count; ++i) {
		double deviation = static_cast<double>(arrayInts[i]) - mean; // calculate deviation from mean
		sumOfSquares += deviation * deviation; // sum up square of deviation
	}
	// return the sum of squares
	return sumOfSquares;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the sum of absolute deviations from the mean
double findSumAbsoluteDeviation(int* arrayInts, int count, double mean) {
	if (count == 0) {
		// if mean is not provided, calculate it
		throw std::runtime_error("Empty array.");
	}

	double sumAbsoluteDeviation = 0;
	// calculate sum of absolute deviations
	for (int i = 0; i < count; ++i) {
		sumAbsoluteDeviation += std::abs(arrayInts[i] - mean);  // calculate absolute deviation and sum it up
	}
	// return the sum of absolute deviations
	return sumAbsoluteDeviation;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the mean absolute deviation of the array
double findMeanAbsoluteDeviation(int* arrayInts, int count) {
	if (count == 0) {
		// if mean is not provided, calculate it
		throw std::runtime_error("The array is empty, cannot calculate mean absolute deviation.");
	}

	double mean = findMean(arrayInts, count);  // calculate mean using existing findMean function
	double sumAbsoluteDeviation = findSumAbsoluteDeviation(arrayInts, count, mean);  // calculate sum of absolute deviations
	double mad = sumAbsoluteDeviation / count;  // calculate mean absolute deviation

	return mad;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0
// POSTCONDITION: calculates and returns the root mean square (RMS) of the array
double findRootMeanSquare(int* arrayInts, int count) {
	if (count == 0) {
		// if mean is not provided, calculate it
		throw std::runtime_error("The array is empty, cannot calculate root mean square.");
	}

	double sumSquared = 0;
	// sum the squares of each element in the array
	for (int i = 0; i < count; ++i) {
		sumSquared += arrayInts[i] * arrayInts[i];
	}

	// calculate the root mean square (RMS)
	double rms = sqrt(sumSquared / count);
	return rms;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0, standardDeviation >= 0
// POSTCONDITION: calculates and returns the standard error of the array based on the provided standard deviation
double findStandardError(int* arrayInts, int count, double standardDeviation) {
	// check if the array is empty
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate standard error.");
	}

	// calculate the standard error
	double standardError = standardDeviation / sqrt(count);
	return standardError;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0, standardDeviation >= 0, mean != 0
// POSTCONDITION: calculates and returns the coefficient of variation for the array based on the provided standard deviation and mean
double findCoefficientOfVariation(int* arrayInts, int count, double standardDeviation, double mean) {
	// check if the array is empty
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate coefficient of variation.");
	}

	// check if the mean is zero
	if (mean == 0) {
		throw std::runtime_error("Mean is zero, cannot calculate coefficient of variation.");
	}

	// calculate the coefficient of variation
	double coefficientOfVariation = (standardDeviation / mean);
	return coefficientOfVariation;
}

// PRECONDITION: arrayInts is a non-null pointer, count > 0, standardDeviation >= 0, mean != 0
// POSTCONDITION: calculates and returns the relative standard deviation for the array based on the provided standard deviation and mean
double findRelativeStandardDeviation(int* arrayInts, int count, double standardDeviation, double mean) {
	// check if the array is empty
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate relative standard deviation.");
	}

	// check if the mean is zero
	if (mean == 0) {
		throw std::runtime_error("Mean is zero, cannot calculate relative standard deviation.");
	}

	// calculate the relative standard deviation (as a percentage)
	double relativeStandardDeviation = (standardDeviation / mean) * 100;
	return relativeStandardDeviation;
}

// PRECONDITION: function expects that any function it calls is properly defined and assumes that any data file it tries to read from is properly formatted.
// POSTCONDITION: the function will perform multiple descriptive statistical operations based on the user's choice, the function will display the results on the screen and may write them to an output file.
// any dynamic memory allocated will be managed properly.
int descriptiveStatistics() {
	int* arrayInts = nullptr;
	int count = 0;
	char option;
	string inputLine;

	do {
		displayDescriptiveStatisticsMenu();
		std::getline(std::cin, inputLine);  // read the whole line

		std::stringstream ss(inputLine);
		ss >> option;  // try to extract a char

		if (ss.fail()) {  // failed to extract a char
			std::cin.clear();
			cout << "Invalid option. Please try again." << endl;
			system("pause");
			system("cls");
			continue;  // skip the remaining code in the loop and start from the beginning
		}

		// If the user entered extra characters after the first one
		if (!ss.eof()) {
			string extra;
			ss >> extra;
			if (!ss.fail()) {
				cout << "Invalid option. Please enter only a single character." << endl;
				system("pause");
				system("cls");
				continue;
			}
		}

		switch (toupper(option))
		{

		case 'A': // read, store, and display into sorted dynamic array
		{
			system("cls");
			string filename;
			cout << "Please enter the filename: ";
			cin >> filename;

			// clear the input buffer before reading the next line
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			try {
				readIntsFromFile(filename, arrayInts, count);
				displayArray(arrayInts, count);
			}
			catch (const runtime_error& e) {
				cout << e.what() << endl;
			}

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
			try {
				findFrequencies(arrayInts, count);
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'J': // mode

			system("cls");
			try {
				findMode(arrayInts, count);
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
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
			try {
				double varianceVal = findVariance(arrayInts, count);
				cout << "The variance of the given data set is: " << varianceVal << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'M': // midrange

			system("cls");
			try {
				double midrangeVal = findMidrange(arrayInts, count);
				cout << "The midrange of the given data set is: " << midrangeVal << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'N': // quartiles

			system("cls");
			try {
				findQuartiles(arrayInts, count); 
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'O': // interquartile range

			system("cls");
			try {
				double iqr = findInterquartileRange(arrayInts, count);
				cout << "The interquartile range (IQR) of the given data set is: " << iqr << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'P': // outliers

			system("cls");
			try {
				findOutliers(arrayInts, count);
				cout << "The outliers of the given data set is: " << findOutliers << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'Q': // sum of squares

			system("cls");
			try {
				double sumOfSquaresVal = findSumOfSquares(arrayInts, count);
				cout << "The sum of squares for the given data set is: " << sumOfSquaresVal << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'R': // mean absolute deviation

			system("cls");
			try {
				double mad = findMeanAbsoluteDeviation(arrayInts, count);  
				std::cout << "The Mean Absolute Deviation (MAD) of the given data set is: " << mad << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'S': // root mean square

			system("cls");
			try {
				double rms = findRootMeanSquare(arrayInts, count); 
				std::cout << "The Root Mean Square (RMS) of the given data set is: " << rms << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'T': // standard error of the mean

			system("cls");
			try {
				double stdDev = calculateStandardDeviation(arrayInts, count);  
				double standardError = findStandardError(arrayInts, count, stdDev); 
				std::cout << "The Standard Error of the Mean for the given data set is: " << standardError << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'U': // coefficient of variation

			system("cls");
			try {
				double mean = findMean(arrayInts, count);  
				double stdDev = calculateStandardDeviation(arrayInts, count); 
				double coefficientOfVariation = findCoefficientOfVariation(arrayInts, count, stdDev, mean); 
				std::cout << "The Coefficient of Variation for the given data set is: " << coefficientOfVariation << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'V': // relative standard deviation

			system("cls");
			try {
				double mean = findMean(arrayInts, count);  
				double stdDev = calculateStandardDeviation(arrayInts, count);  
				double relativeStandardDeviation = findRelativeStandardDeviation(arrayInts, count, stdDev, mean);  
				std::cout << "The Relative Standard Deviation for the given data set is: " << relativeStandardDeviation << "%" << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'W': // display all results and write to an output text file
		{
			system("cls");
			std::ofstream outputFile("DescriptiveStatisticsResults.txt");
			if (!outputFile) {
				cerr << "Error opening output file." << endl;
				break;
			}
			try {
				// writing to file (and this will overwrite the file if it already exists)

				displayArray(arrayInts, count); // A
				cout << "\n" << endl;

				int minVal = findMinimum(arrayInts, count); // B
				outputFile << "Minimum Value: " << minVal << endl;
				cout << "Minimum Value: " << minVal <<"" << endl;
				cout << "\n" << endl;

				int maxVal = findMaximum(arrayInts, count); // C
				outputFile << "Maximum Value: " << maxVal << endl;
				cout << "Maximum Value: " << maxVal << endl;
				cout << "\n" << endl;

				int range = findRange(arrayInts, count); // D
				outputFile << "Range: " << range << endl;
				cout << "Range: " << range << endl;
				cout << "\n" << endl;

				outputFile << "Size: " << count << endl; // E 
				cout << "Size: " << count << endl;
				cout << "\n" << endl;

				int sum = findSum(arrayInts, count); // F 
				outputFile << "Sum: " << sum << endl;
				cout << "Sum: " << sum << endl;
				cout << "\n" << endl;

				double mean = findMean(arrayInts, count); // G 
				outputFile << "Mean: " << mean << endl;
				cout << "Mean: " << mean << endl;
				cout << "\n" << endl;

				double median = findMedian(arrayInts, count); // H
				outputFile << "Median: " << median << endl;
				cout << "Median: " << median << endl;
				cout << "\n" << endl;

				findMode(arrayInts, count);	 // J
				cout << "\n" << endl;

				double stdDev = calculateStandardDeviation(arrayInts, count); // K
				outputFile << "Standard Deviation: " << stdDev << endl;
				cout << "Standard Deviation: " << stdDev << endl;
				cout << "\n" << endl;

				double variance = findVariance(arrayInts, count); // L
				outputFile << "Variance: " << variance << endl;
				cout << "Variance: " << variance << endl;
				cout << "\n" << endl;

				double midrangeVal = findMidrange(arrayInts, count); // M
				outputFile << "Midrange: " << midrangeVal << endl;
				cout << "Midrange: " << midrangeVal << endl; 	
				cout << "\n" << endl;

				findQuartiles(arrayInts, count); // N 
				cout << "\n" << endl;

				double iqr = findInterquartileRange(arrayInts, count); // O
				outputFile << "Interquartile Range (IQR): " << iqr << endl;
				cout << "Interquartile Range (IQR): " << iqr << endl;
				cout << "\n" << endl;

				findOutliers(arrayInts, count); // P
				cout << "\n" << endl;

				double sumOfSquaresVal = findSumOfSquares(arrayInts, count); // Q
				outputFile << "Sum of Squares: " << sumOfSquaresVal << endl;
				cout << "Sum of Squares: " << sumOfSquaresVal << endl;
				cout << "\n" << endl;

				double mad = findMeanAbsoluteDeviation(arrayInts, count); // R
				outputFile << "Mean Absolute Deviation (MAD): " << mad << endl;
				cout << "Mean Absolute Deviation (MAD): " << mad << endl;
				cout << "\n" << endl;

				double rms = findRootMeanSquare(arrayInts, count); // S
				outputFile << "Root Mean Square (RMS): " << rms << endl;
				cout << "Root Mean Square (RMS): " << rms << endl;
				cout << "\n" << endl;

				double standardError = findStandardError(arrayInts, count, stdDev); // T
				outputFile << "Standard Error of the Mean: " << standardError << endl;
				cout << "Standard Error of the Mean: " << standardError << endl;
				cout << "\n" << endl;

				double coefficientOfVariation = findCoefficientOfVariation(arrayInts, count, stdDev, mean); // U
				outputFile << "Coefficient of Variation: " << coefficientOfVariation << endl;
				cout << "Coefficient of Variation: " << coefficientOfVariation << endl;
				cout << "\n" << endl;
				 
				double relativeStandardDeviation = findRelativeStandardDeviation(arrayInts, count, stdDev, mean); // V
				outputFile << "Relative Standard Deviation: " << relativeStandardDeviation << "%" << endl;
				cout << "Relative Standard Deviation: " << relativeStandardDeviation << "%" << endl;
				cout << "\n" << endl;

				findFrequencies(arrayInts, count); // I (moved to last to make output look nicer for user)
				cout << "\n" << endl;

				cout << "Enter output file name: " << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				outputFile << "Error: " << e.what() << endl;
			}

			outputFile.close();
			system("pause");
			system("cls");
		}
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

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} 
	while (toupper(option) != 'X');
	delete[] arrayInts;
	return 0;
}









