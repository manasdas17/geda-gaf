## Process this file with automake to produce Makefile.in

EXTRA_DIST = gafrc.hierarchy2 hierarchy2.geda top.sch under.sch under.sym

# Temporarily disabled make check, since this is interfering with 
# make distcheck
check_SCRIPTS = tests

BUILDDIR=$(top_builddir)/tests/hierarchy2
SRCDIR=$(srcdir)

tests: tests-job tests-clean

tests-job:
	rm -f $(BUILDDIR)/new_*
	( export TESTDIR=$(SRCDIR); \
	  echo $$TESTDIR; \
	  cp -f $(SRCDIR)/gafrc.hierarchy2 $(BUILDDIR)/gafrc; \
	  gnetlist \
	     -o $(BUILDDIR)/new_hierarchy2.geda -g geda \
	     $(SRCDIR)/top.sch )
	diff $(SRCDIR)/hierarchy2.geda $(BUILDDIR)/new_hierarchy2.geda;

tests-clean:
	rm -f $(BUILDDIR)/gafrc

MOSTLYCLEANFILES = new_* core *.log FILE *.ps *~
CLEANFILES = new_* core *.log FILE *.ps *~
DISTCLEANFILES = *.log core FILE *~ prototype.bak
MAINTAINERCLEANFILES = new_* core *.log FILE *.ps *~ Makefile.in configure



