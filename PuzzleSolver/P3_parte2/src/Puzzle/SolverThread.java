package Puzzle;


public class SolverThread extends Thread{

    private PuzzleElementList pezzi;

    public SolverThread(PuzzleElementList pezzi){
        this.pezzi=pezzi; //Salvo il riferimento alla lista condivisa tra thread.
    }
    public SolverThread(PuzzleElementList pezzi, String name){
        this.pezzi=pezzi; //Salvo il riferimento alla lista condivisa tra thread.
        super.setName(name);
    }

    public void run(){
        /* Il thread va avanti finché il puzzle non è risolto */

        while (!pezzi.hasBeenCompleted()){
            PuzzleElement anItem=null, attachableItem;
            /*Quando sono qui non so quanti pezzi ci sono, so solo che il puzzle presente nella lista
            * non è ancora stato completato  */
            synchronized (pezzi) {
                if (pezzi.size() < 2) {
                    /* Può essere che mentre il thread che eseguiva questo codice era in coda per entrare nel blocco synchronized
                     * un altro thread abbia risolto il puzzle, verifico e nel caso esco.
                     * Uso return, così il thread corrente termina
                     * In questo modo, se sono il thread che il main thread sta aspettando l'esecuzione del programma
                     * può continuare*/
                    if (pezzi.hasBeenCompleted()) {
                        //System.out.println(super.getName()+": Mi hanno finito il puzzle");
                        return;
                    }
                    /* Se c'è al massimo un solo pezzo e il puzzle non è già stato completato vuol dire che devono essere ancora
                    * caricati. Questo perché secondo le specifiche ci sono tutti i pezzi.
                    * Quindi vuol dire che il thread di caricamento deve ancora finire di caricarli oppure che ci sono pochi pezzi
                    * e sono già stati presi in carico da altri thread.
                    * Il thread quindi si mette in wait sulla lista dei pezzi ad aspettare che un pezzo venga aggiunto */
                    try {
                        pezzi.wait();
                        /*Quando il thread si sveglia viene forzata la riesecuzione del ciclo while in modo da controllare che
                        * il puzzle non sia stato risolto nel mentre e nel caso terminare l'esecuzione del thread*/
                        continue;
                    } catch (InterruptedException e) {
                        System.err.println(e.getMessage());
                    }
                } else {
                    /* Ci sono alemno due pezzi, li prendo*/
                    anItem = pezzi.remove(0);
                }
            } //fine Sync.

            /* A questo punto sono sicuro che anItem sia un pezzo del puzzle non completo e che NON è condiviso con altri thread*/

            attachableItem = pezzi.removeAttachableTo(anItem);
            /* Per quanto riguarda attachableItem o è Null perché non è stato trovato nessun pezzo compatibile con anItem
            * oppure è un pezzo di puzzle non completo, che si può combinare con anItem e che NON è condiviso con altri thread.*/
            if (attachableItem != null){
                /* Creo un nuovo elemento a partire dai due che ho preso dalla lista, sono sicuro che l'operazione va a buon fine
                * perché se i due item non fossero compatibili attachableItem sarebbe stato Null*/
                //System.out.println(super.getName()+": Attacco due pezzi");
                //System.out.println(super.getName()+anItem.print());
                //System.out.println(super.getName()+attachableItem.print());
                PuzzleElement newItem = anItem.attach(attachableItem);

                /* Aggiungo il nuovo item alla lista.
                * La sincornizzazione è fatta lato server, inoltre in con questa chiamata viene eseguito notifyAll per svegliare
                * altri thread che stavano aspettando i pezzi*/

                 pezzi.add(newItem);
            } else {
                /* Non è stato trovato nessun elemento compatibile, vuol dire che non è ancora stato caricato oppure è in fase di
                * elaborazione da parte di un altro thread.
                * L'elemento viene quindi rimesso nella lista condivisa perché potrebbe servire ad altri thread.*/

                pezzi.add(anItem);
            }
        }
    }
}
