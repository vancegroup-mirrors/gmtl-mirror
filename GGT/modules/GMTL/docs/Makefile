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
	@echo "- gmake clean      (remove everything that was built)"
	@echo ""

reference ref r:
	doxygen gmtl.doxy

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
