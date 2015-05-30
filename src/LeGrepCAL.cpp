//============================================================================
// Name        : LeGrepCAL.cpp
// Author      : Diogo Moura
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include "mingw.thread.h"
#include <cctype>
#include "Grep.h"
#include "auxFunc.h"

using namespace std;

void runGrep(Grep * grep);

int main(int argc, char* argv[]) {
	cout << "Grep" << endl;

	int linhasAntes = 1, linhasDepois = 1, temp;
	bool invertMatch = false, ignoreCase = false, needleFound = false;
	string needle, tempString;

	Grep::SSA algoritmo_temp = Grep::BOYER_MOORE;

	vector<string> files;
	vector<Grep *> search;

	//Analisar Flags introduzidas e activar respetivas flags
	for (int i = 1; i < argc; ++i) {
		string flag(argv[i]);
		//TODO Falta flags alternativas para cada tipo

		if (flag == "-A" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 1;
			} else if (linhasDepois <= temp) {
				linhasDepois = temp;
			}
			i++;
		} else if (flag == "-B" && i + 1 <= argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 2;
			} else if (linhasAntes <= temp) {
				linhasAntes = temp;
			}
			i++;
		} else if (flag == "-C" && i + 1 < argc) {
			stringstream(argv[i + 1]) >> temp;

			if (!isdigit(argv[i + 1][0])) {
				cerr << "Argumento " << argv[i + 1] << " não é um numero de linha" << endl;
				return 3;
			} else if (linhasAntes <= temp && linhasDepois <= temp) {
				linhasDepois = temp;
				linhasAntes = temp;
			}
			i++;
		} else if (flag == "-i") {
			ignoreCase = true;

		} else if (flag == "-v") {
			invertMatch = true;
		} else if (flag.compare(0, 16, "--after-context=") == 0) {
			stringstream(flag.substr(16, flag.length())) >> temp;
			if (temp >= 99) {
				cerr << "Numero Linhas exagerado " << endl;
				return 0;
			} else {
				if (linhasDepois < temp) {
					linhasDepois = temp;
				}
			}
		} else if (flag.compare(0, 17, "--before-context=") == 0) {
			stringstream(flag.substr(17, flag.length())) >> temp;
			if (temp >= 99) {
				cerr << "Numero Linhas exagerado " << endl;
				return 0;
			} else {
				if (linhasAntes < temp) {
					linhasAntes = temp;
				}
			}
		} else if (flag.compare(0, 10, "--context=") == 0) {
			stringstream(flag.substr(10, flag.length())) >> temp;
			if (temp >= 99) {
				cerr << "Numero Linhas exagerado " << endl;
				return 0;
			} else {
				if (linhasAntes < temp) {
					linhasAntes = temp;
				}
				if (linhasDepois < temp) {
					linhasDepois = temp;
				}
			}
		} else if (flag == "--ignore-case") {
			ignoreCase = true;
		} else if (flag == "--invert-match") {
			invertMatch = true;
		} else if (flag.compare(0, 12, "--algorithm=") == 0) {
			tempString = flag.substr(12, flag.length());

			if (tempString == "naive") {
				algoritmo_temp = Grep::NAIVE;
			} else if (tempString == "boyermoore") {
				algoritmo_temp = Grep::BOYER_MOORE;
			} else if (tempString == "kmp") {
				algoritmo_temp = Grep::KMP;
			} else {
				cerr << "Wrong Algorithm!" << endl;
			}
		} else if (needleFound) {
			files.push_back(string(flag));

		} else if (needleFound == false) {
			needle = flag;
			needleFound = true;
		}
	}

	//Verificar se existe a palavra a pesquisar
	if (needle.empty()) {
		cerr << "Word to search not found!";
		return 1;
	}

	//Verificar se exitem ficheiros
	if (files.empty()) {
		cerr << "Files to search not found!";
		return 1;
	}

	//Redimensionar o tamanha da consola para 1500 linhas em vez de 300
	COORD newSize;
	newSize.X=160;
	newSize.Y=1500;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),newSize);

	/*CONSOLE_SCREEN_BUFFER_INFO infoBufferConsole;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&infoBufferConsole);
	cout<<"colunas: "<<infoBufferConsole.dwSize.X<<"linhas: "<<infoBufferConsole.dwSize.Y<<endl;*/



	//Criar Objecto do tipo Grep e inicializacao do buffer com o conteudo do ficheiro
	for (unsigned int i = 0; i < files.size(); i++) {
		ifstream ficheiro;
		ficheiro.open(files[i].c_str());

		if (!ficheiro.is_open()) {
			cerr << "Erro Abrir Ficheiro " << files[i] << endl;
			return 1;
		}

		string haystack((std::istreambuf_iterator<char>(ficheiro)), (std::istreambuf_iterator<char>()));

		search.push_back(new Grep(linhasAntes, linhasDepois, ignoreCase, invertMatch, haystack, needle, algoritmo_temp));

	}

	//Sistema de Threads

	/*
	 * Para cada ficheiro que se tenha de pesquisar vai exitir um thread
	 * Todas estas vao estar a correr em paralelo e quando acabarem é imprimido o output na consola
	 */

	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	vector<thread*> thr;

	if (sysinfo.dwNumberOfProcessors > 1) {
		for (unsigned int i = 0; i < search.size(); i++) {
			thr.push_back(new thread(runGrep, search[i], files[i]));
		}

		for (unsigned int i = 0; i < thr.size(); i++) {
			thr[i]->join();

			cor(BLACK, RED);
			cout << "Pesquisa Ficheiro: " << files[i] << endl;
			cout<<"Tempo Pesquisa:" << search[i]->getTempoPesquisa()<<endl;
			cor(BLACK,WHITE);
			cout << search[i]->getResult()<<endl<<endl;
		}
	}

	cin.get();
	return 0;
}

/**
 *Exeutar o algoritmo de pesquisa de strings e formata o output consolante as flags
 */
void runGrep(Grep * grep) {

	grep->run();

	grep->formatResults();

}

