#
#
#
.PHONY: help build clean run

help:
	@echo help - this message
	@echo build - build release
	@echo clean - clean build
	@echo run - run build

src/ui/Makefile: src/ui/ui.pro
	(cd src/ui ; qmake)

clean: src/ui/Makefile
	@make -C src/ui clean
	@rm -f src/ui/Makefile

build: src/ui/Makefile
	@make -C src/ui

run:
	@open build/logicaide.app

