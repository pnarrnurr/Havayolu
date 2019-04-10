

#ifndef UCAK_H_
#define UCAK_H_


#include <string>
using namespace std;


class ucak {
private:
	string kalkis;
	string varis;
	int ucusno;
	int koltuksayisi;
public:
	string getkalkis();
	string getvaris();
	int getucusno();
	int getkoltuksayisi();
	void setkalkis(string k);
	void setvaris(string v);
	void setucusno(int n);
	void setkoltuksayisi(int s);
	ucak(int n=0, string k=" ", string v=" ", int s=0);
	void yaz();
};



#endif /* UCAK_H_ */
