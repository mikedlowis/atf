#------------------------------------------------------------------------------
# Build Configuration
#------------------------------------------------------------------------------
# Update these variables according to your requirements.

# tools
CC = c99
LD = ${CC}
AR = ar

# flags
INCS      = -Isource/ -Itests/
CPPFLAGS  = -D_XOPEN_SOURCE=700
CFLAGS   += ${INCS} ${CPPFLAGS}
LDFLAGS  += ${LIBS}
ARFLAGS   = rcs

#------------------------------------------------------------------------------
# Build Targets and Rules
#------------------------------------------------------------------------------
SRCS = source/atf.c
OBJS = ${SRCS:.c=.o}
TEST_SRCS = tests/main.c tests/test_signals.c
TEST_OBJS = ${TEST_SRCS:.c=.o}

all: options libatf.a testatf

options:
	@echo "Toolchain Configuration:"
	@echo "  CC       = ${CC}"
	@echo "  CFLAGS   = ${CFLAGS}"
	@echo "  LD       = ${LD}"
	@echo "  LDFLAGS  = ${LDFLAGS}"
	@echo "  AR       = ${AR}"
	@echo "  ARFLAGS  = ${ARFLAGS}"

libatf.a: ${OBJS}
	@echo AR $@
	@${AR} ${ARFLAGS} $@ ${OBJS}

testatf: ${TEST_OBJS} libatf.a
	@echo LD $@
	@${LD} -o $@ ${TEST_OBJS} libatf.a ${LDFLAGS}
	-./$@
	@echo "Note: It is expected that exactly 2 of the tests will fail."

.c.o:
	@echo CC $<
	@${CC} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f libatf.a testatf ${OBJS} ${TEST_OBJS}

.PHONY: all options

