#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;


/** check if the element "a" of the attempt is in the solution (any position)
	
	parameters:
		x (int[]): solution
		a (int): element to check if in the solution
		size (int): size of the array
	
	return:
		true if a is in the solution, false otherwise
*/
bool contain(int x[], int a, int size) {
	for (int i = 0; i < size; i++)
			if (x[i] == a)
				return true;
	return false;
}

/** Create a random solution 
*/
void createInput(int x[], int size, int max) {
	int num = 0;
	for (int i = 0; i < size; i++) {
		num = rand() % max + 1;
		x[i] = num;
	}
}

/** Check if the attempt is right and tell where it is wrong

	parameters:
		res (int[]): the response
		input (int[]): solution
		output [int[]): the attempt
		size (int): array size
	
	return:
		true if you win, also otherwise
		furthermore, it return an array which tells you where you are wrong
*/
bool check(int res[], int input[], int output[], int size) {
	bool winner = true;
	for (int i = 0; i < size; i++) {
		// if the element is right and in the correct position
		if (input[i] == output[i])
			res[i] = 1;
		else { 
			winner = false;
			// if the element is right but not in the correct position
			if (contain(input, output[i], size))
				res[i] = 0;
			// if the element is wrong
			else
				res[i] = -1;
			}
	}
	return winner;
}

/** Change settings like solution size, or number of allowed attempts

	parameters:
		element (int*): element to modify, as array size or number of allowed attempts
		max (int): max allowed value for element
		min (int): min allowed value for element
*/
void changeSettings (int *element, int max, int min) {
	if (*element > max)
		*element = max;
	else if (*element < min)
		*element = min;
}

/** Print the array of hints (so, tell you where you are wrong)

	x (int[]): array to print
	size (int): array size
	colored (bool): if have to print colored
*/
void printVector(int x[], int size, bool colored) {
	char tmp = ' ';
	for (int i = 0; i < size; i++)
		if (colored) {
			if (x[i] == 1) {
				tmp = 'o';
				cout<<"\033[1;32m"; //green
			}
			else if (x[i] == -1) {
				tmp = 'x';
				cout<<"\033[1;31m"; //red
			}
			else 
				tmp = '-';
			cout<<tmp<<"\033[0m"<<" ";
		}
		else 
			cout<<x[i]<<" ";
}

/** Start the game
	Gamer try his attempts while he isn't right or he finish the allowed attempts.
	At every attempt, game prints where the gamer is wrong.
	At the end, if the gamer didn't win, solution is printed.
	In any rate, game asks if gamer wanna play again.
	
	parameters:
		tries (int): allowed number of attempts
		tries_num (int*): how many attempts gamer has used
		output (int[]): the attempt
		input (int[]): the solution
		res (int[]): response
		size (int): array size
		max_num (int): the greater num you can find in the solution
*/
void startGame(int tries, int *tries_num, int output[], int input[], int res[], int size, int max_num) {
	do {
		createInput(input,size,max_num);
			//Print solution (for debug)
			/*
			cout<<"Soluzione: ";
			printVector(input,size,false);
			cout<<endl;
			*/
		char replay;
		while (*tries_num < tries) {
			string tmp = "";	//Gamer's response
			cout<<(*tries_num)+1<<" of "<<tries<<" ";
			do {
				cout<<"Try to guess, "<<size<<" size: ";
				cin>>tmp;
			} while (tmp.size() != size);
			//Convert every character to int
			for (int i = 0; i < size; i++) {
				char cifra = tmp.at(i);
				output[i] = (int)cifra - 48;
			}
			//Print hints or victory
			if (check(res, input, output, size)) {
				cout<<"Congratulations, you win!\n";
				*tries_num = 0;
				break;
			}
			(*tries_num)++;
			printVector(res, size, true);
			cout<<endl;
			if ((*tries_num) >= tries) {
				cout<<"I'm sorry, you lost!\n";
				cout<<"Solution: ";
				printVector(input, size, false);
				cout<<endl;
				*tries_num = 0;
				break;
			}
		}
		do {
			cout<<"Do you wanna replay? (y/n) ";
			cin>>replay;
		} while (replay != 'n' && replay != 'y');
		if (replay == 'n')
			break;
	} while (true);
}

void printMenu(int *size, int *max_num, int *tries) {
	string menu = "\t\t\tGuess\n1. New game\n2. Change combination size: ";
	menu += to_string(*size);
	menu += "\n3. Change symbols number: ";
	menu += to_string(*max_num);
	menu += "\n4. Change tries number: ";
	menu += to_string(*tries);
	menu += "\n5. Print this menu";
	menu += "\n6. Help";
	menu += "\n7. Exit";
	cout<<menu;
}

void printHelp() {
	string help = "\t\t\tGuess - Help";
	 help += "\nYou have a set of numbers (symbols number) (es. symbols number = 4 => symbols 1-2-3-4), and have to reproduce a predetermined sequence of them (chosen by the computer) within a certain number of guesses (tries).";

	help += "\n\nEach guess gets marked with: ";
	help += "\n\t-A green 'o' if the number is right and in the right position;";
	help += "\n\t-A white '-' if the number is right but in the wrong position;";
	help += "\n\t-A red 'x' if the number is wrong.";
	help += "\n\nYou can change settings like tries number, size of the sequence to guess and number of allowed symbols.";
	help += "\nTo play you have to write the sequence, get the response and fix your sequence until you guess the right sequence";
	cout<<help;
}

int main() {
	
	int size = 4;		//How much numbers to guess
	int const max_size = 9;	//Max allowed size
	int max_num = 4;	//Numbers of possible symbols
	int const max_max_num = 9;	//Max allowed symbols number
	int tries = 9;		//Number of gamer tries
	
	int input[size];		//Solution
	int output[size];		//Gamer response
	int res[size];			//Result of response
	int tries_num = 0;		//Increment every try
	bool gameover = false;	//Game is over when gamer guess or if too many tries
	
	int choose = 0;

	srand (time(NULL));		//Root for random input
	
	printMenu(&size, &max_num, &tries);
	//Main cicle
	
	bool invalid = true;	//For some check
	cout<<endl;
	while (choose != 7) {
		cout<<endl;
		do {
			invalid = false;
			cout<<"What to do: ";
			cin>>choose;
			if (!cin) {
				invalid = true;
				cin.clear();
				cin.ignore(100, '\n');
			}
		} while (invalid);
		switch (choose) {
			case 1:
				startGame(tries, &tries_num, output, input, res, size, max_num);
				break;
			case 2:
				cout<<"New combination size (actual "<<size<<", max "<<max_size<<"): ";
				cin>>size;
				changeSettings(&size, max_size, 1);
				break;
			case 3:
				cout<<"New combination allowed symbols (actual "<<max_num<<", max "<<max_max_num<<"): ";
				cin>>max_num;
				changeSettings(&max_num, max_max_num, 2);
				break;
			case 4:
				cout<<"New tries (actual "<<tries<<", max 99): ";
				cin>>tries;
				changeSettings(&tries, 99, 1);
				break;
			case 5:
				printMenu(&size, &max_num, &tries);
				break;
			case 6:
				printHelp();
				cout<<endl;
				break;
			case 7:
				return 0;
			default:
				cout<<"Invalid choose"<<endl;
				break;
		}
	
	}
}
