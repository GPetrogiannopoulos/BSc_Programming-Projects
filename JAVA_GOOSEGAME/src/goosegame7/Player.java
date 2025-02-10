package goosegame7;

// Class which defines a Player, a Player has a name and a current cell.
public class Player {

	protected String name;
	protected Cell currentCell;
	
	public Player(){
		
	}
	
        // Constructor of a Player, it creates a Player with a name and a currentCell, both given in parameters
	public Player(String name, Cell currentCell){
		this.name = name;
		this.currentCell = currentCell;
	}

        // Gives the current cell of the player, return the current cell of the player
	public Cell getCurrentCell() {
		return currentCell;
	}

        // Sets the cell of a player , currentCell New value of the Player's current cell.
	public void setCurrentCell(Cell currentCell) {
		this.currentCell = currentCell;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
}
