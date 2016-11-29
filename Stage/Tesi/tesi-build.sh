#!bin/bash
echo "Compilo la tesi"
pdflatex tesi.tex
biber tesi
makeglossaries glossario.tex
makeindex -s tesi.ist -t tesi.glg -o tesi.gls tesi.glo
makeindex -s tesi.ist -t tesi.alg -o tesi.acr tesi.acn
pdflatex tesi.tex
pdflatex tesi.tex
echo "Compilazione completata"