for dotc_file in ./src/*.c; do
  clang -g -fPIC -c "$dotc_file" -I./include/ -I./src/ -o "$dotc_file.o"
done

doto_files=""

for doto_file in ./src/*.c.o; do
  doto_files="${doto_files} ${doto_file}"
done

ar rcs bin/libcontinuum.a $doto_files
clang -g -shared -o bin/libcontinuum.so $doto_files
 
clang -g -o bin/program program/program.c -I./include -L./bin -l:libcontinuum.a

rm ./src/*.c.o


install='install'
uninstall='uninstall'

case "$1" in
  "$install")
    cp bin/libcontinuum.so ~/.local/lib/
    cp bin/libcontinuum.a ~/.local/lib/
  ;;
  "$uninstall")
    rm ~/.local/lib/libcontinuum.so
    rm ~/.local/lib/libcontinuum.a
  ;;
  *)
    
  ;;
esac
