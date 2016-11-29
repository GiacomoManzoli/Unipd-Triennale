package Puzzle;

import java.io.BufferedReader;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

class LoaderThread extends Thread{

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

    private Path inputPath;
    private PuzzleElementList pezzi;

    public LoaderThread(Path inputPath, PuzzleElementList pezzi){
        this.inputPath = inputPath;
        this.pezzi=pezzi;
    }
    public LoaderThread(Path inputPath, PuzzleElementList pezzi, String name){
        this.inputPath = inputPath;
        this.pezzi=pezzi;
        super.setName(name);
    }
    public void run() {
        Charset charset = StandardCharsets.UTF_8;
        try (BufferedReader reader = Files.newBufferedReader(inputPath, charset)) {
            String line;
            while ((line = reader.readLine()) != null) {
                /* line: linea del file che ho letto.
                * Ha la forma: id_pezzo \t carattere \t id_nord \t id_est \t id_sud \t id_ovest*/
                String[] parts = line.split("\t");
                if (parts.length == 6) {
                    PuzzleElement p = LoaderThread.createElement(parts);
                    pezzi.add(p);
                } else {
                    Exception e = new Exception("Problema con il caricamento del file: " + inputPath.toString());
                    throw e;
                }
            }
        } catch (Exception e) {
            System.err.println(e.toString());
        }
    }
}
