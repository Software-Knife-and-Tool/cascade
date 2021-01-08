##########
##
##  SPDX-License-Identifier: BSD-3-Clause
##
##  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
##
##

.PHONY: help build clean clobber run install format

help:
	@echo help - this message
	@echo build - build release
	@echo clean - clean build
	@echo clobber - clobber build
	@echo run - run build

src/ui/Makefile:
	(cd src/ui ; qmake)

clean:
	# @make -C src/ui clean
	@rm -f src/ui/Makefile

clobber: clean
	@rm -rf build/*


format:
	(cd ./src/ui && clang-format -i *.h *.cpp)

build:
	(cd src/ui ; qmake)
	@make -C src/ui

run:
	@open build/gyre-ui.app

install:
	@cp gyre-ui.l ~/.gyre-ui

