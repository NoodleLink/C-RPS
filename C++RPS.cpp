#include <iostream>
using namespace std;
class Player{
	private:
		bool alive;
		int health;
		string name;
	public:
	    Player(int structHealth, string structName){
	        alive = true;
		    health = structHealth;
		    name = structName;
	    }
		void takeLife(){
			health -= 1;
			return;
		}
		int getLives(){
			return health;
		}
		bool isAlive(){
			return alive;
		}
		void kill(){
			alive = false;
			return;
		}
		string getName(){
			return name;
		}
		void setName(string newName){
			name = newName;
			return;
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
	else if(selection == 2){ // Number will be between 0 and 2 thanks to the module is of 3 
		return("S");
	}
	else{ // This should never without debug
		cerr << "\033[31m\tERROR Code: \t\"How did we get here\"\033[0m" << endl;
		return("How did we get here");
	}
}
string didPlayerWin(string playerChoice, string cpuChoice){
	if(playerChoice == cpuChoice){
		cout << "CPU Picked: " << cpuChoice << endl;
		return "Draw";
	}
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
	else{
		return "Idk man";
	}
}
int main(){
	string playername;
	int debug = 1;
	cout << "Welcome! Please enter a name" << endl;
	cin >> playername;
	Player player(3, playername);
	int coins = 0;
	int wins = 0;
	string selection = "B";
	while(player.isAlive() == true){
		cout << "Coins: " << coins << "\tWins: " << wins << endl;
		cout << "Please pick Rock (R) Paper (P) or Scissors (S)" << endl;
		cin >> selection;
		if(selection == "R" || selection == "P" || selection == "S"){
			string state = didPlayerWin(selection, counterAttack(debug));
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
			debug += 1;
			cout << "Debug state: " << debug << "\t(Odd = Off\t Even = On)" << endl;
		}
		else {
			player.takeLife();
			cout << "Invalid input! -1 Life\n" << player.getLives() << " Lives left" << endl;
		}
		if(player.getLives() <= 0){
			cout << "\tOut of lives!" << endl;
			cout << "\tPlayer: " << player.getName() << endl;
			cout << "\t---\tSCORE\t---" << endl;
			cout << "\tCoins: \t" << coins << endl;
			cout << "\tWins:  \t" << wins << endl;
			cin;
			player.kill();
		}
	}
	return 0;
}