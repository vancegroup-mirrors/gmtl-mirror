default: guide ref
all a: gh gp gt rh rm rp
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

ref reference rh:
	doxygen gmtl.doxy

ref-latex rl:
	doxygen gmtl.latex.doxy

ref-pdf rp: rl
	-rm -r pdf
	-mkdir  pdf
	cd latex && make ps && ps2pdf *.ps ../pdf/ref-guide.pdf
	-rm -r latex

man ref-man rm manpage m:
	doxygen gmtl.man.doxy

guide g:
	-cd programmer.guide && gmake

guide-html gh:
	-cd programmer.guide && gmake html
guide-pdf gp:
	-cd programmer.guide && gmake pdf
guide-txt gt:
	-cd programmer.guide && gmake txt

# useful for creating a tree that can be tarred up and posted to a 
# website for download.
#
# prefix: Specify the dir you want the docs dumped into, can be a 
#         new dir one level deep.  Defaults to "./installed"
prefix ?=./installed
version ?=0.0.1
install:
	-mkdir $(prefix)
	-cp -r html $(prefix)/gmtlReferenceGuide-$(version)-html
	-cp -r man $(prefix)/gmtlReferenceGuide-$(version)-man
	-cp pdf/ref-guide.pdf $(prefix)/gmtlReferenceGuide-$(version).pdf
	-cp programmer.guide/guide.pdf $(prefix)/gmtlProgrammersGuide-$(version).pdf
	-mkdir $(prefix)/gmtlProgrammersGuide-$(version)-html
	-cp programmer.guide/guide.html $(prefix)/gmtlProgrammersGuide-$(version)-html/index.html

tarballname ?=gmtldocs-$(version)
tempdirname ?=temp-gmtldoc16981418215
tarball:
	-mkdir $(tempdirname)
	$(MAKE) prefix=$(tempdirname)/$(tarballname) install
	cd $(tempdirname) && tar -zcvf $(tarballname).tgz $(tarballname) && mv $(tarballname).tgz ../ && rm $(tempdirname)

clean c:
	-rm -rf html man pdf latex installed $(tempdirname)
	-cd programmer.guide && gmake clean clobber

clobber: clean
	-rm $(tarballname).tgz
