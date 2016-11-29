package Puzzle;


import java.nio.file.Path;



public class Puzzle {

    private PuzzleElement solution;


    public Puzzle(Path inputPath){

        PuzzleElementList listaPezzi = new PuzzleElementList();

        LoaderThread loader = new LoaderThread(inputPath,listaPezzi, "Millenium Falcon");
        loader.start();

        SolverThread solver1 = new SolverThread(listaPezzi,"Rosso 1");
        SolverThread solver2 = new SolverThread(listaPezzi,"\t \tRosso 2");
        //SolverThread solver3 = new SolverThread(listaPezzi,"\t \t \t \tRosso 3");
        //SolverThread solver4 = new SolverThread(listaPezzi,"\t \t \t \t \t \tRosso 4");
        solver1.start();
        solver2.start();
        //solver3.start();
        //solver4.start();

        try {
            /* Quando un Solver finisce il puzzle, gli altri Solver se ne accorgono e terminano anche loro, il solver su
            * cui fare join è dunque indifferente */
            solver1.join();
            synchronized (listaPezzi) {
                listaPezzi.notifyAll(); // Può essere che si sia messo a dormire qualche thread sulla lista dei pezzi
            }
            //System.out.println("Rosso Leader: Ho gli schemi della Death Star");
            //Viene svegliato quando il puzzle è stato risolto
            solution = listaPezzi.remove(0);
        }catch (InterruptedException e){
            System.err.println(e.getMessage());
            solution=null;
        }

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
