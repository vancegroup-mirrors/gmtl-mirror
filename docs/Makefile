default: guide ref
all a: guide ref man
usage u help h:
	@echo ""
	@echo "Targets:"
	@echo "- gmake guide      (for gmtl programmer guide: html, pdf, txt)"
	@echo "- gmake guide-html (for gmtl programmer guide: html)"
	@echo "- gmake guide-pdf  (for gmtl programmer guide: pdf)"
	@echo "- gmake guide-txt  (for gmtl programmer guide: txt)"
	@echo "- gmake man        (for man page reference)"
	@echo "- gmake ref        (for html reference manual)"
	@echo "- gmake ref-latex  (for latex reference manual)"
	@echo "- gmake ref-pdf    (for pdf reference manual)"
	@echo "- gmake clean      (remove everything that was built)"
	@echo ""

reference ref r rh:
	doxygen gmtl.doxy

ref-latex rl latex:
	doxygen gmtl.latex.doxy

ref-pdf rp pdf: latex
	-mkdir  pdf
	cd latex && make ps && ps2pdf *.ps ../pdf/ref-guide.pdf

manpage man m:
	doxygen gmtl.man.doxy

guide g:
	-cd programmer.guide && gmake

guide-html gh:
	-cd programmer.guide && gmake html
guide-pdf gp:
	-cd programmer.guide && gmake pdf
guide-txt gt:
	-cd programmer.guide && gmake txt


clean c:
	-rm -rf html man
	-cd programmer.guide && gmake clean clobber
