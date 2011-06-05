
# This is just for ctfmerge; copy from the build machine.

GUDIR=/kernel

DBG_LINKS= debug32/genunix debug64/genunix
OBJ_LINKS= obj32/genunix obj64/genunix

def:		all
all: $(DBG_LINKS) $(OBJ_LINKS)

$(DBG_LINKS) : FRC
	-mkdir debug32 debug64
	-rm -f $(DBG_LINKS)
	ln -s $(GUDIR)/genunix debug32/genunix
	ln -s $(GUDIR)/amd64/genunix debug64/genunix

$(OBJ_LINKS) : FRC
	-mkdir obj32 obj64
	-rm -f $(OBJ_LINKS)
	ln -s $(GUDIR)/genunix obj32/genunix
	ln -s $(GUDIR)/amd64/genunix obj64/genunix

clean:	FRC
	-rm -f $(DBG_LINKS) $(OBJ_LINKS)

clobber: clean

lint:

modlintlib:

clean.lint:

install: all

FRC:
