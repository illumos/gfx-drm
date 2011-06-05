
# This is just for ctfmerge; copy from the build machine.

GUDIR=/platform/sun4u/kernel

DBG_LINKS= debug64/genunix
OBJ_LINKS= obj64/genunix

def:		all
all: $(DBG_LINKS) $(OBJ_LINKS)

$(DBG_LINKS) : FRC
	-mkdir debug64
	-rm -f $(DBG_LINKS)
	ln -s $(GUDIR)/sparcv9/genunix debug64/genunix

$(OBJ_LINKS) : FRC
	-mkdir obj64
	-rm -f $(OBJ_LINKS)
	ln -s $(GUDIR)/sparcv9/genunix obj64/genunix

clean:	FRC
	-rm -f $(DBG_LINKS) $(OBJ_LINKS)

clobber:

lint:

modlintlib:

clean.lint:

install: all

FRC:
