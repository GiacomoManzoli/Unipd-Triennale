package Puzzle;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

public class Puzzle {

    private static List<PuzzleElement> loadData(Path inputPath){
        Charset charset = StandardCharsets.UTF_8;
        List<PuzzleElement> items = new ArrayList<>();
        try (BufferedReader reader = Files.newBufferedReader(inputPath, charset)) {
            String line;
            while ((line = reader.readLine()) != null) {
				/* line: linea del file che ho letto.
				* Ha la forma: id_pezzo \t carattere \t id_nord \t id_est \t id_sud \t id_ovest*/
                String[] parts = line.split("\t");
                if (parts.length == 6){
                    items.add(Puzzle.createElement(parts));
                }else{
                    Exception e = new Exception("Problema con il caricamento del file: "+inputPath.toString());
                    throw e;
                }
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
        return items;
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
    	    String validChar="!?.,:;\"( )";
            return s.length()==1 &&
                    (Character.isLetterOrDigit(s.charAt(0)) || validChar.contains(s));
    }


    private PuzzleElement solution;


    public Puzzle(Path inputPath){
        List<PuzzleElement> items = Puzzle.loadData(inputPath); //ritorna null se non è riuscito a caricare la lista.
        if (items.size()>0 && solve(items)) {
            //items contiene un solo elemento che è la soluzione
            solution = items.get(0);
        }else {
            solution=null;
        }
    }

    private boolean solve(List<PuzzleElement> pezzi){

        /*Ripeto finché non è rimasto solo un pezzo e questo pezzo è completo*/
        while (pezzi.size() > 1 && !(pezzi.get(0).isComplete() && pezzi.size()==1)){
            PuzzleElement anItem = pezzi.remove(0);
            int i=0;

            while (i < pezzi.size() && !anItem.canAttach(pezzi.get(i))){
                i++;
            }
            if (i != pezzi.size()){
                PuzzleElement itemToAttach = pezzi.remove(i);

                pezzi.add(anItem.attach(itemToAttach));
            }
        }

        /*L'ultimo pezzo rimasto è completo*/
        PuzzleElement sol = pezzi.get(0);

        /* !sol.isComposed considera anche il caso degenere in cui il puzzle ha una tessera solo.*/
        //return !sol.isComposed() || sol.isComplete();
        return sol.isComplete();
        /*Equivale a:
        if (sol.isComposed()) {
            return sol.isComplete();
        } else {

            return true;
        }*/
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
