package Puzzle;


import java.io.Serializable;

public class Puzzle implements Serializable{

    private static Puzzle emptyPuzzle = new Puzzle();
    public static Puzzle EmptyPuzzle() { return emptyPuzzle;}

    private PuzzleElement solution;


    private Puzzle(){solution=null;}
    public Puzzle(PuzzleElementList listaPezzi) throws BadPuzzleException{
        Thread currentThread = Thread.currentThread();
        System.out.println("Risolvo il puzzle sul thread:" +currentThread.getName());

        if (!listaPezzi.isComplete()) {
            /* Se la lista dei pezzi che ho ricevuto non è già un puzzle completo, provo a risolverlo.*/
            SolverThread solver1 = new SolverThread(listaPezzi, "Rosso 1");
            SolverThread solver2 = new SolverThread(listaPezzi, "Rosso 2");
            solver1.start();
            solver2.start();
            try {
            /* Quando un Solver finisce il puzzle, gli altri Solver se ne accorgono e terminano anche loro, il solver su
            * cui fare join è dunque indifferente */
                while (!listaPezzi.hasBeenCompleted()) {
                    solver1.join(2500);
                    if (solver1.getState() == Thread.State.WAITING &&
                            solver2.getState() == Thread.State.WAITING) {
                        solver1.interrupt();
                        solver2.interrupt();
                    /* Se si sono fermati tutti e due i solver vuol dire che sono stati inviati al server
                    * dei dati errati.
                    * Lancio un'eccezione*/
                        throw new BadPuzzleException("Non è stato possibile risolvere il puzzle");
                    }
                }
                synchronized (listaPezzi) {
                    listaPezzi.notifyAll(); // Può essere che si sia messo a dormire qualche thread sulla lista dei pezzi
                }
                //System.out.println("Rosso Leader: Ho gli schemi della Death Star");
                //Viene svegliato quando il puzzle è stato risolto
            } catch (InterruptedException e) {
                System.err.println(e.getMessage());
                solution = null;
            }
        }
        solution = listaPezzi.remove(0);
        System.out.println("Termino");
    }



    public int getColNumber(){
        if (solution != null){
            return solution.getColCount();
        } else {
            return -1;
        }
    }

    public int getRowNumber(){
        if (solution != null){
            return solution.getRowCount();
        } else {
            return -1;
        }
    }

    public String getText(){
        if (solution != null){
            return solution.print().replaceAll("\n","");
        } else {
            return "Soluzione non trovata";
        }
    }

    public String print(){
        if (solution != null){
            return solution.print().trim(); //Toglie eventali ritorni a capo.
        } else {
            return "Soluzione non trovata";
        }
    }
}
