package PuzzleServer;


import Puzzle.*;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface PuzzleMaker  extends Remote {
    public Puzzle makePuzzle(PuzzleElementList pezzi) throws RemoteException, BadPuzzleException;
}
