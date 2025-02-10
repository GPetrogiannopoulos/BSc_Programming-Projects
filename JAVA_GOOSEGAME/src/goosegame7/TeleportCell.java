package goosegame7;

// Class which defines the TeleportCell of the Game, when a TeleportCell is reached it sends a player to another cell.
public class TeleportCell extends NormalCell 
{
	int dest;
	
    // Constructor of a TeleportCell that creates a TeleportCell at the index given in parameters and also set his destination.  
    // idx = Index of the TeleportCell that will be created. 
    // dest = Index of the destination where the player will be sent.
	public TeleportCell(int idx, int dest){
		super(idx);
		this.dest = dest;
	}
	
    // Returns the index of the cell really reached by a player when he reaches this cell.For a TeleportCell, the returned value is equals to this.dest. return Index of the destination
	public int handleMove(int diceThrow){
		return this.dest; // Returns to another cell
	}
}
