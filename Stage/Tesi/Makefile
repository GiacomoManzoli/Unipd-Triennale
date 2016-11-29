TEX = pdflatex -interaction=nonstopmode -halt-on-error -file-line-error

document:
	$(TEX) tesi.tex
	biber tesi
	$(TEX) tesi.tex
	makeindex -s tesi.ist -t tesi.glg -o tesi.gls tesi.glo
	makeindex -s tesi.ist -t tesi.alg -o tesi.acr tesi.acn
	$(TEX) tesi.tex
	$(TEX) tesi.tex

correct-chapter-1:
	aspell -c capitoli/capitolo-1.tex -d it

correct-chapter-2:
	aspell -c capitoli/capitolo-2.tex -d it

correct-chapter-3:
	aspell -c capitoli/capitolo-3.tex -d it

correct-chapter-4:
	aspell -c capitoli/capitolo-1.tex -d it

correct-appendix-A:
	aspell -c capitoli/capitolo-A.tex -d it

