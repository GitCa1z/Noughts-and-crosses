#include <string> //defines one variable type, one macro, and many functions which can be used to manipulate a string or array of characters.
#include <iostream> //display output on the screen and read input from the keyboard.
#include <Windows.h> //contains declarations for all of the functions in the Windows API
#include <ctime>  // returns the string representing the localtime based on the argument timer.
#include <chrono> // provides a precision-neutral way of handling date and time that is independent of the underlying frameworks used by different systems
#include <thread> // threading is the idea of a single program executing multiple lists of instructions simultaneously or nearly simultaneously.


using namespace std; //allow programmers to use the standard functions without std:: (Not recommend though as it can cause issues in bigger programs)

// enum used for making an array that the AI can use to make to make random choice when in game
enum AIChoice {
	q,
	w,
	e,
	a,
	s,
	d,
	z,
	x,
	c,
	l,
};

//array that the AI can use to make to make random choice when in game
AIChoice chosen[]{ q,w,e,a,s,d,z,x,c};

//function prototypes / forward declarations
void StartUp();
void DisplayGrid();
void DisplayInput();
void FillSquare(int row, int col);
void CheckInput();
void CheckStatus();
int mainMenu();
int howToPlay();
void Init();
void SoundManager (int soundNum);
void AiBrain();
void AiEasy();
void AiAdvanced();
void difficulty();
void YouWin(int currentplayer);
void HeartCounter();
string SetColor(unsigned short color);

//globals variables
bool ThreeLivesMode = false;
bool skip = false;
bool advanced = false;
bool solo = false;
int menuChoice;
const int ROWS = 3;			
const int COLS = 3;			
char grid[ROWS][COLS];		
int filledSquares = 0;		
char input = ' ';
int currentPlayer = 3;
int lives = 3;
string playerOne = " ";
string playerTwo = " ";

// The int main() defines the entry or the starting point of the C/C++ program code.
int main(){

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); // makes the console fullscreen
	SoundManager(5); // invokes sound manager with an int parameter that corresponds with switch case 
	int x = time(0); //time() function returns the current calendar time.
	srand(x); //stime() sets the system's idea of the time and date. The time, pointed to by x
	bool runProg = true; // checks to see if the program is still running
	StartUp();

	Init(); // The initialize function initializes the state on which the generated C/C++ entry-point functions operate.

	//do while loop excutuing code block at least once before checking the conditon and will contiune to do so until the player has inputed the charater 'F'
	do {
		
		mainMenu(); // invokes the mainMenu Function excuting all code within the mainMenu code block

		switch (menuChoice){ // checks agaisnt the menuChoice that the mainMenu functuon returns

		case 2: // plays standard noughts and crosses with a friend
			currentPlayer = 1; // set the current player to 1
			
			do {
				system("color 07"); // sets console bg and text colour
				system("cls");  // clears any previous prompts displayed onto the console
				cout << "Welcome to Noughts and Crosses!" << endl; 
				DisplayGrid();	// invokes the DisplayGrid Function excuting all code within the DisplayGrid code block
				DisplayInput();	// invokes the DisplayInput Function excuting all code within the DisplayInput code block
				CheckInput();	// invokes the CheckInput Function excuting all code within the CheckInput code block
				CheckStatus();	// invokes the CheckStatus Function excuting all code within the CheckStatus code block
				system("cls");
			} while (toupper(input) != 'F' && toupper(input) != 'M'); // checks to see if the player has type the charater F break out of the do while loop
			break; // breaks out of the switch case

		case 3:
			howToPlay(); // invokes the HowToPlay Function excuting all code within the HowToPlay code block
			break;

		case 4:
			runProg = false; // returns runprog to false closing the game down
			return 0; // if returned 0 application ran successful if 1 then application cannot run
			break;
		case 1:	
			do {
			solo = true; // checks to see if the player is playing against the AI instead of friend
			if (skip == false) { difficulty(); } // invokes the difficulty Function excuting all code within the difficulty code block if condtion is met
			system("cls");
			system("color 0F");
			DisplayGrid();		
			DisplayInput();		
			CheckInput();		
			CheckStatus();		
			system("cls");
		} while (toupper(input) != 'F' && toupper(input) != 'M');

		default:
			cout << "Please enter a valid choice" << endl;
			}
		

	} while (toupper(input) != 'F');

	return 0;

	system("pause");
}

//function to display game board to the players
void DisplayGrid(){
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	//displays the game board to the grid whilst holding the grid array indexs for charater placement
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << grid[0][0] << "|" << grid[0][1] << "|" << grid[0][2] << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << "-" << "|" << "-" << "|" << "-" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << grid[1][0] << "|" << grid[1][1] << "|" << grid[1][2] << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << "-" << "|" << "-" << "|" << "-" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << grid[2][0] << "|" << grid[2][1] << "|" << grid[2][2] << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << endl;
}
//fuction to display input board so the players know what keys to press for the corrosponding posions on the game board
void DisplayInput(){
	if (currentPlayer == 1) {
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t| " << playerOne << " it's your turn [your place is X] |" << endl;
	}

	else {
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t| " << playerTwo << " it's your turn [your place is O] |" << endl;
	}

	//Displays the input board to the players
	cout << "\n" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << "Q" << "|" << "W" << "|" << "E" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << "-" << "|" << "-" << "|" << "-" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << "A" << "|" << "S" << "|" << "D" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << "-" << "|" << "-" << "|" << "-" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << "Z" << "|" << "X" << "|" << "C" << endl;
	cout << "\n\n"; // adds new lines
	if (ThreeLivesMode) { HeartCounter();}  // invokes the HeartCounter Function excuting all code within the HeartCounter code block if condtion is met
	if (currentPlayer == 1 && ThreeLivesMode) { lives--; } // takes away a life from player one during the ThreeLiveMode agaisnt AI


}

//function using two int arguments to check if players selection is valid
void FillSquare(int row, int col){
	
	if (grid[row][col] != ' ') // checks to see if the row and col in the grid array are empty
	{

		if (currentPlayer == 3) { // checks to see if the current player is 3
			auto seconds = 0.1s; // delcares and variable using the chrono library feature
			this_thread::sleep_for(seconds); // delays the console from proceeding for the time specified in paramters which I delacred as seconds
			CheckInput();
		}
		
		if (currentPlayer == 1 || currentPlayer == 2) { // checks if current player is 1 or 2
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "That square is filled, please try again" << endl;
			SoundManager(2); // invokes sound manager with an int parameter that corresponds with switch case 
			CheckInput();
		}
		
	}
	else
	{
		
		if (currentPlayer == 1) {
			grid[row][col] = 'X'; // check to see if the space is grid array [row][col] are free if so place X in spot specified
			SoundManager(1);
		}		
		else {
			grid[row][col] = 'O'; // check to see if the space is grid array [row][col] are free if so place O in spot specified
			SoundManager(1);

		}
			

		//increment the filledSquares var as we've filled one
		filledSquares++; // Increases the filledSquares variable by +1
	}
}

//Function Asks Player and AI for their postion input and checks if its a valid choice
static void CheckInput() {
	
	AiBrain(); // invokes the AiBrain Function excuting all code within the AiBrain code block

	if (currentPlayer == 1 || currentPlayer == 2) {
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
		cin >> input; // takes in users input

	
	if (cin.fail()){ // checks to see if the cin input specified above is valid input
		cout << "Invalid character, try again!" << endl;
		CheckInput();
	}

	//converts the char to upper case
	input = toupper(input); // Tranforms all lower case charaters in 'input' to uppercase charaters

	//checks the input agaisnt the different switch cases that call the FillSquare function with exclusive int paramters
	switch (input){
	case 'Q': FillSquare(0, 0); break; // places current players charater at top-left of grid
	case 'W': FillSquare(0, 1); break; // places current players charater at top-centre of grid
	case 'E': FillSquare(0, 2); break; // places current players charater at top-right of grid
	case 'A': FillSquare(1, 0); break; // places current players charater at middle-left of grid
	case 'S': FillSquare(1, 1); break; // places current players charater at middle-centre of grid
	case 'D': FillSquare(1, 2); break; // places current players charater at middle-right of grid
	case 'Z': FillSquare(2, 0); break; // places current players charater at bottom-left of grid
	case 'X': FillSquare(2, 1); break; // places current players charater at bottom-centre of grid
	case 'C': FillSquare(2, 2); break; // places current players charater at bottom-right of grid
	
	default:{ // if none of the condtions above are accepted
		
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "Invalid character, try again!" << endl;
		SoundManager(2);
		CheckInput();
	}
	break;
	}
  }
	
}

//this function checks for a winning combo or a draw
static void CheckStatus()
{
	char xo; // set an undeclared char varibble called xo
	

	if (currentPlayer == 1) { xo = 'X'; } // Sets player one charater as X
	else if (currentPlayer == 2 || currentPlayer == 3) { xo = 'O';} // Set players 2 or 3(AI) charater as O
		

	
	bool inPlay = true; // create a variable called Inplay and delcare it as true

	
	if (
		//check to see if current players xo charater matches the horizontal row conditon
		grid[0][0] == xo && grid[0][1] == xo && grid[0][2] == xo ||
		grid[1][0] == xo && grid[1][1] == xo && grid[1][2] == xo ||
		grid[2][0] == xo && grid[2][1] == xo && grid[2][2] == xo ||

		//check to see if current players xo charater matches the Vertical row conditon
		grid[0][0] == xo && grid[1][0] == xo && grid[2][0] == xo ||
		grid[0][1] == xo && grid[1][1] == xo && grid[2][1] == xo ||
		grid[0][2] == xo && grid[1][2] == xo && grid[2][2] == xo ||

		//check to see if current players xo charater matches the Diagonal row conditon
		grid[0][0] == xo && grid[1][1] == xo && grid[2][2] == xo ||
		grid[0][2] == xo && grid[1][1] == xo && grid[2][0] == xo

		) {
		
		YouWin(currentPlayer); // invokes YouWin function with the paramater of the current active player
		inPlay = false; // set inplay varible to false
		
	}

	else if (lives == 0) { // checks to see if player one lives on ThreeHeartMode = 0
		YouWin(currentPlayer = 3); // invokes YouWin function with the paramater player 3
		inPlay = false;
	}

	else if (filledSquares == ROWS * COLS) { // check to see if all postions in the 3 x 3 are entirely filled with any matches (Resulting in a draw)
	
		currentPlayer = 4;
		YouWin(currentPlayer);
		SoundManager(6);
		inPlay = false;
	}

	//checks to see if the game is in play if not then it will excute the code block 
	if (!inPlay) {
	
		DisplayGrid();
		Init();
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "   Play again? Any key. F to quit" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t";  cin >> input;
	}
	else {
		// if still in play then this switch the current players
		if (currentPlayer == 1) {
			if (!solo) { // if not playing agaisnt AI then player 1 swtiches to player 2 not 3(AI)
				currentPlayer = 2;
			}
			else currentPlayer = 3;
		}
			
		else
			currentPlayer = 1; //switches back to player 1 if player 2 or 3(AI) have taken their turn
	}
}

//function to set update grid with space chars and set
static void Init(){
	lives = 3; //set players lives back to 3 if on ThreeHeartsMode this is so player do not lose instantly when starting new game
	currentPlayer = 3;
	filledSquares = 0; // set filledSquares back to 0 if all 9 have been filled this so players do not draw instantly when starting new game

	//nested loop through all rows and columns to set each square in the grid to a space char
	for (int row = 0; row < ROWS; row++){
		for (int col = 0; col < COLS; col++){
			grid[row][col] = ' ';
		}
	}
}

//displays the players with the main menu, ask for their input and returns the menuChoice
int mainMenu() {
	system("cls");

	cout << "\t\t\t\t" << "                       .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.                       " << endl;
	cout << "\t\t\t\t" << "                      | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |                      " << endl;
	cout << "\t\t\t\t" << "                      | |    _______   | || |  _________   | || |   _____      | || |  _________   | || |     ______   | || |  _________   | |                      " << endl;
	cout << "\t\t\t\t" << "                      | |   /  ___  |  | || | |_   ___  |  | || |  |_   _|     | || | |_   ___  |  | || |   .' ___  |  | || | |  _   _  |  | |                      " << endl;
	cout << "\t\t\t\t" << "                      | |  |  (__ \\_|  | || |   | |_  \\_|  | || |    | |       | || |   | |_  \\_|  | || |  / .'   \\_|  | || | |_/ | | \\_|  | |                      " << endl;
	cout << "\t\t\t\t" << "                      | |   '.___`-.   | || |   |  _|  _   | || |    | |   _   | || |   |  _|  _   | || |  | |         | || |     | |      | |                      " << endl;
	cout << "\t\t\t\t" << "                      | |  |`\\____) |  | || |  _| |___/ |  | || |   _| |__/ |  | || |  _| |___/ |  | || |  \\ `.___.'\\  | || |    _| |_     | |                      " << endl;
	cout << "\t\t\t\t" << "                      | |  |_______.'  | || | |_________|  | || |  |________|  | || | |_________|  | || |   `._____.'  | || |   |_____|    | |                      " << endl;
	cout << "\t\t\t\t" << "                      | |              | || |              | || |              | || |              | || |              | || |              | |                      " << endl;
	cout << "\t\t\t\t" << "                      | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |                      " << endl;
	cout << "\t\t\t\t" << "                       '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'                       " << endl;
	cout << "\t\t\t\t" << "   .----------------.  .-----------------.   .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .-----------------." << endl;
	cout << "\t\t\t\t" << "  | .--------------. || .--------------. |  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
	cout << "\t\t\t\t" << "  | |      __      | || | ____  _____  | |  | |     ____     | || |   ______     | || |  _________   | || |     _____    | || |     ____     | || | ____  _____  | |" << endl;
	cout << "\t\t\t\t" << "  | |     /  \\     | || ||_   \\|_   _| | |  | |   .'    `.   | || |  |_   __ \\   | || | |  _   _  |  | || |    |_   _|   | || |   .'    `.   | || ||_   \\|_   _| | |" << endl;
	cout << "\t\t\t\t" << "  | |    / /\\ \\    | || |  |   \\ | |   | |  | |  /  .--.  \\  | || |    | |__) |  | || | |_/ | | \\_|  | || |      | |     | || |  /  .--.  \\  | || |  |   \\ | |   | |" << endl;
	cout << "\t\t\t\t" << "  | |   / ____ \\   | || |  | |\\ \\| |   | |  | |  | |    | |  | || |    |  ___/   | || |     | |      | || |      | |     | || |  | |    | |  | || |  | |\\ \\| |   | |" << endl;
	cout << "\t\t\t\t" << "  | | _/ /    \\ \\_ | || | _| |_\\   |_  | |  | |  \\  `--'  /  | || |   _| |_      | || |    _| |_     | || |     _| |_    | || |  \\  `--'  /  | || | _| |_\\   |_  | |" << endl;
	cout << "\t\t\t\t" << "  | ||____|  |____|| || ||_____|\\____| | |  | |   `.____.'   | || |  |_____|     | || |   |_____|    | || |    |_____|   | || |   `.____.'   | || ||_____|\\____| | |" << endl;
	cout << "\t\t\t\t" << "  | |              | || |              | |  | |              | || |              | || |              | || |              | || |              | || |              | |" << endl;
	cout << "\t\t\t\t" << "  | '--------------' || '--------------' |  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
	cout << "\t\t\t\t" << "   '----------------'  '----------------'    '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;
	cout << "\n" << endl;
	cout << "\t\t\t\t" << "====================================================================================================================================================================" << endl;
	cout << "\t\t\t\t" << "| 1. play vs AI" << endl;
	cout << "\t\t\t\t" << "| 2. play vs friend" << endl;
	cout << "\t\t\t\t" << "| 3. Learn how to play" << endl;
	cout << "\t\t\t\t" << "| 4. Quit the game" << endl;
	cout << "\t\t\t\t" << "| >>";
	cin >> menuChoice;
	cout << "\t\t\t\t" << "====================================================================================================================================================================" << endl;

	return menuChoice;
}

//displays to the player and long prompt on how to play the game
int howToPlay() {
	system("cls");
	cout << "\t\t" << "--------------------------------------------------" << endl;
	cout << "\t\t" << "|This is the game of naughts and crosses the aim |" << endl;
	cout << "\t\t" << "|of the game is to place your piece on the board |" << endl;
	cout << "\t\t" << "|in a pattern og three like the examples there   |" << endl;
	cout << "\t\t" << "|are eight winning conditions the first to meet  |" << endl;
	cout << "\t\t" << "|one is the winner.                              |" << endl;
	cout << "\t\t" << "|                                                |" << endl;
	cout << "\t\t" << "|Horizontal                                      |" << endl;
	cout << "\t\t" << "| | 1 | 2 | 3 | / |   |   |   | / |   |   |   |  |" << endl;
	cout << "\t\t" << "|-------------- / ------------- / -------------  |" << endl;
	cout << "\t\t" << "| |   |   |   | / | 1 | 2 | 3 | / |   |   |   |  |" << endl;
	cout << "\t\t" << "|-------------- / ------------- / -------------  |" << endl;
	cout << "\t\t" << "| |   |   |   | / |   |   |   | / | 1 | 2 | 3 |  |" << endl;
	cout << "\t\t" << "|-------------- / ------------- / -------------  |" << endl;
	cout << "\t\t" << "|vertical                                        |" << endl;
	cout << "\t\t" << "| | 1 |   |   | / |   | 1 |   | / |   |   | 1 |  |" << endl;
	cout << "\t\t" << "|-------------- / ------------- / -------------  |" << endl;
	cout << "\t\t" << "| | 2 |   |   | / |   | 2 |   | / |   |   | 2 |  |" << endl;
	cout << "\t\t" << "|-------------- / ------------- / -------------  |" << endl;
	cout << "\t\t" << "| | 3 |   |   | / |   | 3 |   | / |   |   | 3 |  |" << endl;
	cout << "\t\t" << "|-------------- / ------------- / -------------  |" << endl;
	cout << "\t\t" << "|Diagonal                                        |" << endl;
	cout << "\t\t" << "| | 1 |   |   | /               / |   |   | 1 |  |" << endl;
	cout << "\t\t" << "|-------------- /               / -------------  |" << endl;
	cout << "\t\t" << "| |   | 2 |   | /               / |   | 2 |   |  |" << endl;
	cout << "\t\t" << "|-------------- /               / -------------  |" << endl;
	cout << "\t\t" << "| |   |   | 3 | /               / | 3 |   |   |  |" << endl;
	cout << "\t\t" << "|----------------------------------------------  |" << endl;
	cout << "\t\t" << "|A tie                                           |" << endl;
	cout << "\t\t" << "|when none of these conditions are met the game  |" << endl;
	cout << "\t\t" << "|will end in a tie                               |" << endl;
	cout << "\t\t" << "|----------------------------------------------  |" << endl;
	cout << "\t\t" << "|Press any key to return back to the menu        |" << endl;
	cout << "\t\t" << "|or F to quit                                    |" << endl;
	cout << "\t\t" << "--------------------------------------------------" << endl;
	cout << "\t\t" << ">>";
	cin >> input;
	return input;
}

// plays a sound or music based on the int parmater when called
void SoundManager(int soundNum) {

	switch (soundNum) {
	case 1:
		PlaySound(TEXT("pong"), NULL, SND_SYNC); // plays sound
		break;
	case 2:
		PlaySound(TEXT("8-bit-error"), NULL, SND_SYNC);
		break;
	case 3:
		PlaySound(TEXT("win"), NULL, SND_SYNC);
		break;
	case 4:
		PlaySound(TEXT("lose"), NULL, SND_SYNC);
		break;
	case 5:
		PlaySound(TEXT("bg"), NULL, SND_LOOP | SND_ASYNC);
		break;
	case 6:
		PlaySound(TEXT("beep"), NULL, SND_SYNC);
	default:

		break;
	}
}

//Checks to see which AI difficutly to use based on difficultys setting the player had chosen
void AiBrain() {
	if (currentPlayer == 3) { 
		switch (advanced){
		case false:
			AiEasy();
			break;
		case true:
			AiAdvanced();
			break;
		default:
			break;
		}
	}
	
}

//AI uses this function to decide moves on the easy diffculty
void AiEasy(){
	AIChoice randomChoice = chosen[rand() % sizeof(chosen) / sizeof(AIChoice)]; // look at the enum array and choose a random element inside the index to use for the switch case

	switch (randomChoice) {
	case q: FillSquare(0, 0);  break;
	case w: FillSquare(0, 1);  break; 
	case e: FillSquare(0, 2);  break; 
	case a: FillSquare(1, 0);  break; 
	case s: FillSquare(1, 1);  break; 
	case d: FillSquare(1, 2);  break; 
	case z: FillSquare(2, 0);  break; 
	case x: FillSquare(2, 1);  break; 
	case c: FillSquare(2, 2);  break; 

	default: {

	}
		   break;
	}
}

//AI uses this function to decide moves on the advanced diffculty
void AiAdvanced() {
		
		//AI checks two horizontal charaters with a potential win conditon and fill in the final remain space to win
	     if (grid[0][0] == 'O' && grid[0][1] == 'O' && grid[0][2] != 'X') { FillSquare(0, 2); }
	else if (grid[0][1] == 'O' && grid[0][2] == 'O' && grid[0][0] != 'X') { FillSquare(0, 0); }
	else if (grid[1][0] == 'O' && grid[1][1] == 'O' && grid[1][2] != 'X') { FillSquare(1, 2); }
	else if (grid[1][1] == 'O' && grid[1][2] == 'O' && grid[1][0] != 'X') { FillSquare(1, 0); }
	else if (grid[2][0] == 'O' && grid[2][1] == 'O' && grid[2][2] != 'X') { FillSquare(2, 2); }
	else if (grid[2][1] == 'O' && grid[2][2] == 'O' && grid[2][0] != 'X') { FillSquare(2, 0); }

	else if (grid[0][0] == 'O' && grid[0][2] == 'O' && grid[0][1] != 'X') { FillSquare(0, 1); }
	else if (grid[2][0] == 'O' && grid[2][2] == 'O' && grid[2][1] != 'X') { FillSquare(2, 1); }

	//AI checks two vertical charaters with a potential win conditon and fill in the final remain space to win
	else if (grid[0][0] == 'O' && grid[1][0] == 'O' && grid[2][0] != 'X') { FillSquare(2, 0); }
	else if (grid[2][0] == 'O' && grid[1][0] == 'O' && grid[0][0] != 'X') { FillSquare(0, 0); }
	else if (grid[0][1] == 'O' && grid[1][1] == 'O' && grid[2][1] != 'X') { FillSquare(2, 1); }
	else if (grid[2][1] == 'O' && grid[1][1] == 'O' && grid[0][1] != 'X') { FillSquare(0, 1); }
	else if (grid[0][2] == 'O' && grid[1][2] == 'O' && grid[2][2] != 'X') { FillSquare(2, 2); }
	else if (grid[2][2] == 'O' && grid[1][2] == 'O' && grid[0][2] != 'X') { FillSquare(0, 2); }

	else if (grid[0][0] == 'O' && grid[2][0] == 'O' && grid[1][0] != 'X') { FillSquare(1, 0); }
	else if (grid[0][2] == 'O' && grid[2][2] == 'O' && grid[1][2] != 'X') { FillSquare(1, 2); }
	else if (grid[0][1] == 'O' && grid[2][1] == 'O' && grid[1][1] != 'X') { FillSquare(1, 1); }

	//AI checks two diagonal charaters with a potential win conditon and fill in the final remain space to win
	else if (grid[0][0] == 'O' && grid[1][1] == 'O' && grid[2][2] != 'X') { FillSquare(2, 2); }
	else if (grid[2][2] == 'O' && grid[1][1] == 'O' && grid[0][0] != 'X') { FillSquare(0, 0); }
	else if (grid[0][2] == 'O' && grid[1][1] == 'O' && grid[2][0] != 'X') { FillSquare(2, 0); }
	else if (grid[2][0] == 'O' && grid[1][1] == 'O' && grid[0][2] != 'X') { FillSquare(0, 2); }

	else if (grid[0][0] == 'O' && grid[2][2] == 'O' && grid[1][1] != 'X') { FillSquare(1, 1); }
	
    //AI checks player one two horizontal charaters with a potential win conditon and fill in the final remain space to block player from winning
	else if (grid[0][0] == 'X' && grid[0][1] == 'X' && grid[0][2] != 'O') { FillSquare(0, 2); }
	else if (grid[0][1] == 'X' && grid[0][2] == 'X' && grid[0][0] != 'O') { FillSquare(0, 0); }
	else if (grid[1][0] == 'X' && grid[1][1] == 'X' && grid[1][2] != 'O') { FillSquare(1, 2); }
	else if (grid[1][1] == 'X' && grid[1][2] == 'X' && grid[1][0] != 'O') { FillSquare(1, 0); }
	else if (grid[2][0] == 'X' && grid[2][1] == 'X' && grid[2][2] != 'O') { FillSquare(2, 2); }
	else if (grid[2][1] == 'X' && grid[2][2] == 'X' && grid[2][0] != 'O') { FillSquare(2, 0); }

	else if (grid[0][0] == 'X' && grid[0][2] == 'X' && grid[0][1] != 'O') { FillSquare(0, 1); }
	else if (grid[2][0] == 'X' && grid[2][2] == 'X' && grid[2][1] != 'O') { FillSquare(2, 1); }

	//AI checks player one two vertical charaters with a potential win conditon and fill in the final remain space to block player from winning
	else if (grid[0][0] == 'X' && grid[1][0] == 'X' && grid[2][0] != 'O') { FillSquare(2, 0); }
	else if (grid[2][0] == 'X' && grid[1][0] == 'X' && grid[0][0] != 'O') { FillSquare(0, 0); }
	else if (grid[0][1] == 'X' && grid[1][1] == 'X' && grid[2][1] != 'O') { FillSquare(2, 1); }
	else if (grid[2][1] == 'X' && grid[1][1] == 'X' && grid[0][1] != 'O') { FillSquare(0, 1); }
	else if (grid[0][2] == 'X' && grid[1][2] == 'X' && grid[2][2] != 'O') { FillSquare(2, 2); }
	else if (grid[2][2] == 'X' && grid[1][2] == 'X' && grid[0][2] != 'O') { FillSquare(0, 2); }

	else if (grid[0][0] == 'X' && grid[2][0] == 'X' && grid[1][0] != 'O') { FillSquare(1, 0); }
	else if (grid[0][2] == 'X' && grid[2][2] == 'X' && grid[1][2] != 'O') { FillSquare(1, 2); }
	else if (grid[0][0] == 'X' && grid[2][2] == 'X' && grid[1][1] != 'O') { FillSquare(1, 1); }

    //AI checks player one two diagonal charaters with a potential win conditon and fill in the final remain space to block player from winning
	else if (grid[0][0] == 'X' && grid[1][1] == 'X' && grid[2][2] != 'O') { FillSquare(2, 2); }
	else if (grid[2][2] == 'X' && grid[1][1] == 'X' && grid[0][0] != 'O') { FillSquare(0, 0); }
	else if (grid[0][2] == 'X' && grid[1][1] == 'X' && grid[2][0] != 'O') { FillSquare(2, 0); }
	else if (grid[2][0] == 'X' && grid[1][1] == 'X' && grid[0][2] != 'O') { FillSquare(0, 2); }

	//else if (grid[2][0] == 'X' && grid[0][2] == 'X' && grid[1][1] != 'O') { FillSquare(1, 1); }

	else AiEasy();

}

//Displays difficulty menu to the player
void difficulty(){

	system("cls");

	int dif;
	SetColor(10); // invokes SetColor Function with a unsigned short paramater

	cout << "   .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. " << endl;
	cout << "  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
	cout << "  | |     __       | || |              | || |  _________   | || |      __      | || |    _______   | || |  ____  ____  | |" << endl;
	cout << "  | |    /  |      | || |              | || | |_   ___  |  | || |     /  \\     | || |   /  ___  |  | || | |_  _||_  _| | |" << endl;
	cout << "  | |    `| |      | || |              | || |   | |_  \\_|  | || |    / /\\ \\    | || |  |  (__ \\_|  | || |   \\ \\  / /   | |" << endl;
	cout << "  | |     | |      | || |              | || |   |  _|  _   | || |   / ____ \\   | || |   '.___`-.   | || |    \\ \\/ /    | |" << endl;
	cout << "  | |    _| |_     | || |      _       | || |  _| |___/ |  | || | _/ /    \\ \\_ | || |  |`\\____) |  | || |    _|  |_    | |" << endl;
	cout << "  | |   |_____|    | || |     (_)      | || | |_________|  | || ||____|  |____|| || |  |_______.'  | || |   |______|   | |" << endl;
	cout << "  | |              | || |              | || |              | || |              | || |              | || |              | |" << endl;
	cout << "  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
	cout << "   '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;

 SetColor(14);

    cout << "   .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  " << endl;
    cout << "  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | " << endl;
    cout << "  | |    _____     | || |              | || |      __      | || |  ________    | || | ____   ____  | || |      __      | || | ____  _____  | || |     ______   | || |  _________   | || |  ________    | | " << endl;
	cout << "  | |   / ___ `.   | || |              | || |     /  \\     | || | |_   ___ `.  | || ||_  _| |_  _| | || |     /  \\     | || ||_   \\|_   _| | || |   .' ___  |  | || | |_   ___  |  | || | |_   ___ `.  | | " << endl;
    cout << "  | |  |_/___) |   | || |              | || |    / /\\ \\    | || |   | |   `. \\ | || |  \\ \\   / /   | || |    / /\\ \\    | || |  |   \\ | |   | || |  / .'   \\_|  | || |   | |_  \\_|  | || |   | |   `. \\ | | " << endl;
	cout << "  | |   .'____.'   | || |              | || |   / ____ \\   | || |   | |    | | | || |   \\ \\ / /    | || |   / ____ \\   | || |  | |\\ \\| |   | || |  | |         | || |   |  _|  _   | || |   | |    | | | | " << endl;
	cout << "  | |  / /____     | || |      _       | || | _/ /    \\ \\_ | || |  _| |___.' / | || |    \\ ' /     | || | _/ /    \\ \\_ | || | _| |_\\   |_  | || |  \\ `.___.'\\  | || |  _| |___/ |  | || |  _| |___.' / | | " << endl;
	cout << "  | |  |_______|   | || |     (_)      | || ||____|  |____|| || | |________.'  | || |     \\_/      | || ||____|  |____|| || ||_____|\\____| | || |   `._____.'  | || | |_________|  | || | |________.'  | | " << endl;
	cout << "  | |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | | " << endl;
	cout << "  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | " << endl;
	cout << "   '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  " << endl;

 SetColor(12);

 cout << "   .----------------.  .----------------.    .----------------.    .----------------.  .----------------.  .----------------.  .----------------.  .----------------. " << endl;
 cout << "  | .--------------. || .--------------. |  | .--------------. |  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
 cout << "  | |    ______    | || |              | |  | |    ______    | |  | |   _____      | || |     _____    | || | ____   ____  | || |  _________   | || |    _______   | |" << endl;
 cout << "  | |   / ____ `.  | || |              | |  | |   / ____ `.  | |  | |  |_   _|     | || |    |_   _|   | || ||_  _| |_  _| | || | |_   ___  |  | || |   /  ___  |  | |" << endl;
 cout << "  | |   `'  __) |  | || |              | |  | |   `'  __) |  | |  | |    | |       | || |      | |     | || |  \\ \\   / /   | || |   | |_  \\_|  | || |  |  (__ \\_|  | |" << endl;
 cout << "  | |   _  |__ '.  | || |              | |  | |   _  |__ '.  | |  | |    | |   _   | || |      | |     | || |   \\ \\ / /    | || |   |  _|  _   | || |   '.___`-.   | |" << endl;
 cout << "  | |  | \\____) |  | || |      _       | |  | |  | \\____) |  | |  | |   _| |__/ |  | || |     _| |_    | || |    \\ ' /     | || |  _| |___/ |  | || |  |`\\____) |  | |" << endl;
 cout << "  | |   \\______.'  | || |     (_)      | |  | |   \\______.'  | |  | |  |________|  | || |    |_____|   | || |     \\_/      | || | |_________|  | || |  |_______.'  | |" << endl;
 cout << "  | |              | || |              | |  | |              | |  | |              | || |              | || |              | || |              | || |              | |" << endl;
 cout << "  | '--------------' || '--------------' |  | '--------------' |  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
 cout << "   '----------------'  '----------------'    '----------------'    '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;

 SetColor(15);
 cout << "Please enter a number: ";
	cin >> dif;

	switch (dif){
	case 1:
		advanced = false;
		skip = true;
		break;
	case 2:
		advanced = true;
		skip = true;
		break;
	case 3:
		advanced = true;
		skip = true;
		ThreeLivesMode = true;
	default:
		break;
	}
	
}

//Displays winning condition screens such as win, lose, draw
void YouWin(int currentplayer) {

	switch (currentPlayer){
	case 1:
		system("color 2F");
		system("cls");
		cout << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t" << " __   __  _______  __   __    _     _  ___   __    _  __   __        " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |  |       " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |  |       " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|       ||  | |  ||  |_|  |  |       ||   | |       ||  | |  |       " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|_     _||  |_|  ||       |  |       ||   | |       ||__| |__|       " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "  |   |  |       ||       |  |   _   ||   | | | |   | __   __        " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "  |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |__|       " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << " _______  ___      _______  __   __  _______  ______      ____   __  " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|       ||   |    |   _   ||  | |  ||       ||    _ |    |    | |  | " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|    _  ||   |    |  |_|  ||  |_|  ||    ___||   | ||     |   | |  | " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|   |_| ||   |    |       ||       ||   |___ |   |_||_    |   | |  | " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|    ___||   |___ |       ||_     _||    ___||    __  |   |   | |__| " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|   |    |       ||   _   |  |   |  |   |___ |   |  | |   |   |  __  " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|___|    |_______||__| |__|  |___|  |_______||___|  |_|   |___| |__| " << endl;
		cout << "\n\n";
		SoundManager(3);
		break;

	case 2:
		system("color 2F");
		system("cls");
		cout << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t" << " __   __  _______  __   __    _     _  ___   __    _  __   __         " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |  |        " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |  |        " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|       ||  | |  ||  |_|  |  |       ||   | |       ||  | |  |        " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|_     _||  |_|  ||       |  |       ||   | |       ||__| |__|        " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "  |   |  |       ||       |  |   _   ||   | | | |   | __   __         " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "  |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |__|        " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << " _______  ___      _______  __   __  _______  ______      _______  __ " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|       ||   |    |   _   ||  | |  ||       ||    _ |    |       ||  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|    _  ||   |    |  |_|  ||  |_|  ||    ___||   | ||    |____   ||  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|   |_| ||   |    |       ||       ||   |___ |   |_||_    ____|  ||  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|    ___||   |___ |       ||_     _||    ___||    __  |  | ______||__|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|   |    |       ||   _   |  |   |  |   |___ |   |  | |  | |_____  __ " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|___|    |_______||__| |__|  |___|  |_______||___|  |_|  |_______||__|" << endl;
		SoundManager(3);
		cout << "\n\n";
		break;
	case 3:
		system("color 4F");
		system("cls");
		cout << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t" << " __   __  _______  __   __    ___      _______  _______  _______  __   __   __ " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|  | |  ||       ||  | |  |  |   |    |       ||       ||       ||  | |  | |  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___||  | |  | |  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ |  | |  | |  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___||__| |__| |__|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "  |   |  |       ||       |  |       ||       | _____| ||   |___  __   __   __ " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "  |___|  |_______||_______|  |_______||_______||_______||_______||__| |__| |__|" << endl;
		SoundManager(4);
		cout << "\n\n";
		break;

	case 4:
		system("color 6F");
		system("cls");
		cout << "\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << " ______   ______    _______  _     _  __ " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "|      | |    _ |  |   _   || | _ | ||  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "|  _    ||   | ||  |  |_|  || || || ||  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "| | |   ||   |_||_ |       ||       ||  |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "| |_|   ||    __  ||       ||       ||__|" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "|       ||   |  | ||   _   ||   _   | __ " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "|______| |___|  |_||__| |__||__| |__||__|" << endl;
		cout << "\n\n";
		break;
	default:
		break;
	}
	
}

//Displays hearts display when playing ThreeHeartsMode agaisnt AI
void HeartCounter() {

	switch (lives){
	case 3:
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "------------------LIVES-----------------\n"<< endl;
		SetColor(10);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << " , d88b.d88b, , d88b.d88b, , d88b.d88b,   " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  88888888888  88888888888  88888888888   " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  `Y8888888Y'  `Y8888888Y'  `Y8888888Y'   " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    `Y888Y'      `Y888Y'      `Y888Y'     " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "      `Y'          `Y'          `Y'     \n" << endl;
		SetColor(15);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "========================================= " << endl;
		break;
	case 2:
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "------------------LIVES------------------\n" << endl;
		SetColor(14);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << " , d88b.d88b, , d88b.d88b,                 " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  88888888888  88888888888                 " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  `Y8888888Y'  `Y8888888Y'                 " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    `Y888Y'      `Y888Y'                   " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "      `Y'          `Y'                   \n" << endl;
		SetColor(15);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "=========================================  " << endl;
		break;
	case 1:
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "------------------LIVES------------------\n" << endl;
		SetColor(12);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << " , d88b.d88b,                              " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  88888888888                              " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  `Y8888888Y'                              " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    `Y888Y'                                " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "      `Y'                                \n" << endl;
		SetColor(15);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "=========================================  " << endl;
		
		break;
	default:
		break;
	}

}

//set the colour of the console and text of string display on console depending on the paramter recives 
string SetColor(unsigned short color){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE); // Retrieves a handle to the specified standard device (standard input, standard output, or standard error). The standard output device. Initially, this is the active console screen buffer
    SetConsoleTextAttribute(hcon, color); // Sets the attributes of characters written to the console screen buffer by the WriteFile or WriteConsole function
    return "";
}

//displays start up
void StartUp() {
	system("color 0F"); // displays background and text colour

	cout << "\t\t\t\t" << "   .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. " << endl;
	cout << "\t\t\t\t" << "  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
	cout << "\t\t\t\t" << "  | | _____  _____ | || |  _________   | || |   _____      | || |     ______   | || |     ____     | || | ____    ____ | || |  _________   | || |              | |" << endl;
	cout << "\t\t\t\t" << "  | ||_   _||_   _|| || | |_   ___  |  | || |  |_   _|     | || |   .' ___  |  | || |   .'    `.   | || ||_   \\  /   _|| || | |_   ___  |  | || |      _       | |" << endl;
	cout << "\t\t\t\t" << "  | |  | | /\\ | |  | || |   | |_  \\_|  | || |    | |       | || |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\/   |  | || |   | |_  \\_|  | || |     | |      | |" << endl;
	cout << "\t\t\t\t" << "  | |  | |/  \\| |  | || |   |  _|  _   | || |    | |   _   | || |  | |         | || |  | |    | |  | || |  | |\\  /| |  | || |   |  _|  _   | || |     | |      | |" << endl;
	cout << "\t\t\t\t" << "  | |  |   /\\   |  | || |  _| |___/ |  | || |   _| |__/ |  | || |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\/_| |_ | || |  _| |___/ |  | || |     | |      | |" << endl;
	cout << "\t\t\t\t" << "  | |  |__/  \\__|  | || | |_________|  | || |  |________|  | || |   `._____.'  | || |   `.____.'   | || ||_____||_____|| || | |_________|  | || |     |_|      | |" << endl;
	cout << "\t\t\t\t" << "  | |              | || |              | || |              | || |              | || |              | || |              | || |              | || |     (_)      | |" << endl;
	cout << "\t\t\t\t" << "  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
	cout << "\t\t\t\t" << "   '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;
	cout << "\t\t\t\t" << "         .----------------.  .----------------.    .----------------.    .----------------.  .-----------------. .----------------.    .----------------.         " << endl;
	cout << "\t\t\t\t" << "        | .--------------. || .--------------. |  | .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |        " << endl;
	cout << "\t\t\t\t" << "        | |  _________   | || |     ____     | |  | |  ____  ____  | |  | |      __      | || | ____  _____  | || |  ________    | |  | |     ____     | |        " << endl;
	cout << "\t\t\t\t" << "        | | |  _   _  |  | || |   .'    `.   | |  | | |_  _||_  _| | |  | |     /  \\     | || ||_   \\|_   _| | || | |_   ___ `.  | |  | |   .'    `.   | |        " << endl;
	cout << "\t\t\t\t" << "        | | |_/ | | \\_|  | || |  /  .--.  \\  | |  | |   \\ \\  / /   | |  | |    / /\\ \\    | || |  |   \\ | |   | || |   | |   `. \\ | |  | |  /  .--.  \\  | |        " << endl;
	cout << "\t\t\t\t" << "        | |     | |      | || |  | |    | |  | |  | |    > `' <    | |  | |   / ____ \\   | || |  | |\\ \\| |   | || |   | |    | | | |  | |  | |    | |  | |        " << endl;
	cout << "\t\t\t\t" << "        | |    _| |_     | || |  \\  `--'  /  | |  | |  _/ /'`\\ \\_  | |  | | _/ /    \\ \\_ | || | _| |_\\   |_  | || |  _| |___.' / | |  | |  \\  `--'  /  | |        " << endl;
	cout << "\t\t\t\t" << "        | |   |_____|    | || |   `.____.'   | |  | | |____||____| | |  | ||____|  |____|| || ||_____|\\____| | || | |________.'  | |  | |   `.____.'   | |        " << endl;
	cout << "\t\t\t\t" << "        | |              | || |              | |  | |              | |  | |              | || |              | || |              | |  | |              | |        " << endl;
	cout << "\t\t\t\t" << "        | '--------------' || '--------------' |  | '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |        " << endl;
	cout << "\t\t\t\t" << "         '----------------'  '----------------'    '----------------'    '----------------'  '----------------'  '----------------'    '----------------'         " << endl;
	cout << "\n" << endl;
	cout << "\t\t\t\t" << "==================================================================================================================================================================" << endl;

	cout << "\t\t\t\t" << "|Enter the name of player one                                                                                                                                    |" << endl;
	cout << "\t\t\t\t" << "| >>";
	cin >> playerOne; // allows player to input their name
	cout << "\t\t\t\t" << "|Enter the name of player two                       |" << endl;
	cout << "\t\t\t\t" << "| >>";
	cin >> playerTwo;
}

