export ASAN_SYMBOLIZER_PATH=/usr/local/bin/llvm-symbolizer-3.4
export ASAN_OPTIONS=symbolize=0

g++ -g3 -fno-omit-frame-pointer -fsanitize=address main.cpp
