

#include "ucak.h"
#include <string>
#include <iostream>

using namespace std;

string ucak::getkalkis(){
	return kalkis;
}

string ucak::getvaris(){
	return varis;
}

int ucak::getucusno(){
	return ucusno;
}

int ucak::getkoltuksayisi(){
	return koltuksayisi;
}

void ucak::setkalkis(string k){
	kalkis=k;
}

void ucak::setvaris(string v){
	varis=v;
}

void ucak::setucusno(int n){
	ucusno=n;
}

void ucak::setkoltuksayisi(int s){
	koltuksayisi=s;
}

ucak::ucak(int n, string k, string v, int s){
	setkalkis(k);
	setvaris(v);
	setucusno(n);
	setkoltuksayisi(s);
}

void ucak::yaz(){
	cout<<getucusno()<<" ; "<<getkalkis()<<" ; "<<getvaris()<<" ; "<<getkoltuksayisi()<<" "<<endl;
}


