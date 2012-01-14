PDF_PRODUCER=pdflatex
LATEX_FILE=rapport.tex
PDF_VIEWER=evince

PHONY: all clean view do_anyway

all: $(LATEX_FILE)
	$(PDF_PRODUCER) $(LATEX_FILE)
	$(PDF_PRODUCER) $(LATEX_FILE) 

view: all
	$(PDF_VIEWER) *.pdf &

do_anyway: 

clean: do_anyway
	@rm -rf *.toc *~ *.lof *.aux  *.log *.out *.bbl *.blg *.nav *.snm
	@rm -rf src/*~ img/#*


