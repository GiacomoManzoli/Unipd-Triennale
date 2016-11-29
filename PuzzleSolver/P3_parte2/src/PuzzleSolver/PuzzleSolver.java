package PuzzleSolver;

import Puzzle.*;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;


public class PuzzleSolver {

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

	public static void main(String[] args) {
		System.out.println("Puzzle Solver Avviato con " +args.length);
		
		String inputFile, outputFile;

		if (args.length == 2){
			inputFile = args[0];
			outputFile = args[1];
			System.out.println(inputFile);
			System.out.println(outputFile);
			
			Path inputPath = Paths.get(inputFile);
			Path outputPath = Paths.get(outputFile);

			System.out.println("Puzzle Solver Avviato");
			Puzzle puzzle = new Puzzle(inputPath);
			printPuzzle(outputPath,puzzle);
		}
		else {

			int times = 30;
			int[] x = new int[]{1,4,5,6,5,8,1,-1,-1}; //righe
			int[] y = new int[]{1,4,5,5,6,1,4,-1,-1};
			int r = 0;
			int errorcount = 0;

			Puzzle puzzle;
			for (int i = 1; i <= 7; i++) {
				while (r<times){
					//System.out.println("----------------------Input"+i+" Iterazione:"+r);
					r++;
					inputFile="./test/test"+i;
					outputFile ="./test/soluzione"+i;

					Path inputPath = Paths.get(inputFile);
					Path outputPath = Paths.get(outputFile);

					puzzle = new Puzzle(inputPath);
					/*
					System.out.println("Soluzione:");
					System.out.println(puzzle.getText());
					System.out.println("");
					System.out.println(puzzle.print());
					System.out.println("");
					System.out.println(puzzle.getRowNumber()+" "+puzzle.getColNumber());
						*/
					printPuzzle(outputPath,puzzle);

					if (puzzle.getColNumber() != y[i-1] || puzzle.getRowNumber() != x[i-1]){
						System.err.println("Input "+i+" Iterazione "+r);
						errorcount++;
						break;
					}
				}

				r=0;
			}
			System.out.println("Ho completato le iterazioni");
			System.out.println("Errori: "+errorcount);
		}


	}

}
