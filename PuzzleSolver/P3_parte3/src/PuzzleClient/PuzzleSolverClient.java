package PuzzleClient;


import PuzzleServer.PuzzleMaker; /*Interfaccia del remote object*/
import Puzzle.*;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class PuzzleSolverClient{

    public static void main(String[] args){
        System.out.println("Puzzle Solver Avviato con " +args.length);

        String inputFile, outputFile, serverName;

        if (args.length == 3){
            inputFile = args[0];
            outputFile = args[1];
            serverName = args[2];
            System.out.println("Input file: "+inputFile);
            System.out.println("Output file: "+outputFile);
            System.out.println("Server name: "+serverName);

            Path inputPath = Paths.get(inputFile);
            Path outputPath = Paths.get(outputFile);

            System.out.println("Client avviato");

            PuzzleElementList listaPezzi=null;
            try {
                listaPezzi = new PuzzleElementList(inputPath);
            } catch (Exception e){
                /* Si è verificato un errore con il caricamento del file perché non era ben formato oppure non esisteva.
                * Viene stampato un errore, prodotto come file di output un file contenente la stampa di un Puzzle senza soluzione
                 * e viene terminato il programma client*/
                System.err.println("Errore con il caricamento del file");
                printBadPuzzle(outputPath);
                return;
            }
            if (listaPezzi.size() == 0){
                printBadPuzzle(outputPath);
                return;
            }
            try{

                /*Recupero l'oggetto remoto che mi crea e risolve un puzzle in automatico.*/
                PuzzleMaker remoteMaker = (PuzzleMaker)Naming.lookup("rmi://localhost/"+serverName);

                /*Chiamo il metodo remoto makePuzzle, il quale crea un Puzzle a partire dalla lista di Pezzi e lo risolve.
                * Il Puzzle risolto viene serializzato e reinviato al client trammite valore di ritorno.
                *
                * Mentre aspetta il client si mette in attesa*/
                System.out.println("Invoco il metodo remoto");
                Puzzle solvedPuzzle = remoteMaker.makePuzzle(listaPezzi);

                System.out.println("Stampo il puzzle");
                /* Stampo il Puzzle risolto */
                printPuzzle(outputPath,solvedPuzzle);

            }catch (BadPuzzleException e) {
                /*Sollevata quando il server non riesce a risolvere il puzzle*/
                System.err.println(e.getMessage());
                printBadPuzzle(outputPath);
            }catch (RemoteException e) {
                /*Sollevata quando il tento di connettermi ad un server spento oppure il server muore mentre sono in attesa del valore*/
                System.err.println("Errore di comunicazione con il server.");
                System.err.println(e.getMessage());
                printBadPuzzle(outputPath);
            }catch (NotBoundException e){
                /*Sollevata quando tento di accedere ad un remote object che non è nel registro*/
                System.err.println("Indirizzo del server errato");
                printBadPuzzle(outputPath);
                System.err.println(e.getMessage());
            }catch (Exception e){
                System.err.println("Errore generico");
                printBadPuzzle(outputPath);
                System.err.println(e.getClass() + " "+ e.getMessage());
            }


        }
    }

    private static void printBadPuzzle(Path outputPath){
        printPuzzle(outputPath,Puzzle.EmptyPuzzle());
    }


    private static void printPuzzle(Path file, Puzzle puzzle){
        Charset charset = StandardCharsets.UTF_8;
        try (BufferedWriter writer = Files.newBufferedWriter(file, charset)) {
            writer.write(puzzle.getText());
            writer.newLine();
            writer.newLine();
            writer.write(puzzle.print());
            writer.newLine();
            writer.newLine();
            writer.write(puzzle.getRowNumber() + " " + puzzle.getColNumber());
            writer.flush();
        } catch (IOException e) {
            System.out.println(e.toString());
        }
    }

}
