package Puzzle;

import java.util.ArrayList;
import java.util.List;

/*Rappresenta un blocco di righe complete*/

//Visibilità package
class PuzzleBlock implements PuzzleElement {

    private List<PuzzleElement> rows = new ArrayList<>();

    private PuzzleElement firstItem, lastItem;



    public PuzzleBlock(List<PuzzleElement> rs){
        rows=rs;
        firstItem = rows.get(0);
        lastItem = rows.get(rows.size()-1);
    }


    /* ritorna l'id dell'elemento che si deve attaccare nel dato lato*/
    public String getTop(){return firstItem.getTop();}
    public String getBottom(){return lastItem.getBottom();}

    public String getRight(){return PuzzleItem.EMPTY_ID;}
    public String getLeft(){return PuzzleItem.EMPTY_ID;}

    public String getID(){return firstItem.getID();}

    /* Ritorna true quando i due item possono essere attaccati in un lato*/
    /* Essendo un blocco di righe complete non posso attaccarci nulla orizzontalmente*/
    //private boolean canAttachHorizzontally(PuzzleElement item){return false;}
    private boolean canAttachVertically(PuzzleElement item){
        return  canAttachOnTop(item) || canAttachOnBottom(item);
    }

    public boolean canAttach(PuzzleElement item){
        return canAttachVertically(item);
    }

    /* Crea un nuovo AttachabelItem ottenuto a partire dalla concatenazione dell'elemento corrente con l'elemento
    * passato per parametro */
    public PuzzleElement attach(PuzzleElement item) {
        List<PuzzleElement> items=item.getComponents();
        if (canAttachOnTop(item)) {
            items.addAll(rows);
            return new PuzzleBlock(items);
        } else if (canAttachOnBottom(item)){
            items.addAll(0,rows);
            return new PuzzleBlock(items);
        }else return null;
    }

    private boolean canAttachOnTop(PuzzleElement item){
        //Il controllo sul rowcount serve per evitare di attaccare ad un blocco righe incomplete e o pezzi singoli.
        //nel caso di un murphy attack prima poteva succedere.
        return item.getBottom().equals(firstItem.getID()) && getColCount() == item.getColCount();
    }
    private boolean canAttachOnBottom(PuzzleElement item){
        return item.getTop().equals(lastItem.getID()) && getColCount() == item.getColCount();
    }


    /* indica se l'elemento è un singolo elemento (return false) o se è composto da più elementi */
    public boolean isComposed(){return true;}
    public boolean isComplete(){
        return getTop().equals(PuzzleItem.EMPTY_ID) && getBottom().equals(PuzzleItem.EMPTY_ID);
    }
    /* Ritorna una lista di elementi che lo compongono*/
    public List<PuzzleElement> getComponents(){return rows;}


    public int getRowCount(){
        return rows.size();
    }
    public int getColCount(){
        return firstItem.getColCount();
    }

    public String print(){
        String res = "";
        for(PuzzleElement i:rows){
            res +=i.print()+"\n";
        }
        return  res;
    }
    public String toString(){
        String res = "";
        for(PuzzleElement i:rows){
            res +=i.toString()+"\n";
        }
        return  res;
    }
}
