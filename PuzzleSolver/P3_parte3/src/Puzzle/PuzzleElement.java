package Puzzle;

import java.util.List;

/**
 * PuzzleElement:
 *  Modella un tipo che rappresenta un elemento concatenabile, questo elemento può a sua volta essere composto
 *  da più elementi già concatenati.
 *  Ogni PuzzleElement deve essere identificato in modo univoco da una stringa.
 */
public interface PuzzleElement {

    /* ritorna l'id dell'elemento che si deve attaccare nel dato lato*/
    public String getTop();
    public String getRight();
    public String getBottom();
    public String getLeft();

    public String getID();

    /* Ritorna true quando i due item possono essere attaccati in un lato*/
    public boolean canAttach(PuzzleElement item);
    //public boolean canAttachHorizzontally(PuzzleElement item);
    //public boolean canAttachVertically(PuzzleElement item);

    /* Crea un nuovo AttachabelItem ottenuto a partire dalla concatenazione dell'elemento corrente con l'elemento
    * passato per parametro */
    public PuzzleElement attach(PuzzleElement item);


    /* indica se l'elemento è un singolo elemento (return false) o se è composto da più elementi */
    public boolean isComposed();
    public boolean isComplete();

    /* numero di righe e colonne che compongono il pezzo del puzzle*/
    public int getRowCount();
    public int getColCount();

    /* Ritorna una lista di elementi che lo compongono*/
    public List<PuzzleElement> getComponents();

    public String print();
}
