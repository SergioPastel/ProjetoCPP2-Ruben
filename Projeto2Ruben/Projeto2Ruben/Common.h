#pragma once

// Header contendo todas as bibliotecas que o programa usa a fim de evitar codigo repetitivo

#include<iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <locale.h> // Para permitir caracteres especiais
#include <conio.h> // Adicionado para usar o comando _getch, que interrompe limpezas de tela for de hora esperando um input do user
#include <vector> // Necessário para usar vetores
#include <algorithm> // adicionador para verificar a igualdade entre strings: transform e tolower
#include <limits> // Necessário para as funções de validações
#include <sstream> // Necessário para std::ostringstream
#include <map> // Necessário para usar mapas (dicionários)
#define RESET   "\033[0m" // Reseta a cor para o padrão.
#define RED     "\033[31m" // Define a cor vermelha.
#define GREEN   "\033[32m" // Define a cor verde.
#define CYAN    "\033[36m" // Define a cor ciano.

