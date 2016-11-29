package PuzzleServer;

import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.server.ExportException;

public class PuzzleSolverServer {

    public static void main(String[] args){
        //1 solo parametro: nome del server
        String serverName = "RossoLeader";
        if (args.length==1){
            serverName = args[0];
        }
        System.out.println(serverName+": Server avviato");
        try{
            //Creo l'oggetto remoto
            PuzzleMaker maker = new PuzzleMakerImp();
            //Genero un nome con cui pubblicizzare l'oggetto
            String makerName = "rmi://localhost/"+serverName;
            Naming.rebind(makerName,maker);
            System.out.println(serverName+": Server pronto");
        }catch  (ExportException e){
            System.err.println("Errore durante l'avvio del server");
            //System.err.println(e.getMessage());
        }catch (RemoteException e){
            System.err.println("Errore durante l'inizializzazione dell'oggetto remoto");
        }catch (MalformedURLException e){
            System.err.println("Errore durante la pubblicazione dell'oggetto");
        }

    }
}
