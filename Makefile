compile:
	cc *.c -o regexLite

zip:
	zip ../FinalProject_ECE3331_Team1/*

format:
	clang-format main.c > tmp
	mv tmp main.c

test:
	./regexLite test/*.txt
	./regexLite -in test/*.txt "e" "INput|output"
	./regexLite -i test/*.txt "e" "INput|output"
