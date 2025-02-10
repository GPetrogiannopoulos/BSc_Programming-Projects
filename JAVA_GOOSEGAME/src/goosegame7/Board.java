package goosegame7;

import java.util.ArrayList;

// Class that defines the board of the Game, the board is defined by a list of players and a table of cells.
public class Board {

	protected ArrayList<Player> players;
        protected ArrayList<Cell> cells;

	public Board() {

	}

	// Constructor of a Board, it initializes a list of players and a table of cells.
	public Board(ArrayList<Player> p, ArrayList<Cell> c) {
		this.players = p;
		this.cells = c;
	}

	//It swaps the position of two players.p1 the first to be swapped, p2 the second to be swapped
	public void swapPlayer(Player p1, Player p2) { // swaps two players
		Player tmp = new Player();
		tmp.setCurrentCell(p1.getCurrentCell()); // temp 
		p1.setCurrentCell(p2.getCurrentCell());  // swap
		p2.setCurrentCell(tmp.getCurrentCell()); // swap
	}

	// It normalizes a move, if a move send a player out of bounds, it sends back the player on the other way.
        // target= Index to normalize, return The correct new index of a player
	public int normalize(int target,int dice) {  
		int bounce;

		if (target <= 63) {
			return target;
		}
                else{
                    int current = target-dice;  // current player square
                    bounce = (current+dice-63)+current;    
                    if(bounce<=63)    
                        return bounce;
                    else 
                        return (current-(bounce-63));
                }
	}

	// Initializes the board to the size given in parameters with every specific cell at the right place.
	public void initializeBoard(int size) { 
		for (int i = 0; i <= size; i++) {
			switch (i) {
			case 0:
                                this.cells.add(i, new StartingCell(this.players));
				break;
                        case 5:
			case 9:
                        case 14:
			case 18:
                        case 23:
			case 27:
                        case 32:
			case 36:
                        case 41:
			case 45:
                        case 50:
			case 54:
                        case 59:
                                this.cells.add(i,new GooseCell(i));
				break;
			case 31:
			case 52:
                                this.cells.add(i,new TrapCell(i));
				break;

			case 6:
                                this.cells.add(i,new TeleportCell(i, 12));
                                
				break;

			case 42:
                                this.cells.add(i,new TeleportCell(i, 30));
				break;

			case 58:
                                this.cells.add(i,new TeleportCell(i, 1));
				break;

			case 19:
                                this.cells.add(i,new WaitingCell(i, 2, 2));
				break;

			default:
                                this.cells.add(i,new NormalCell(i));
				break;
			}
		}
	}
}
