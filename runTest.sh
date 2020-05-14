#! /bin/zsh
# rm -rf *.o
if [[ ! -d bin ]]; then
  mkdir bin;
fi
 gcc -c test/*.c linkedlist.c
 gcc -o bin/test.out *.o
 rm -rf *.o
 ./bin/test.out