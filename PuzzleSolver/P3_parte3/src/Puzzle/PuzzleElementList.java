package Puzzle;

import java.io.BufferedReader;
import java.io.Serializable;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

public class PuzzleElementList implements Serializable {
    /* ArrayList non è thread safe, viene quindi wrappato all'interno di un oggetto che sarà thread safe.*/
    private List<PuzzleElement> lista;
    /* Flag che indica che la il puzzle rappresentato dalla lista è stato completato o meno.*/
    private boolean completed = false;
    public PuzzleElementList(){
        lista = new ArrayList<>();
    }

    public PuzzleElementList(Path filePath) throws Exception{
        lista = loadFromFile(filePath);
    }

    public synchronized void add(PuzzleElement e){
        /* Per scelte progettuali una volta che il puzzle memorizzato su una PuzzleElementList è stato risolto non è più
        * possibile aggiungere pezzi alla lista. */
        if (!completed) {
            lista.add(e);
            /*Se il puzzle è stato completato, vuol dire che un thread ha preso gli unici due pezzi presenti nella lista dei
            * pezzi (svuotandola) e ha aggiunto il pezzo completo che ha ottenuto unendo i due che ha preso.
            * Il metodo add aggiunge quindi alla lista l'unico pezzo completo.
            * Essendoci un unico pezzo completo il flag completed viene messo a false.*/
            if (isComplete()) {
                completed = true;
            }
        }
        /* Sveglia eventuali thread che stavano aspettando dei pezzi*/
        this.notifyAll();
    }

    /*Wrappa il metodo remove, se la lista è vuota viene ritornato null*/
    public synchronized PuzzleElement remove(int i){
        if (lista.size() == 0)
            return null;
        return lista.remove(i);
    }

    public synchronized boolean hasBeenCompleted(){
        /*Dato che per la sementaica di isComplete() può essere che un thread Solver trovi la lista vuota perché il
        * thread principale si è già il pezzo completo è necessario usare questo metodo per segnalare al solver che la festa
        * è finita.*/
        return completed;
    }

    public synchronized int size(){
        return lista.size();
    }

    public synchronized boolean isComplete(){
        /* Ritorna true se la lista contiente un singolo pezzo e questo pezzo è completo*/
        boolean isSingleElementAndComplete = lista.size()==1 && lista.get(0).isComplete();
        /*Vero, però è possibile che quando viene chiamato isComplete() ci sia solo un pezzo, che sia completo ma che il puzzle non sia completo:
        * c'è una PuzzleRow completa anche se il Puzzle ha più righe, queste possono non essere presenti perché ancora da caricare
        * o affidate ad altri thread.*/

        /*Cambiando e fornzano il fatto che una PuzzleRow completa diventa subito un PuzzleBlock composto da una sola riga
        * fa si che non si possa verificare la situazione descritta prima. */
        return isSingleElementAndComplete;// && lista.get(0).isComposed();// && lista.get(0).getComponents().get(0).isComplete();
    }

    public synchronized PuzzleElement removeAttachableTo(PuzzleElement element){
        /*Cerca un pezzo della lista che si possa attaccare ad element, lo rimuove dalla lista e lo ritorna.
         Se non trova niente ritorna null*/

        /*Essendo un metodo syncronized una volta che inizio a cercare sono sicuro che l'unico thread ha accesso alla lista
        * dei pezzi è il thread che sta eseguendo questo metodo. Grazie a questo lock sono sicuro che la lista può essere modifciata
        * solo da questo thread.*/

        int i=0;
        while (i < lista.size() && !element.canAttach(lista.get(i))) {
            i++;
        }
        if (i == lista.size()){
            //non ho trovato niente
            return null;
        } else {
            return lista.remove(i);
        }
    }

    private List<PuzzleElement> loadFromFile(Path filePath) throws Exception{
        List<PuzzleElement> pezzi = new ArrayList<>();
        Charset charset = StandardCharsets.UTF_8;
        BufferedReader reader = Files.newBufferedReader(filePath, charset);
        String line;
        while ((line = reader.readLine()) != null) {
            /* line: linea del file che ho letto.
            * Ha la forma: id_pezzo \t carattere \t id_nord \t id_est \t id_sud \t id_ovest*/
            String[] parts = line.split("\t");
            if (parts.length == 6) {
                PuzzleElement p = createElement(parts);
                pezzi.add(p);
            } else {
                Exception e = new Exception("Problema con il caricamento del file: " + filePath.toString());
                throw e;
            }
        }
        return pezzi;
    }

    private static PuzzleElement createElement(String[] parts) throws Exception{
        /*Questo metodo si occupa di verificare che i dati siano corrette e di creare un oggetto del tipo giusto:
        * - PuzzleItem quando la stringa mi rappresenta un Item
        * - PuzzleBlock quando l'item rappresentato dalla stringa è già una riga completa */

        if (!verify(parts[1])){
            Exception e = new Exception("Problema con la tessera '"+parts[1]+"'");
            throw e;
        }
        PuzzleElement item = new PuzzleItem(parts[0],parts[1],parts[2],parts[3],parts[4],parts[5]);
        //Controllo se è una riga completa sfruttando il fatto che se lo stesso ID compare sia a destra
        //sia a sinistra del puzzle allora deve essere PuzzleItem.EMPTY_ID
        if (item.getLeft().equals(item.getRight())){
            //Costruisco una riga
            item = new PuzzleRow(item.getComponents());
            //Essendo una riga completa può anche essere vista come un blocco di righe.
            item = new PuzzleBlock(item.getComponents());
        }
        return item;
    }

    private static boolean verify(String s){
        return s.length()==1;
    }
}
