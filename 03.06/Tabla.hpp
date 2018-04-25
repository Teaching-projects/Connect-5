#ifndef TABLA_HPP
#define TABLA_HPP

class Tabla {
	int size;
	int **tabla;
	bool xkov;

public:
	Tabla(int size);
	bool isXkov() const;
	void setXkov();
	int **getTabla();
	void setTabla(int **ujtabla);
	void resizeRight();
	void resizeLeft();
	int getSize();
};

#endif // !TABLA_HPP

