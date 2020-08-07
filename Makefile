#
#
#
.PHONY: help build clean run

help:
	@echo help - this message
	@echo build - build release
	@echo clean - clean build
	@echo run - run build

clean:
	(cd src/ui ; make clean)

build:
	(cd src/ui ; qmake ; make)

run:
	open build/logicaide.app

