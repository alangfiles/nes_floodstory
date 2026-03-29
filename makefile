# makefile for nesdoug example code, for Linux
# this version won't move the final files to BUILD folder
# also won't rebuild on changes to neslib/nesdoug/famitone files

CC65 = cc65
CA65 = ca65
LD65 = ld65
NAME = noahman
CFG = MMC1_128_128.cfg


.PHONY: default clean

default: $(NAME).nes


#target: dependencies

$(NAME).nes: $(NAME).o crt0.o $(CFG)
	$(LD65) -C $(CFG) -o $(NAME).nes crt0.o $(NAME).o nes.lib -Ln labels.txt --dbgfile dbg.txt
	rm *.o
	@echo $(NAME).nes created

crt0.o: crt0.s CHRS/stage1.chr CHRS/stage2.chr MUSIC/TestMusic3.s MUSIC/SoundFx.s
	$(CA65) crt0.s

$(NAME).o: $(NAME).s
	$(CA65) $(NAME).s -g

$(NAME).s: $(NAME).c noahman.h bank0.h bank1.h bank2.h bank3.h bank4.h bank5.h bank6.h sprites.h LEVELS/Stage1/Stage1.c LEVELS/Stage2/Stage2.c LEVELS/Stage3/Stage3.c LEVELS/Stage4/Stage4.c LEVELS/Stage5/Stage5.c
	$(CC65) -Oirs $(NAME).c --add-source

clean:
	rm $(NAME).nes
