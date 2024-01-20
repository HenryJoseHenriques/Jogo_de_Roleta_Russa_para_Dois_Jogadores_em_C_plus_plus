#include <iostream>
#include <time.h>
#include "RoletaLib.h"

int main() {
  TamborDaArma<6> Balas;
  Participante<2,3> Jogadores;
  RoletaRussa(Jogadores, Balas);
}