compile:
	cc main.c -o regexLite

zip:
	zip ../FinalProject_ECE3331_Team1/*

format:
	clang-format main.c > tmp
	mv tmp main.c

check:
	./regexLite test/*.txt
	./regexLite -n test/*.txt "e" "input|output"
	./regexLite -i test/*.txt "INput|output"
	./regexLite -c test/*.txt "input|output"
	./regexLite -o test/*.txt "input|output"
	./regexLite -v test/1.txt "match"
	./regexLite -vo test/*.txt "e"
