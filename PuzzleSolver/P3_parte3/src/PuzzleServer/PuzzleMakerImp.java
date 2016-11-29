package PuzzleServer;


import Puzzle.*;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

class PuzzleMakerImp extends UnicastRemoteObject implements PuzzleMaker{
    private static int puzzleSolved = 0;

    public PuzzleMakerImp() throws RemoteException{
    	System.out.println("PuzzleMaker creato");
    }

    public Puzzle makePuzzle(PuzzleElementList pezzi) throws RemoteException, BadPuzzleException {
    	System.out.println("PuzzleMaker.makePuzzle "+puzzleSolved);
        puzzleSolved++;
        return new Puzzle(pezzi);
    }
}


