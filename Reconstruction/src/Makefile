########################################################################	
##
## ---------------------------
##   Makefile for KalTest
## ---------------------------
##
## (Version Information)
##   Version: 0.2
##   Release: 1
##
## (Update Record)
##    2002/01/18  K.Hoshina     Derived from baby/src/Makefile
##    2002/10/21  K.Fujii       Cleanup.
##
## (Description)
##   In order to use this package you should first set some
##   environmental variables. Take a look at README in the
##   top directory.
##
## (Targets)
##	all       	: creates libraries in lib.
##	Makefiles 	: creates Makefiles.
##	clean     	: deletes *.o ...
##	distclean 	: deletes even lib/*.
## 
########################################################################	
SHELL =/bin/bash
MFLAGS	=
CURRDIR	= .

SUBDIRS	= ALSim RKFitter ALPatternRecognition

all:
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS); do \
	(cd $$i; echo ``making'' all ``in $(CURRDIR)/$$i...''; \
	xmkmf -a; \
	$(MAKE) $(MFLAGS) install); \
	done
	
Makefiles:
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS); do \
	(cd $$i; echo ``making'' Makefiles ``in $(CURRDIR)/$$i...''; \
	xmkmf); \
	done
	
clean: Makefiles
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS); do \
	(cd $$i; echo ``making'' clean ``in $(CURRDIR)/$$i...''; \
	$(MAKE) $(MFLAGS) clean); \
	done

distclean: clean
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS); do \
	(cd $$i; echo ``making'' distclean ``in $(CURRDIR)/$$i...''; \
	$(MAKE) $(MFLAGS) distclean); \
	done; \
	rm -rf lib include

