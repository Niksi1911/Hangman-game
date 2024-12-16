#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <typeinfo>
#include <cmath>
#include <cstdlib>
#include <string>
#include <time.h>
#include <ctime> 
#include <array> 
#include <sstream> //iss oss
#include <fstream> //file W R
#include <vector>  //vektor
#include <map>
#include <list>
#include <iomanip>  // For setw

using namespace std;

void StartGame(string, string&);

void push_toGuess(string&,int);
void printOutOfthe_(string&);

void Startgameprintout(); //SAMO TEKST
void addLetterToGuess(char,string&,int&,string); //DODAJ SLOVO U rijec koju gadas

void checkIfWin(string, string,bool&); //provjera jesu li sve rici pogodene
void checkIfLives0(string,int,bool&);  //provjera zivota

int main() {
	ifstream fin;
	fin.open("Vjesala.txt");

	if(fin.fail()) {
		cout << "ERROR WHILE OPENING THE FILE";
		exit(1);
	}

	string g;
	vector<string>words;

	while (!fin.eof())
	{
		fin >> g;
		words.push_back(g);
	}
	
	srand(static_cast<unsigned int>(time(0)));
	int randomIndex = rand() % words.size();
	string word = words[randomIndex];
	
	int word_len = 0; 
	word_len = word.length();
	
	string guess_word;
	push_toGuess(guess_word,word_len);
	
	StartGame(word,guess_word);
	cout << "\n";

	return 0;
}

void StartGame(string word, string& guess_word) {
	int lives = 0;
	int choice = 0;
	char c;
	bool GameOver = false;

	Startgameprintout();
	
	bool flag = false;
	do
	{
		//cin >> choice;
		while (!(cin >> choice)) {
			cout <<"neispravan unos. trazimo brojeve u rasponu 1-90" <<endl;
			cin.clear(); // Clear error flags
			cin.ignore(1000, '\n'); //clear input buffer
		}
		switch (choice)
		{
		case 1:
			lives = 10;
			break;
		case 2:
			lives = 8;
			break;
		case 3:
			lives = 6;
			break;
		default:
			cout << "WRONG INPUT !" << endl;
			cout << "TRY AGAIN !" << endl;
			break;
		}

		if (choice==1 || choice==2 || choice ==3)
		{
			flag = true;
		}

	} while (flag == false);

	cout << "\n\n";
	cout << setw(30) << "GAME STARTING ! " << endl;
	cout << "\n\n\n";
	printOutOfthe_(guess_word);
	cout << "YOUR WORD CONSISTS OF " << word.length() << " LETTERS" << "\n\n\n" << endl;

	while (GameOver==false)
	{
		cout << "INPUT A LETTER --> ";
		cin>>c;
		cout << endl;

		addLetterToGuess(c,guess_word,lives,word);
		cout << endl;
		printOutOfthe_(guess_word);
		cout << "\t\t\t\t\tRemaining lives : " << lives << endl;
		cout<<"\n\n";

		checkIfWin(word,guess_word,GameOver);
		checkIfLives0(word,lives,GameOver);
	}
}

void push_toGuess(string& guess_word, int n) {
	int i = 0;
	while (i<n)
	{
		guess_word.push_back('_');
		i++;
	}	
}
void printOutOfthe_(string& guess_word) {
	for (auto p:guess_word)
	{
		cout << "  " << p << "  ";
	}
}
void Startgameprintout() {
	cout <<setw(40)<< "WELCOME TO THE GAME HANGMAN !"<< endl;
	cout << endl;
	cout <<setw(30)<< "SELECT DIFICULTY" << endl;
	cout << endl;
	cout << setw(20) << "1 EASY" << "---> 10 LIVES" << endl;
	cout << setw(20) << "2 MEDIDUM" << "---> 8 LIVES" << endl;
	cout << setw(20) << "3 HARD" << "---> 6 LIVES" << endl;
	cout << "\n";
	cout <<"-------------------------------------------------> ";
}

void addLetterToGuess(char c,string& guess_word,int& lives,string word) {
	int n = guess_word.length();
	
	string copyOfGuess;
	copyOfGuess = guess_word;

	for (int i = 0; i <n; i++)
	{
		if (word[i]==c)
		{
			guess_word[i]= c;
		}
	}

	if (copyOfGuess==guess_word)
	{
		cout << "---WRONG LETTER---" << endl;
		lives--;
	}
}

void checkIfWin(string word, string guess, bool& gameOver) {
	if (word==guess)
	{
		gameOver = true;
		cout << "\n\nCONGRATULATIONS YOU GUESSED THE WORD CORRECTLY" << endl;
	}
}

void checkIfLives0(string word,int lives,bool& GameOver){
	if (lives==0)
	{
		GameOver = true;
		cout << "\n\nGAME OVER !\n\nYOU LOST ALL YOUR LIVES!"<<endl;
		cout << "WORD WAS : " << word;
	}
}