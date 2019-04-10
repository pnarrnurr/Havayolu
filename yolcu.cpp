

#include <string>
#include <iostream>
#include "yolcu.h"
#include "ucak.h"
using namespace std;


string yolcu::getad(){
	return ad;
}

string yolcu::getsoyad(){
	return soyad;
}

int yolcu::getucusno(){
	return ucusno;
}

int yolcu::getkoltukno(){
	return koltukno;
}

void yolcu::setucusno(int n){
	ucusno=n;
}


void yolcu::setad(string a){
	ad=a;
}

void yolcu::setsoyad(string s){
	soyad=s;
}

void yolcu::setkoltukno(int t){
	koltukno=t;
}

yolcu::yolcu(int n, string a, string s, int t){
	setucusno(n);
	setsoyad(a);
	setad(s);
	setkoltukno(t);

}

void yolcu::goster(){
	cout<<getucusno()<<" ; " <<getsoyad()<<" ; "<<getad()<< " ; " << getkoltukno() <<endl;
}

