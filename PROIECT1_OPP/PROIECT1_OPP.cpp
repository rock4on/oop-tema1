// PROIECT1_OPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

class nod
{
private:
	int valoare;
	nod* next;
	friend class lista;

public:
	// functie care ne arata daca avem acelasi nod // folosita in operatorul egal din clasa lista
	bool is_egal(nod &n)
	{
		if (this == &n) return true;
		else
		{
			return false;
		}
	}


};


class lista{
private:
	int nr_elemente;
	nod *start;
public:
	//Constructor
	lista()
	{
		nr_elemente = 0;
		start = new nod;
		start->next = new nod;
	}
	//constructor copiere
	lista(lista &m)
	{
		nr_elemente = 0;
		start = new nod;
		start->next = new nod;
		if (start->is_egal(*m.start)) return;
		for (int i = 0; i < nr_elemente; i++)
		{
			rm(i);
		}
		start->valoare = m.start->valoare;
		int i = 0;
		while (m.nr_elemente > i)
		{
			//cout << "2";
			adauga_cap(m.el(i));
			i++;
		}
	}






	//Destructor 
	~lista()
	{
		nod* current = start;
		nod* next;
		int p = 0;
		while (p < nr_elemente) {
			next = current->next;
			delete current;
			current = next;
			p++;
			
		}
		nr_elemente = 0;
	}

	lista &operator=(lista m)
	{	
		if (start->is_egal(*m.start)) return *this;
		for (int i = nr_elemente + 1; i >-1; i--)
		{	
			rm(i);
		}

		start->valoare = m.start->valoare;
		int i = 0;
		while (m.nr_elemente > i)
		{
			adauga_cap(m.el(i));
			i++;
		}

		return *this;
	}




	friend istream &operator >>(istream &in,lista &l)
	{
		for (int i = l.nr_elemente; i > -1; i--)
		{
			l.rm(i);
		}
		cout << "nr elemente:";
		int  n;
		in >> n;
		int nr;
		while (n)
		{
			in >> nr;
			l.adauga_cap(nr);


			n--;
		}
		return in;
	}

	friend ostream &operator <<(ostream &out, lista &l)
	{
		int n = l.nr_elemente;
		int i=-1;
		while (i<n-1)
		{
			i++;
			out << l.el(i)<<" ";
		}
		cout << endl;
		return out;
	}


	void swap(nod *n1, nod *n2)
	{
		int aux = n1->valoare;
		n1->valoare = n2->valoare;
		n2->valoare = aux;
	}



	lista &operator +(lista &l)
	{
		lista aux=*this;
		aux.add(l);
		return *new lista(aux);
		// am folosit new deoarece aux se sterge pana este pasat in constructorul de copiere daca returnez aux simplu

	}

	
	lista &operator *(lista &l)
	{
		lista aux = *this;
		lista aux2 = l;

		aux.to_multime(); aux2.to_multime();
		aux.add(aux2);
		int i = 0, j = 0;
		while (i < aux.nr_elemente)
		{
			j = i + 1; int nr = 0;
			while (j < aux.nr_elemente)
			{
				if (aux.el(i) == aux.el(j)) nr++;
				j++;
			}
			if (nr < 1) aux.rm(i);
			else i++;

		}


		return *new lista(aux);
	}


	lista &operator -(lista &l)
	{
		lista aux = *this;
		lista aux2 = l;

		aux.to_multime();
		aux2.to_multime();
		aux.add(aux2);
		int i = 0, j = 0;
		while (i < aux.nr_elemente)
		{
			j = i + 1;
			while (j < aux.nr_elemente)
			{
				if (aux.el(i) == aux.el(j)) {
					aux.rm(j); aux.rm(i); j = i + 1;
				}
				else j++;
			}
			i++;
		}
		aux = aux * *this;
		return *new lista(aux);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Adaugare element in capatul listei
	void adauga_cap(int);
	//accesare element
	int el(int);

	//stergere element
	void rm(int);

	//functie afisare
	void afisare();
	

	//functie de sortare
	void sortare();
	
	//functie de adunare a 2 vectori
	void add(lista &l2);
	

	//transformare listei in multime
	void to_multime();





};







//////////////////////////////////////////////////////////////////////////////////


void lista::to_multime()
{
	sortare();
	bool unsorted = true;
	nod * cur;
	int p;
	while (unsorted) {
		unsorted = false;
		cur = start;
		p = 1;
		while (p < nr_elemente) {
			nod *next = cur->next;
			if (next->valoare == cur->valoare) {
				rm(p);
				unsorted = true;
			}
			p++;
			cur = cur->next;
		}
	}
}






//functie de adunare a 2 vectori;
void lista::add(lista&l2)
{
	nod* curent = start;
	for (int i = 1; i < nr_elemente; i++)
	{
		curent = curent->next;
	}
	int s = 0;
	nod* c2 = l2.start;
	if (nr_elemente == 0)
	{
		s = 1;
		curent->valoare = c2->valoare;
		c2 = c2->next;
	}
	for (int i = s; i < l2.nr_elemente; i++)
	{
		curent->next = new nod;
		curent->next->valoare = c2->valoare;
		curent = curent->next;
		c2 = c2->next;
	}
	curent->next = new nod;
	nr_elemente += l2.nr_elemente;
}









//functia de sortare , metoda bulelor
void lista::sortare()
{
	bool unsorted = true;
	nod * cur;
	int p;
	while (unsorted) {
		unsorted = false;
		cur = start;
		p = 1;
		while (p < nr_elemente) {
			nod *next = cur->next;
			if (next->valoare < cur->valoare) {
				swap(cur, next);
				unsorted = true;
			}
			p++;
			cur = cur->next;
		}
	}
}




//Adaugare element in capatul listei
void lista::adauga_cap(int el) {
	nod *poz = start;
	for (int i = 0; i < nr_elemente; i++)
	{
		poz = poz->next;
	}
	poz->next = new nod;
	poz->valoare = el;
	nr_elemente++;
}

//accesare element de pe pozitia p
int lista::el(int p)
{
	if (p > nr_elemente - 1) return -9999;
	nod *poz = start;
	for (int i = 0; i < p; i++)
	{
		poz = poz->next;
	}
	return poz->valoare;

}

//stergere element din lista
void lista::rm(int p)
{
	if (p > nr_elemente) return;
	if (nr_elemente == 0) return;
	if (p == 0)
	{
		nod *poz = start;
		poz = poz->next;
		start = poz;
		nr_elemente--;
		return;
	}

	nod *poz = start;
	for (int i = 0; i < p - 1; i++)
	{
		poz = poz->next;
	}

	nod *par = poz->next;
	poz->next = par->next;
	delete par;

	nr_elemente--;
}

//afisare
void lista::afisare()
{
	nod *poz = start;
	for (int i = 0; i < nr_elemente; i++)
	{
		cout << poz->valoare << " ";
		poz = poz->next;

	}
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class multime {
private:
	lista l;
public:
	multime(){
		
	}
	~multime()
	{

	}
	multime(multime &m)
	{
		l = m.l;
	}

	multime(lista &li)
	{
		l = li;
	}


	friend istream &operator >>(istream &in, multime &m)
	{
		in >> m.l;
		return in;
	}

	friend ostream &operator <<(ostream &out, multime &m)
	{
		out << m.l;
		return out;
	}

	multime &operator +(multime &m)
	{
		lista li = m.l + l;
		li.to_multime();
		return *new multime(li);
	}

	multime &operator - (multime &m)
	{
		return *new multime(l - m.l);
	}

	multime &operator *(multime &m)
	{
		return *new multime(l*m.l);
	}

	static multime* citire_n(int n)
	{
		multime *m = new multime[n];

		for (int i = 0; i < n; i++) cin >> n;

		return m;
	}

	static multime afisare_n(multime *m, int n)
	{
		for (int i = 0; i < n; i++) cout << m[i];
	}

};







int main()
{
	multime m, n;
	cin >> m >> n;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout <<" m + n : "<< m + n;
	cout <<" m * n : "<< m * n;
	cout <<" m - n : "<< m - n;
	cout <<" n - m : "<< n - m;
	
}

