

#ifndef YOLCU_H_
#define YOLCU_H_

#include <string>
#include "ucak.h"

class yolcu {
private:
	int ucusno, koltukno;
	string ad, soyad;

public:
	void setucusno(int n);
	void setad(string a);
	void setsoyad(string s);
	void setkoltukno(int t);

	int getucusno();
	string getad();
	string getsoyad();
	int getkoltukno();

	yolcu(int n, string a, string s, int t);
	void goster();
};




#endif /* YOLCU_H_ */
