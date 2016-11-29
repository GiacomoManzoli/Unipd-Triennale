package com.company;

import java.io.*;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Random;
import java.nio.charset.*;


public class Main {
    private static Charset charset = StandardCharsets.UTF_8;

    public static void main(String[] args) {
        String frase;
        int r=1,c=1;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        try{
            System.out.println("Inserisci la frase");
            frase = br.readLine();
            System.out.println("Inserisci il numero di righe");
            r = Integer.parseInt(br.readLine());
            System.out.println("Inserisci il numero di colonne");
            c = Integer.parseInt(br.readLine());
        } catch (Exception e){
            frase = "Ciao";
        }

        int expectedChar = r * c;

        while (frase.length() < expectedChar){
            frase+="#";
        }
        if (frase.length() > expectedChar){
            frase = frase.substring(0,expectedChar);
        }

        //La frase è pronta
        String[][] matrice = new String[r][c];
        int index=0;
        for (int i = 0; i <r; i++) {
            for (int j = 0; j < c; j++) {
                matrice[i][j]=String.valueOf(frase.charAt(index));
                index++;
            }
        }


        String[][] newMatrice = new String[r][c];
        for (int i = 0; i <r; i++) {
            for (int j = 0; j < c; j++) {
                String toWrite = "";
                //ID
                toWrite += (matrice[i][j] + "r" + i + "c" + j);
                toWrite += "\t";
                //Char
                toWrite += matrice[i][j];
                toWrite += "\t";
                //nord
                try {
                    toWrite += matrice[i - 1][j] + "r" + (i - 1) + "c" + j;
                } catch (Exception e) {
                    toWrite += "VUOTO";
                }
                toWrite += "\t";
                //est
                try {
                    toWrite += matrice[i][j + 1] + "r" + i + "c" + (j + 1);
                } catch (Exception e) {
                    toWrite += "VUOTO";
                }
                toWrite += "\t";
                //sud
                try {
                    toWrite += matrice[i + 1][j] + "r" + (i + 1) + "c" + j;
                } catch (Exception e) {
                    toWrite += "VUOTO";
                }
                toWrite += "\t";
                //ovest
                try {
                    toWrite += matrice[i][j - 1] + "r" + i + "c" + (j - 1);
                } catch (Exception e) {
                    toWrite += "VUOTO";
                }


                newMatrice[i][j]=toWrite;
            }
        }
        //newMatrice conitene PuzzleItem stringato
        //La matrice è popolata, Shake it off
        Random rand = new Random();
        //r è il numero di righe
        //c è il numero di colonne
        for (int i = 0; i<100;i++){
            int a = Math.abs(rand.nextInt()%(r));
            int b = Math.abs(rand.nextInt()%(c));
            int e = Math.abs(rand.nextInt()%(r));
            int d = Math.abs(rand.nextInt()%(c));

            String temp = newMatrice[a][b];
            newMatrice[a][b] = newMatrice[e][d];
            newMatrice[e][d] = temp;
        }
        try {
            //Whatever the file path is.
            File statText = new File("./"+(frase.hashCode()%1000));

            BufferedWriter w = Files.newBufferedWriter(statText.toPath(),charset);

            int cnt=0;
            for (int i = 0; i <r; i++) {
                for (int j = 0; j < c; j++) {
                    String toWrite="";
                    //ID
                    toWrite+=(newMatrice[i][j]);

                    toWrite+="\n";
                    w.write(toWrite);
                }
            }
            w.close();
        } catch (IOException e) {
            System.err.println("Problem writing to the file statsTest.txt");
        }





        System.out.println("Finito");
    }




}
