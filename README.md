This project only supports out of source builds. The include paths in the header file
look for prefix 'fool'.

Dependencies:
origin library from: https://github.com/hiraditya/origin

g++ > 4.9

For out of source builds:

1. Download the sources in $DIR/fool, such that $DIR/fool/fool is the git repository.

2. mkdir -p $DIR/build.

3. cd $DIR/build

4. cmake ../fool

5. make

You might want to modify the top level CMakeLists.txt, for appropriate include paths.
