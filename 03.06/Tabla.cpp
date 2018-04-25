#include "Tabla.hpp"

Tabla::Tabla(int size) :size(size) {
	tabla = new int*[size];
	for (int i = 0; i < size; i++) {
		tabla[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tabla[i][j] = 0;
		}
	}
	xkov = true;
}

int** Tabla::getTabla(){
	return tabla;
}

void Tabla::setTabla(int **ujtabla) {
	tabla = ujtabla;
}


bool Tabla::isXkov() const {
	return xkov;
}
void Tabla::setXkov() {
	if (isXkov()) xkov = false;
	else xkov = true;
}

void Tabla::resizeRight() {
	size++;
	int **ujtabla = new int*[size];
	for (int i = 0; i < size; i++) {
		ujtabla[i] = new int[size];
		for (int j = 0; j < size; j++) {
			ujtabla[i][j] = 0;
		}
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			ujtabla[i][j] = tabla[i][j];
		}
		delete(tabla[i]);
	}
	delete tabla;
	tabla=ujtabla;
}
void Tabla::resizeLeft() {
	size++;
	int **ujtabla = new int*[size];
	for (int i = 0; i < size; i++) {
		ujtabla[i] = new int[size];
		for (int j = 0; j < size; j++) {
			ujtabla[i][j] = 0;
		}
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			ujtabla[i + 1][j + 1] = tabla[i][j];
		}
		delete(tabla[i]);
	}
	delete tabla;
	tabla=ujtabla;
}

int Tabla::getSize() {
	return size;
}