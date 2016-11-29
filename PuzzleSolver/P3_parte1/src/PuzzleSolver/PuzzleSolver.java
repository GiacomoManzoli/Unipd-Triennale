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
		System.out.println("Puzzle Solver Avviato");

		String inputFile, outputFile;

		if (args.length == 2){
			inputFile = args[0];
			outputFile = args[1];
			Path inputPath = Paths.get(inputFile);
			Path outputPath = Paths.get(outputFile);

			System.out.println("Puzzle Solver Avviato");
			Puzzle puzzle = new Puzzle(inputPath);
			printPuzzle(outputPath,puzzle);
		}
		else {
			for (int i = 1; i <= 10; i++) {
				inputFile="./test"+i;
				outputFile ="./soluzione"+i;

				Path inputPath = Paths.get(inputFile);
				Path outputPath = Paths.get(outputFile);


				//Carica i dati dal file e creo il puzzle
				//List<PuzzleElement> lista = loadData(inputPath);

				//Risolvi il puzzle
				System.out.println("Puzzle Solver Avviato");
				Puzzle puzzle = new Puzzle(inputPath);

				System.out.println("Soluzione:");
				System.out.println(puzzle.getText());
				System.out.println("");
				System.out.println(puzzle.print());
				System.out.println("");
				System.out.println(puzzle.getRowNumber()+" "+puzzle.getColNumber());

				//Salva i dati nel file
				printPuzzle(outputPath,puzzle);
			}
		}


	}

}
