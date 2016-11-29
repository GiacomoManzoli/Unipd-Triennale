package Puzzle;

import java.util.*;

//Rappresenta una tessera di un puzzle

//Visibilità package
class PuzzleItem implements PuzzleElement {

	static final public String EMPTY_ID="VUOTO";

	//Parte Non Statica
	private String id;
	private String value;
	private String top;
	private String right;
	private String bottom;
	private String left;

	public PuzzleItem(String id, String value, String top, String right, String bottom, String left){
		this.id=id;
		this.value = value;

		this.top = top;
		this.right = right;
		this.bottom = bottom;
		this.left = left;
	}

	//Implementazione PuzzleElement
	/* ritorna l'id dell'elemento che si deve attaccare nel dato lato*/
	public String getTop() {
		return top;
	}
	public String getBottom() {
		return bottom;
	}
	public String getRight() {
		return right;
	}
	public String getLeft() {
		return left;
	}

	public String getID() {
		return id;
	}


	private boolean canAttachHorizzontally(PuzzleElement item) {
		return	this.getID().equals(item.getRight()) ||
				this.getID().equals(item.getLeft());
	}
	/* Due PuzzleItem non si possono accattare verticalmente tra loro */
	//private boolean canAttachVertically(PuzzleElement item) {return	false;}

	public boolean canAttach(PuzzleElement item){return canAttachHorizzontally(item);}


	public PuzzleElement attach(PuzzleElement item) {
		List<PuzzleElement> newItem = item.getComponents();

		if (this.canAttachHorizzontally(item)){
			if (this.getID().equals(item.getLeft())){
				//L'elemento corrente deve essere a sinistra dell'elemento ricevuto per parametro
				//quindi inserisco in testa
				newItem.add(0,this);
			}else{
				//L'elemento corrente deve esssere a destra dell'elemento ricevuto per parametro
				newItem.add(this);
			}
			PuzzleElement newRow = new PuzzleRow(newItem);
			if (newRow.isComplete()){
                /*Se la nuova riga che ho creato è completa, è anche un PuzzleBlock di una riga sola.
                * Questa cosa è un fattore chiave il corretto funzionamento parallelo*/
				List<PuzzleElement> t = new ArrayList<>();
				t.add(newRow);
				return new PuzzleBlock(t);
			}else{
				return newRow;
			}
		}
		return null;
	}

	public boolean isComposed(){
		return false;
	}
	public boolean isComplete() {
		return 	top.equals(PuzzleItem.EMPTY_ID) &&
				right.equals(PuzzleItem.EMPTY_ID) &&
				bottom.equals(PuzzleItem.EMPTY_ID) &&
				left.equals(PuzzleItem.EMPTY_ID);
	}

	public int getColCount() { return 1; }
	public int getRowCount() { return 1; }

	/* Ritorna una lista di elementi che lo compongono*/
	public List<PuzzleElement> getComponents() {
		List<PuzzleElement> comps = new ArrayList<>();
		comps.add(this);
		return comps;
	}

	public String print() {
		return value;
	}

	public String toString() {
		return id + "@" + value;
	}


}
