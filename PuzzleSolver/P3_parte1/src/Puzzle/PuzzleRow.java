package Puzzle;

import java.util.ArrayList;
import java.util.List;

//Visibilità package
class PuzzleRow implements PuzzleElement {

    private List<PuzzleElement> row = new ArrayList<>();

    private PuzzleElement firstItem,lastItem;


    public PuzzleRow(List<PuzzleElement> itemList){
        row=itemList;
        firstItem = itemList.get(0);
        lastItem = itemList.get(itemList.size()-1);
    }



    //Implementazione PuzzleElement

    /* ritorna l'id dell'elemento che si deve attaccare nel dato lato*/
    public String getRight(){return lastItem.getRight();}
    public String getLeft(){return firstItem.getLeft();}
    public String getTop(){return firstItem.getTop();}
    public String getBottom(){return firstItem.getBottom();}

    /*Ogni riga viene identificata dall'id del primo AttchableItem che la compone*/
    public String getID(){ return firstItem.getID();}


    private boolean canAttachHorizzontally(PuzzleElement item){
        return	firstItem.getID().equals(item.getRight()) ||
                lastItem.getID().equals(item.getLeft());
    }
    private boolean canAttachVertically(PuzzleElement item){
        /* Ad una riga posso attaccare sopra o sotto cose solo se è completa.
        * Se item è di tipo PuzzleBlock, item.isComplete() è false se gli manca questa riga,
        * quindi per soddisfare sia la condizione che due righe si possono attaccare verticalmente
        * se sono complete, sia la condizione che una riga si può attaccare ad un blocco solo se è completa
        * devo usare this.isComplete() per capire se questa riga è completa e confrontare il ColCount di this
        * con quello di item.
        * In questo modo se this è completa e this e item è una riga, si possono attaccare se item ha le stesse colonne
        * di this, essendo this una riga completa anche item è una riga completa.
        * Se this è una riga completa e item un blocco, item sarà composto solamente da righe complete quindi
        * il ColCount di item sarà uguale al ColCount di this.*/
        return	(firstItem.getID().equals(item.getTop()) ||
                firstItem.getID().equals(item.getBottom())) && isComplete() && (getColCount() == item.getColCount());
    }

    public boolean canAttach(PuzzleElement item){
        return canAttachHorizzontally(item) || canAttachVertically(item);
    }

    public PuzzleElement attach(PuzzleElement item) {

        List<PuzzleElement> newItem = new ArrayList<>();

        if (this.canAttachHorizzontally(item)){
            newItem.addAll(item.getComponents());
            if (firstItem.getID().equals(item.getRight())){
                //L'elemento corrente deve essere a destra dell'elemento ricevuto per parametro
                //quindi inserisco in testa
                newItem.addAll(row);
            }else{
                //L'elemento corrente deve esssere a sinistra dell'elemento ricevuto per parametro
                newItem.addAll(0, row);
            }
            return new PuzzleRow(newItem);
        }
        /*Se la riga è piena la posso attaccare sopra o sotto ad un'altra riga creando un blocco*/
        if (this.canAttachVertically(item)){
            /*Devo attaccare a questa riga o un'altra riga o un blocco di righe.
            * Per discriminare cosa ci sto attaccando uso RowCount*/
            if (item.getRowCount()==1) {
                newItem.add(item);
            }else{
                newItem.addAll(item.getComponents());
            }
            if (this.getID().equals(item.getTop())){
                //L'elemento corrente deve essere sopra dell'elemento ricevuto per parametro
                //quindi inserisco in testa
                newItem.add(0, this);
            }else{
                //L'elemento corrente deve esssere sotto dell'elemento ricevuto per parametro
                newItem.add(this);
            }
            return new PuzzleBlock(newItem);
        }
        return null;
    }


    public boolean isComposed(){ return true;}
    public boolean isComplete(){
        return firstItem.getLeft().equals(PuzzleItem.EMPTY_ID) && lastItem.getRight().equals(PuzzleItem.EMPTY_ID);
    }


    public int getRowCount(){
        return 1;
    }
    public int getColCount(){
        return row.size();
    }

    /* Ritorna una lista di elementi che lo compongono*/
    public List<PuzzleElement> getComponents() {return row;}

    public String print(){
        String result ="";
        for(PuzzleElement p:row){
            result += p.print();
        }
        return result;
    }

    public String toString(){
        String result ="";
        for(PuzzleElement p:row){
            result += p.toString();
        }
        return result;
    }

}
