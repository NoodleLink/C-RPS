#include <iostream>
using namespace std;
class Player{
	private:
		bool alive;
		int health;
		string name;
	public:
	    Player(int structHealth, string structName){ // Constructor
	        alive = true; // alive will always be true by default
		health = structHealth;
		name = structName;
	    }
		// SET methods
		void takeLife(){ // Takes away 1 life
			health -= 1;
			return;
		}
		void setName(string newName){
			name = newName;
			return;
		}
		void kill(){
			alive = false;
			return;
		}
		// GET methods
		bool isAlive(){
			return alive;
		}
		int getLives(){
			return health;
		}
		string getName(){
			return name;
		}
};
string counterAttack(int debug){ // Get the CPU's move
	int selection = 0;
	if(debug % 2 == 1){
		selection = rand() % 3; // Gets a random number and gets the modulo (remainder) of dividing by 3
	}
	else{ // if debug is on it will cause an error
		selection = 4;
	}
	if(selection == 0){
		return("R");
	}
	else if(selection == 1){
		return("P");
	}
	else if(selection == 2){ // Number will be between 0 and 2 thanks to the modulo is of 3 
		return("S");
	}
	else{ // This should never without debug
		cerr << "\033[31m\tERROR Code: \t\"How did we get here\"\033[0m" << endl; // \033[31m and \033[0m will change the colour of the text, I need to look into this more
		return("How did we get here");
	}
}
string didPlayerWin(string playerChoice, string cpuChoice){ // Function to return whether the player won or lost
	// Draw state
	if(playerChoice == cpuChoice){
		cout << "CPU Picked: " << cpuChoice << endl;
		return "Draw";
	}
	// Win States
	else if(playerChoice == "R" && cpuChoice == "S"){
		cout << "CPU Picked: " << cpuChoice << endl;		
		return "Win";
	}
	else if(playerChoice == "P" && cpuChoice == "R"){
		cout << "CPU Picked: " << cpuChoice << endl;
		return "Win";
	}
	else if(playerChoice == "S" && cpuChoice == "P"){
		cout << "CPU Picked: " << cpuChoice << endl;
		return "Win";
	}
	// Loss states
	else if(cpuChoice == "R" && playerChoice == "S"){
		cout << "CPU Picked: " << cpuChoice << endl;
		return "Loss";
	}
	else if(cpuChoice == "P" && playerChoice == "R"){
		cout << "CPU Picked: " << cpuChoice << endl;
		return "Loss";
	}
	else if(cpuChoice == "S" && playerChoice == "P"){
		cout << "CPU Picked: " << cpuChoice << endl;
		return "Loss";
	}
	else{ // This should never run, idk why I put it here
		return "Idk man";
	}
}
int main(){
	// Initial set up
	string playername;
	int debug = 1; // If this variable is odd debug is off, if not it's on and will force an error.
	cout << "Welcome! Please enter a name" << endl;
	cin >> playername; // Set the player's name to be 
	Player player(3, playername);
	int coins = 0;
	int wins = 0;
	string selection = "B";
	// End of initial set up
	while(player.isAlive() == true){ // Main game loop
		cout << "Coins: " << coins << "\tWins: " << wins << endl; // Displays current run information
		cout << "Please pick Rock (R) Paper (P) or Scissors (S)" << endl;
		cin >> selection;
		if(selection == "R" || selection == "P" || selection == "S"){
			string state = didPlayerWin(selection, counterAttack(debug)); // Check if the player win or not or if it was a draw
			if(state == "Draw"){
				cout << "It's a draw :/" << endl;
			}
			else if(state == "Win"){
				cout << "You win! :)" << endl;
				int payout = rand() % 20 + 10;
				cout << "Awarded " << payout << " coins!" << endl;
				coins += payout;
				wins += 1;
			}
			else if(state == "Loss"){
				player.takeLife();
				cout << "You lose! - 1 Life\n" << player.getLives() << " Lives left" << endl;
			}
			else{
				return 1;
			}
		}
		else if(selection == "debug"){
			debug += 1; // Changes debug by +1, much easier and smaller than having it toggle, though I understand that toggle variables could also be a good idea
			cout << "Debug state: " << debug << "\t(Odd = Off\t Even = On)" << endl; // Output debug state
		}
		else {
			player.takeLife();
			cout << "Invalid input! -1 Life\n" << player.getLives() << " Lives left" << endl;
		}
		if(player.getLives() <= 0){
			// Game over screen
			cout << "\tGAME OVER" << endl;
			cout << "\tPlayer: " << player.getName() << endl;
			cout << "\t---\tSCORE\t---" << endl;
			cout << "\tCoins: \t" << coins << endl;
			cout << "\tWins:  \t" << wins << endl;
			cin; // This makes sure that the program doesn't close unless the user makes an input.
			player.kill();
		}
	}
	return 0;
}
