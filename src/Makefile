FLAGS = -Wall -Werror -Wextra -std=c11

all: 3DViewer.a

3DViewer.a:
	gcc -c $(FLAGS) parcer.c affine_transformation.c
	ar rc 3DViewer.a *.o
	ranlib 3DViewer.a

test: 3DViewer.a
	gcc -c $(FLAGS) test.c
	gcc -lcheck -fprofile-arcs -ftest-coverage parcer.c affine_transformation.c 3DViewer.a test.o  -o tests
	./tests
	
gcov_report:	test
	gcov -i *.gcda	
	lcov -t "3DV" -o 3DV.info -c -d .
	genhtml -o report 3DV.info
	cd report/ && open index.html
	# gcovr --html-details -o report.html
	# open report.html

install:
	cd 3DViewer && qmake6 && make && make clean && cd ../ &&  mv 3DViewer/QOpenGLWidget.app  ~/Desktop

uninstall:
	rm -rf 3DViewer/QOpenGLWidget.app 
	rm -rf ~/Desktop/QOpenGLWidget.app
	rm -rf 3DViewer/Makefile
	
dvi:
	doxygen Doxyfile
	open ./html/index.html

dist: install
	mkdir archiv
	cp -r *.c *.h Makefile 3DViewer/ archiv
	tar -cvzf 3DViewer.tar.gz archiv
	rm -rf archiv

style:
	clang-format -n *.c *.h

leaks:
	leaks -atExit -- ./tests
clean:
	rm -rf *.o *.a *.gcno  *.gcda *.gcov *.css report html latex *.dSYM report *.info *.gz
	rm -rf tests