#
#
#
.PHONY: help build clean run install

help:
	@echo help - this message
	@echo build - build release
	@echo clean - clean build
	@echo run - run build

src/ui/Makefile:
	(cd src/ui ; qmake)

clean:
	@make -C src/ui clean
	@rm -f src/ui/Makefile

build:
	(cd src/ui ; qmake)
	@make -C src/ui

run:
	@open build/gyre-ide.app

install:
	@cp gyre-ide.l ~/.gyre-ide

