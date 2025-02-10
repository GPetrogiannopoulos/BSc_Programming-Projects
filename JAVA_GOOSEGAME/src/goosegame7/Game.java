package goosegame7;

import java.util.ArrayList;
import java.util.Random;

// Main Class of the Game, it initializes the board, the players and launch the game
public class Game {

	protected Board board;
	protected boolean isFinished = false;
	protected Player p1, p2, p3, currentPlayer;

	public Game() {

	}

	// Constructor of a Game, it initializes the board that will be used for this game, b = Board that will be initialized.
	public Game(Board b) {
		this.board = b;
	}

	// Main method of the game, it launches the game until a player wins.
	public void play() 
        {
		int dice = 0;
		Cell realCell, targetCell;
		int idPlayer;
		currentPlayer = p1;
		Cell previousCell = null;
                String str;

		while (!this.isFinished) {
			previousCell = currentPlayer.getCurrentCell();
			if (currentPlayer.getCurrentCell().canBeLeftNow()) {
				dice = this.throwDie() + this.throwDie();

				targetCell = this.board.cells.get(board.normalize((currentPlayer.getCurrentCell().getIndex() + dice),dice));
				realCell = computeTargetCell(targetCell, dice);

				movePlayer(realCell);

				displayTrace(previousCell, targetCell, realCell, dice);

				if (currentPlayer.getCurrentCell().getIndex() == 63) {
					this.isFinished = true;
					System.out.println(currentPlayer.getName() + " has won.");
				}

				previousCell.welcome(null);
			} else if (previousCell instanceof WaitingCell || previousCell instanceof TrapCell) {
                            
                                 if(previousCell.getIndex()==31)
                                    str="Well ";
                                 else if(previousCell.getIndex()==52)
                                    str="Prison ";
                                 else if(previousCell.getIndex()==19)
                                    str="Inn ";
                                 else
                                    str ="";
                            
				String trace = currentPlayer.getName() + " is in "
                                                +str+"cell "
						+ previousCell.getIndex() + ", "
						+ currentPlayer.getName() + " cannot play";
				System.out.println(trace);
			}

			// gives the next player or gives the first player if the current player is the last of the list
			idPlayer = this.board.players.indexOf(this.currentPlayer);
			this.currentPlayer = nextPlayer(idPlayer);
		}
	}
        
	// Random throw of a die, returns a number between one and six, return the value of the throw (between 1 and 6)
	public int throwDie() {
		Random r = new Random();
		return r.nextInt(6) + 1;
	}

	// Returns the next player of the list of players, if he is the last player, it goes back to the first one in the list, return the next player
	public Player nextPlayer(int idCurrentPlayer) {
		if (idCurrentPlayer + 1 == 3) {
			return this.board.players.get(0);
		}
		return this.board.players.get(idCurrentPlayer + 1);
	}

	// Initializes the players and adds them to the player list.
	public void initializePlayers() {
		p1 = new Player("p1", board.cells.get(0));
		p2 = new Player("p2", board.cells.get(0));
		p3 = new Player("p3", board.cells.get(0));

		this.board.players.add(p1);
		this.board.players.add(p2);
		this.board.players.add(p3);
	}

	// Returns the cell truly reached by the move.targetCell = The cell normally reached by the player
	public Cell computeTargetCell(Cell targetCell, int dice) {
		return this.board.cells.get(board.normalize(targetCell.handleMove(dice),dice));
	}

	//Displays the trace for the GooseCells, TeleportCells and NormalCells. previousCell = Previous cell of the current player
	//targetCell = Cell normally reached by the player after the throws ,realCell = Cell really reached by the player 
	public void displayTrace(Cell previousCell, Cell targetCell, Cell realCell,int dice) 
        {
		String trace;
                String str;
		if (targetCell instanceof GooseCell) {
			trace = currentPlayer.getName() + " is in cell "
					+ previousCell.getIndex() + ", " + currentPlayer.getName()
					+ " throws " + dice + ", reaches goose "
					+ targetCell.getIndex() + " and jumps to "
					+ (realCell.getIndex());
			System.out.println(trace);
		} 
                else if (targetCell instanceof TeleportCell) {
                    
                        if(targetCell.getIndex()==58)
                           str="Death ";
                        else if(targetCell.getIndex()==42)
                           str="Labyrinth ";
                        else if(targetCell.getIndex()==6)
                           str="Bridge ";
                        else
                           str ="";
                        
			trace = currentPlayer.getName() + " is in cell "
					+ previousCell.getIndex() + ", " + currentPlayer.getName()
					+ " throws " + dice + ", reaches "
                                        +str+"cell "
					+ targetCell.getIndex() + " and jumps to "
					+ realCell.getIndex();
			System.out.println(trace);
		} 
                else {
			trace = currentPlayer.getName() + " is in cell "
					+ previousCell.getIndex() + ", " + currentPlayer.getName()
					+ " throws " + dice + ", reaches cell "
					+ (realCell.getIndex());
			System.out.println(trace);
		}
	}

	// It moves a player in the cell he has to be, if there is another player in this cell, it swaps the two players, realCell = cell really reached by the player
	public void movePlayer(Cell realCell) {
		if (realCell.isBusy()) {
			this.board.swapPlayer(this.currentPlayer, realCell.getPlayer());
			currentPlayer.setCurrentCell(realCell);
			realCell.welcome(this.currentPlayer);
		} else {
			realCell.welcome(currentPlayer);
			currentPlayer.setCurrentCell(realCell);
		}
	}

	public static void main(String[] args) {
		ArrayList<Player> playerList = new ArrayList<Player>(3);
		ArrayList<Cell> cellTable = new ArrayList<Cell>(64);
                
		Board b = new Board(playerList, cellTable);
                
		Game g = new Game(b);
                
		b.initializeBoard(63);  // create board
                
		g.initializePlayers();  // create players
                
		g.play();               // starts the game
	}
}
