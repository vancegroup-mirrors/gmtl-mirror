default: guide ref
all: guide ref man
usage:
	@echo gmake guide      (for gmtl programmer guide: html, pdf, txt)
	@echo gmake guide-html (for gmtl programmer guide: html)
	@echo gmake guide-pdf  (for gmtl programmer guide: pdf)
	@echo gmake guide-txt  (for gmtl programmer guide: txt)
	@echo gmake man        (for man page reference)
	@echo gmake ref        (for html reference manual)
	@echo gmake clean      (remove everything that was built)

reference ref r:
	doxygen gmtl.doxy

manpage man m:
	doxygen gmtl.man.doxy

guide g:
	-cd programmer.guide && gmake

guide-html:
	-cd programmer.guide && gmake html
guide-pdf:
	-cd programmer.guide && gmake pdf
guide-txt:
	-cd programmer.guide && gmake txt


clean:
	-rm -rf html man
	-cd programmer.guide && gmake clean clobber
