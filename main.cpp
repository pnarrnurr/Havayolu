

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "ucak.h"
#include "yolcu.h"
using namespace std;


void ucusekle(vector <ucak> *s);
void ucussil(vector <ucak> *s);
void ucuslistele(vector <ucak> *s);
void ucusyaz(vector <ucak> *s);
int ucusoku(vector <ucak> *s);


int menu0();
int menu1();
int menu2();


void yolcuekle(vector <yolcu> *p, vector <ucak> *s);
void yolcusil(vector <yolcu> *p);
void yolculistele(vector <yolcu> *p);
int yolcuoku(vector <yolcu> *p);


void liste(vector <yolcu> *p, vector <ucak> *s);
void listeyaz(vector <yolcu> *p, vector <ucak> *s);


int main() {
	vector <ucak> ucus;
	vector <yolcu> yolcu;

	int ucusislem, yolcuislem, islem;

	if(ucusoku(&ucus)==1)
		cout<<"Ucus Sayisi : "<< ucus.size()  <<endl;
	else
		cout<<"Ucuslar Dosyasi Henuz Olusmamamis."<<endl;

	if(yolcuoku(&yolcu)==1)
		cout<<"Yolcu Sayisi : "<< yolcu.size()  <<endl;
	else
		cout<<"Yolcular Dosyasi henuz Olusmamamis."<<endl;

	while (islem!=4){
		islem = menu0();
		switch(islem){

		case 1:	while(ucusislem != 4){
				ucusislem=menu1();
				cin >> ucusislem;
				switch(ucusislem){
				case 1: ucusekle(&ucus); break;
				case 2: ucussil(&ucus); break;
				case 3: ucuslistele(&ucus); break;
				case 4: break; //ucusyaz(&ucus); break;
				default: cout<<"Gecersiz Secim"<<endl; break;
				}
		}; break;

		case 2:	while (yolcuislem != 4) {
				yolcuislem=menu2();
				cin>> yolcuislem;
				switch(yolcuislem){
				case 1: yolcuekle(&yolcu, &ucus); break;
				case 2: yolcusil(&yolcu); break;
				case 3: yolculistele(&yolcu); break;
				case 4: break; //yolcuyaz(&yolcu); break;
				default: cout <<"Gecersiz Secim"<< endl;
				}
		}; break;

		case 3: liste(&yolcu, &ucus); 
				listeyaz(&yolcu, &ucus);
			break;

		case 4:
			break; listeyaz(&yolcu, &ucus);
		}
	}
}


void ucusekle(vector <ucak> *s){	//Ucus ekleme fonksiyonu
	vector <ucak> ucus;
	string kalkis, varis;
	int ucusno, koltuksayisi;

	int girilenucus=0;
	int bulundu=0;

	cout<<"Ucus Numarasi : ";
	cin>>girilenucus;

	for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){

		if (girilenucus == it->getucusno()) {
			bulundu = 1;
			break;
		}
	}

	if(bulundu){
		cout<<girilenucus<<" numarali ucusunuz zaten bulunmaktadir."<<endl;
	}

	else{
		ucusno = girilenucus;

		cout<<"Nereden : ";
		cin>>kalkis;
		cout<<"Nereye : ";
		cin>>varis;
		cout<<"Koltuk Sayisi : ";
		cin>>koltuksayisi;

		ucak u(ucusno, kalkis, varis, koltuksayisi);
		s->push_back(u);
		ucusyaz(s);

		cout<<"Yeni ucus eklendi. Ucus sayisi : "<< s->size()<< endl;
	}
}


void ucuslistele(vector <ucak> *s){ 	// Ucuslari listeleme fonksiyonu

	cout << endl << "-----UCUS LISTESI-----" << endl << endl;
	cout<<"UCUS NO ; KALKIS ; VARIS ; KOLTUK SAYISI"<<endl;
	for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){
		it->yaz();
	}
	cout << endl;
}


void ucussil(vector <ucak> *s) { 	//Ucus silme fonksiyonu

	int silinecekucus = 0;
	int elemanno = 0;
	int bulundu = 0;

	cout << "Silmek istediginiz ucusun numarasi : ";
	cin >> silinecekucus;

	for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){
		if (silinecekucus == it->getucusno()){
			bulundu = 1;
			break;
		}
		elemanno++;
	}

	if (bulundu) {

		s->erase(s->begin()+elemanno);
		ofstream dosya1;
		dosya1.open("ucuslar.txt");

		for(vector <ucak>::iterator it = s->begin(); it != s->end(); it++){
			if (it == s->begin())
				dosya1 << it->getucusno()<<";"<<it->getkalkis()<<";"<<it->getvaris()<<";"<<it->getkoltuksayisi();
			else
				dosya1 << endl << it->getucusno()<<";"<<it->getkalkis()<<";"<<it->getvaris()<<";"<<it->getkoltuksayisi();
		}
		cout << "Ucus silindi." << endl;
		dosya1.close();
	}
	else
		cout << "Ucus bulunamadi." << endl;
}


void ucusyaz(vector <ucak> *s){ 	// Ucuslari dosyaya yazma fonksiyonu

	if (s->size() == 0){
		cerr<<"Dosya yazilacak kayit yok"<<endl;
		exit(1);
	}

	ofstream dosya1("ucuslar.txt", ios::out);
	if(!dosya1){
		cerr<<"Dosya acilamadi!"<<endl;
		exit(1);
	}

	for(vector <ucak>::iterator it = s->begin(); it != s->end(); it++){
		if (it == s->begin())
			dosya1 << it->getucusno()<<";"<<it->getkalkis()<<";"<<it->getvaris()<<";"<<it->getkoltuksayisi();
		else
			dosya1 << endl << it->getucusno()<<";"<<it->getkalkis()<<";"<<it->getvaris()<<";"<<it->getkoltuksayisi();
	}

	cout<<"Dosyaya "<<s->size()<<" adet ucus yazildi."<<endl;
	dosya1.close();
}


int ucusoku(vector <ucak> *s){ 	// Ucuslari okuma fonksiyonu

	string kalkis, varis;
	int koltuksayisi, ucusno;
	ifstream dosya1("ucuslar.txt", ios::in);

	if(!dosya1){
		cerr<<"Dosya acilamadi!"<<endl;
		return -1;
	}
	string alan;
	for (string satir; getline(dosya1, satir);){

		istringstream ss( satir );

		getline(ss, alan, ';');
		ucusno = atoi(alan.c_str());

		getline(ss, alan, ';');
		kalkis = alan;

		getline(ss, alan, ';');
		varis = alan;

		getline(ss, alan, ';');
		koltuksayisi = atoi(alan.c_str());

		ucak u(ucusno, kalkis, varis, koltuksayisi);
		s->push_back(u);
	}

	dosya1.close();
	return 1;
}


int menu0(){ 	//Ana menu fonksiyonu
	int sec;
	cout<<"1- Ucus Islemleri"<<endl;
	cout<<"2- Yolcu Islemleri"<<endl;
	cout<<"3- Listeleme Islemleri"<<endl;
	cout<<"4- Bitir"<<endl;
	cout<<"Secim yap : ";
	cin>>sec;
	return sec;
}


int menu1(){ 	// Ucus islemleri fonksiyonu
	int sec;
	cout<<"1- Ucus ekle"<<endl;
	cout<<"2- Ucus sil"<<endl;
	cout<<"3- Ucus listele"<<endl;
	cout<<"4- Bitir"<<endl;
	cout<<"Secim yap : ";
	cin>>sec;
	return sec;
}


int menu2(){ 	// Yolcu islemleri menusu fonksiyonu
	int sec;
	cout<<"1- Yolcu ekle"<<endl;
	cout<<"2- Yolcu sil"<<endl;
	cout<<"3- Yolcu listele"<<endl;
	cout<<"4- Bitir"<<endl;
	cout<<"Secim yap : ";
	cin>>sec;
	return sec;
}


void yolcuyaz(vector <yolcu> *p) { 	// Yolculari dosyaya yazma fonksiyonu

	if (p->size() == 0){
		cerr<<"Dosyaya yazilacak kayit yok"<<endl;
		exit(1);
	}

	ofstream dosya1("yolcular.txt", ios::out);
	if(!dosya1){
		cerr<<"Dosya acilamadi!"<<endl;
		exit(1);
	}

	for(vector <yolcu>::iterator it = p->begin(); it != p->end(); it++){
		if (it == p->begin())
			dosya1 << it->getucusno()<<";"<<it->getsoyad()<<";"<<it->getad()<<";"<<it->getkoltukno();
			else
				dosya1 << endl << it->getucusno()<<";"<<it->getsoyad()<<";"<<it->getad()<<";"<<it->getkoltukno();
	}

	cout<<"Dosyaya "<<p->size()<<" adet ucus yazildi."<<endl;
	dosya1.close();
}


int yolcuoku(vector <yolcu> *p){ 	//Yolculari dosyadan okuma fonksiyonu
	string soyad, ad;
	int koltukno, ucusno;

	ifstream dosya1("yolcular.txt", ios::in);

	if(!dosya1){
		cerr<<"Dosya acilamadi!"<<endl;
		return -1;
	}
	string alan;
	for (string satir; getline(dosya1, satir);){

		istringstream ss( satir );

		getline(ss, alan, ';');
		ucusno = atoi(alan.c_str());

		getline(ss, alan, ';');
		soyad = alan;

		getline(ss, alan, ';');
		ad = alan;

		getline(ss, alan, ';');
		koltukno = atoi(alan.c_str());

		yolcu y(ucusno, soyad, ad, koltukno);
		p->push_back(y);
	}

	dosya1.close();
	return 1;
}


void yolcuekle(vector <yolcu> *p, vector <ucak> *s){ 	//Yolcu ekleme fonksiyonu

	string ad, soyad, varisyeri;
	int ucusno, koltukno;
	int bulundu=0;

	vector <int> dolukoltuklar;
	vector <int> boskoltuklar;

	int toplamkoltuk;

	cout<<"Nereye : " ;
	cin>>varisyeri;

	for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){
		if( varisyeri == it->getvaris() ){
			bulundu=1;

			cout << it->getucusno() << ";" << it->getkalkis() << ";" << it->getvaris() << ";"  << it->getkoltuksayisi() << endl;

		}
	}

	if(!bulundu){

		cout<< "Boyle bir ucusunuz bulunmamaktadir."<<endl;
	}

	else{

		cout<<"Ucus No : " ;
		cin>>ucusno;

		for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){
			if (ucusno == it->getucusno())
				toplamkoltuk = it->getkoltuksayisi();
		}


		for(vector <yolcu>::iterator it=p->begin(); it!=p->end(); it++){
			if (ucusno == it->getucusno()){
				dolukoltuklar.push_back(it->getkoltukno());
			}

		}

		for (int i=1; i<=toplamkoltuk; i++){
			bool bulundu = false;

			for(vector <int>::iterator it=dolukoltuklar.begin(); it!=dolukoltuklar.end(); it++) {
				if (i == *it) {
					bulundu = true;
					break;
				}
			}

			if (!bulundu)
				boskoltuklar.push_back(i);

		}

		cout << "Bos koltuklar : " << endl;
		for(vector <int>::iterator it=boskoltuklar.begin(); it!=boskoltuklar.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;

		bool bulundu = false;

		while (1) {
			cout<<"Koltuk No: "; cin >> koltukno;
			for(vector <int>::iterator it=dolukoltuklar.begin(); it!=dolukoltuklar.end(); it++) {
				if (koltukno == *it) {
					bulundu = true;
					cout << "Bu koltuk dolu!" << endl;
				}
			}
			if (!bulundu) break;
		}

		cout<<"Soyad : "; cin >> soyad;
		cout<<"Ad : "; cin >> ad;

		yolcu y(ucusno, ad, soyad, koltukno);
		p->push_back(y);

		yolcuyaz(p);

		cout<<"Yeni yolcu eklendi. Yolcu sayisi : "<<p->size()<<endl;
	}
}


void yolcusil(vector <yolcu> *p) { 	// Yolcu silme fonksiyonu

	int silinecekyolcu = 0;
	int ucusnumarasi= 0;
	int elemanno = 0;
	int bulundu = 0;

	cout << "Silmek Istediginiz Yolcunun Ucus Numarasi : ";
	cin >> ucusnumarasi;

	cout << "Silmek Istediginiz Yolcunun Koltuk Numarasi : ";
	cin >> silinecekyolcu;

	for(vector <yolcu>::iterator it=p->begin(); it!=p->end(); it++){
		if ( ucusnumarasi == it->getucusno() && silinecekyolcu == it->getkoltukno()){
			bulundu = 1;
			break;
		}
		elemanno++;
	}

	if (bulundu) {

		p->erase(p->begin()+elemanno);
		ofstream dosya1;
		dosya1.open("yolcular.txt");

		for(vector <yolcu>::iterator it = p->begin(); it != p->end(); it++){
			if (it == p->begin())
				dosya1 << it->getucusno()<<";"<<it->getsoyad()<<";"<<it->getad()<<";"<<it->getkoltukno();
			else
				dosya1 << endl << it->getucusno()<<";"<<it->getsoyad()<<";"<<it->getad()<<";"<<it->getkoltukno();
		}
		cout << "Yolcu silindi." << endl;
		dosya1.close();
	}
	else
		cout << "Yolcu bulunamadi." << endl;
}


void yolculistele(vector <yolcu> *p){ 	//Yolcular liseleme fonksiyonu

	cout << endl << "-----YOLCU LISTESI-----" << endl << endl;
	cout<<"UCUSž NO ; SOYAD ; AD ; KOLTUK NUMARASI"<<endl;
	for(vector <yolcu>::iterator it=p->begin(); it!=p->end(); it++){
		it->goster();
	}
	cout << endl;
}


void listeyaz(vector <yolcu> *p, vector <ucak> *s){ 	// Gunluk yolcu listesini dosyaya yazma fonksiyonu

	if (s->size() == 0 && s->size() == 0 ){
		cerr<<"Dosyaya yazilacak kayit yok"<<endl;
		exit(1);
	}

	ofstream dosya1("yolculiste.txt", ios::out);
	if(!dosya1){
		cerr<<"Dosya acilamadi!"<<endl;
		exit(1);
	}

	int toplamyolcu;

	vector<int> yolcusayilari;

	for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){

		toplamyolcu = 0;
		for(vector <yolcu>::iterator ity=p->begin(); ity!=p->end(); ity++){

			if (it->getucusno() == ity->getucusno()){

				toplamyolcu++;
			}
		}
		yolcusayilari.push_back(toplamyolcu);
	}

	vector<int>::iterator yolcusay=yolcusayilari.begin();

	for(vector <ucak>::iterator it = s->begin(); it != s->end(); it++){
		if (it == s->begin())
			dosya1 << it->getucusno()<<";"<<it->getkalkis()<<";"<<it->getvaris()<<";"<<it->getkoltuksayisi()<<";"<<*yolcusay;
		else
			dosya1 << endl << it->getucusno()<<";"<<it->getkalkis()<<";"<<it->getvaris()<<";"<<it->getkoltuksayisi()<<";"<<*yolcusay;

		for(vector <yolcu>::iterator ity = p->begin(); ity != p->end(); ity++){
			if (it->getucusno() == ity->getucusno())

			dosya1 << endl << ity->getkoltukno()<<";"<<ity->getsoyad()<<";"<<ity->getad();
		}
		yolcusay++;
		dosya1 << endl<<endl<< "******************************************"<<endl;
	}
	dosya1.close();
}


void liste(vector <yolcu> *p, vector <ucak> *s){ 	// Gunluk yolcu listesini yazma fonksiyonu

	int toplamyolcu;

	vector<int> yolcusayilari;

	for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){

		toplamyolcu = 0;
		for(vector <yolcu>::iterator ity=p->begin(); ity!=p->end(); ity++){
			if (it->getucusno() == ity->getucusno()){
				toplamyolcu++;
			}
		}
		yolcusayilari.push_back(toplamyolcu);
	}
	vector<int>::iterator yolcusay=yolcusayilari.begin();

	cout<< endl<<"-----GUNLUK YOLCU LISTESI-----"<<endl;
	for(vector <ucak>::iterator it=s->begin(); it!=s->end(); it++){
		cout<< it->getucusno()<<";"<<it->getkalkis()<<";"<<it->getvaris()<<";"<<it->getkoltuksayisi()<<";"<<*yolcusay<<endl;
		toplamyolcu = 0;
		for(vector <yolcu>::iterator ity=p->begin(); ity!=p->end(); ity++){

			if (it->getucusno() == ity->getucusno()){
				cout<< ity->getkoltukno()<<";"<<ity->getsoyad()<<";"<<ity->getad()<<endl;
			}
		}
		cout<<endl<<"********************************************"<<endl;
		yolcusay++;
	}
}
