#!/bin/bash

# Muda para o diretório do script, independentemente de onde o script é chamado
cd "$(dirname "$0")" || exit

# Cria o diretório 'build' se não existir, navega até ele, executa o cmake, faz a build e volta para o diretório inicial
mkdir -p build && cd build && cmake .. && make && cd ..
