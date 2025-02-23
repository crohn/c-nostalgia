CC = gcc
CFLAGS = -Wall -Werror -std=c99

DIR_SRC = src
DIR_DIST = dist

.PHONY: kr-%

kr-%:
	$(eval PARTS := $(subst -, ,$*))
	$(eval CHAP  := $(word 1,$(PARTS)))
	$(eval EX    := $(word 2,$(PARTS)))
	$(eval REV   := $(if $(word 3,$(PARTS)),$(word 3,$(PARTS)),0))
	$(eval SRC   := $(DIR_SRC)/kernighan-ritchie/chap-$(CHAP)/ex-$(CHAP)_$(EX).$(REV).c)
	$(eval TGT   := $(DIR_DIST)/ex-$(CHAP)_$(EX))
	$(CC) $(CFLAGS) $(SRC) -o $(TGT)

