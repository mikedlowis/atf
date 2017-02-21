VERSION = 0.0.1
DISTDIR   = atf-${VERSION}
DISTTAR   = ${DISTDIR}.tar
DISTGZ    = ${DISTTAR}.gz
DISTFILES = atf.h LICENSE.md Makefile README.md tests.c

tests: tests.c
	@echo "============================================"
	@echo "NOTE: It is expected that 3 tests will fail."
	@echo "============================================"
	$(CC) -I. -o $@ $^
	-./$@

clean:
	$(RM) tests $(DISTGZ)

dist: clean
	mkdir -p ${DISTDIR}
	cp -R ${DISTFILES} ${DISTDIR}
	tar -cf ${DISTTAR} ${DISTDIR}
	gzip ${DISTTAR}
	rm -rf ${DISTDIR}
