#pragma once

#include "Funcoes.h"

// Validações e tratamentos de tipos utilizada em todo o codigo

class Validacoes {
	public:
		static void limparBufferEntrada();
		static void tratarErroEntrada();
		static float obterFloat(const string&);
		static int validacaoInt(const string&);
};
