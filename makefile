# makefile for nesdoug example code, for Linux
# this version won't move the final files to BUILD folder
# also won't rebuild on changes to neslib/nesdoug/famitone files

CC65 = cc65
CA65 = ca65
LD65 = ld65
NAME = floodstory
CFG = MMC1_128_128.cfg


.PHONY: default clean

default: $(NAME).nes


#target: dependencies

$(NAME).nes: $(NAME).o crt0.o $(CFG)
	$(LD65) -C $(CFG) -o $(NAME).nes crt0.o $(NAME).o nes.lib -Ln labels.txt --dbgfile dbg.txt
	rm *.o
	@echo $(NAME).nes created

crt0.o: crt0.s CHRS/1.chr CHRS/2.chr CHRS/3.chr CHRS/4.chr CHRS/5.chr CHRS/6.chr CHRS/7.chr CHRS/8.chr CHRS/9.chr CHRS/10.chr CHRS/11.chr CHRS/12.chr CHRS/13.chr CHRS/14.chr CHRS/15.chr CHRS/16.chr MUSIC/TestMusic3.s MUSIC/SoundFx.s
	$(CA65) crt0.s

$(NAME).o: $(NAME).s
	$(CA65) $(NAME).s -g

$(NAME).s: $(NAME).c floodstory.h animations.h bank0.h bank1.h bank2.h bank3.h bank4.h bank5.h bank6.h sprites.h LEVELS/Stage1/Stage1.c LEVELS/Stage2/Stage2.c LEVELS/Stage3/Stage3.c LEVELS/Stage4/Stage4.c LEVELS/Stage5/Stage5.c
	$(CC65) -Oirs $(NAME).c --add-source

clean:
	rm $(NAME).nes
