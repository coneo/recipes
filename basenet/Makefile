SUBDIRS = test

all: $(SUBDIRS)

$(SUBDIRS):
	cd $@ && make

clean:
	for d in $(SUBDIRS); do cd $$d && make clean && cd ..; done

.PHONY: all clean $(SUBDIRS)
