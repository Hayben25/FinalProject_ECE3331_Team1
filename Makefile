compile:
	cc *.c -o regexLite

test:
	regexLite test/*

zip:
	zip ../FinalProject_ECE3331_Team1/*

format:
	clang-format main.c > tmp
	mv tmp main.c
