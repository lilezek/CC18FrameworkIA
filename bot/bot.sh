# Versión C++ del script de ejecución.

dir=$(realpath --relative-to=`pwd` "$(dirname "$0")")
program=main  

usage() {
  echo "$0 (build|exec)" 
}

# Compilar el bot
build() {
  make clean
  make
}

# Ejecutar el bot
execute() {
  ./$program
}

if [ $# -ne 1 ]
then
  usage
else
  case "$1" in
  "exec")
    execute
  ;;
  "build")
    build
  ;;
  *)
    usage
  ;;
  esac
fi