#pragma once

#include "Loja.h"

// Declaração de funções utilitárias (não são validações ou métodos principais das classes)

class Funcoes {
	public:
		static std::string toMinuscula(string);
		static void exibirMenu();
		static void submenuEstoque(Loja&);
		static void submenuClientes(Loja&);
		static void submenuRelatorios(Loja&);
};