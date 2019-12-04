#include "pch.h"
#include <iostream>
#include <string>
#include<string.h>
#include<fstream>
using namespace std;

#define LH 1
#define EH 0
#define RH -1
struct av {
	string a;
	string b;
};
typedef av AV;
struct AVLNode
{
	AV data;
	int CSCB;
	AVLNode *pLeft;
	AVLNode *pRight;
};

typedef AVLNode * AVLTree;

void CreateAVLTree(AVLTree &Root)
{
	Root = NULL;
}

AVLNode *CreateAVLNode(AV x)
{
	AVLNode *p = new AVLNode;

	if (!p) exit(1);

	p->CSCB = EH;
	p->data = x;
	p->pLeft = NULL;
	p->pRight = NULL;

	return p;
}

//cay con trai lech trai
void Rotate_Left_Left(AVLTree &Root)
{
	AVLNode *p;

	p = Root->pLeft;
	Root->pLeft = p->pRight;
	p->pRight = Root;

	switch (p->CSCB)
	{
	case LH:
		Root->CSCB = EH;
		p->CSCB = EH;
		break;
	case EH:
		p->CSCB = RH;
		Root->CSCB = LH;
		break;
	}

	Root = p;
}

//cay con phai lech phai
void Rotate_Right_Right(AVLTree &Root)
{
	AVLNode *p;

	p = Root->pRight;
	Root->pRight = p->pLeft;
	p->pLeft = Root;

	switch (p->CSCB)
	{
	case EH:
		Root->CSCB = RH;
		p->CSCB = EH;
		break;
	case RH:
		p->CSCB = EH;
		Root->CSCB = EH;
		break;
	}

	Root = p;
}

//cay con phai lech trai
void Rotate_Right_Left(AVLTree &Root)
{
	AVLNode *p1, *p2;

	p1 = Root->pRight;
	p2 = p1->pLeft;
	Root->pRight = p2->pLeft;
	p1->pLeft = p2->pRight;
	p2->pLeft = Root;
	p2->pRight = p1;

	switch (p2->CSCB)
	{
	case LH:
		Root->CSCB = EH;
		p1->CSCB = RH;
		break;
	case EH:
		Root->CSCB = EH;
		p1->CSCB = EH;
		break;
	case RH:
		Root->CSCB = LH;
		p1->CSCB = EH;
		break;
	}

	p2->CSCB = EH;
	Root = p2;
}

//cay con trai lech phai
void Rotate_Left_Right(AVLTree &Root)
{
	AVLNode *p1, *p2;

	p1 = Root->pLeft;
	p2 = p1->pRight;
	Root->pLeft = p2->pRight;
	p1->pRight = p2->pLeft;
	p2->pRight = Root;
	p2->pLeft = p1;

	switch (p2->CSCB)
	{
	case LH:
		p1->CSCB = EH;
		Root->CSCB = RH;
		break;
	case EH:
		Root->CSCB = EH;
		p1->CSCB = EH;
		break;
	case RH:
		Root->CSCB = EH;
		p1->CSCB = LH;
		break;
	}

	p2->CSCB = EH;
	Root = p2;
}

//Can bang khi cay lech trai
int BalanceLeft(AVLTree &Root)
{
	AVLNode *p;

	p = Root->pLeft;

	switch (p->CSCB)
	{
	case LH:
		Rotate_Left_Left(Root);
		return 2;
	case EH:
		Rotate_Left_Left(Root);
		return 1;
	case RH:
		Rotate_Left_Right(Root);
		return 2;
	}
}

//can bang cay lech phai
int BalanceRight(AVLTree &Root)
{
	AVLNode *p;

	p = Root->pRight;

	switch (p->CSCB)
	{
	case RH:
		Rotate_Right_Right(Root);
		return 2;
	case EH:
		Rotate_Right_Right(Root);
		return 1;
	case LH:
		Rotate_Right_Left(Root);
		return 2;
	}
}

//Chen 1 node vao cay AVL
int InsertNode(AVLTree &Root, AV x)
{
	int Res;
	if (Root)
	{
		//gia tri da co trong cay
		if (strcmp(Root->data.a.c_str(), x.a.c_str()) == 0) return 0;

		//Root->x > x
		//chen vao ben trai
		if (strcmp(Root->data.a.c_str(), x.a.c_str()) > 0)
		{
			Res = InsertNode(Root->pLeft, x);
			if (Res < 2) return Res;

			//Res >= 2
			switch (Root->CSCB)
			{
			case RH:
				Root->CSCB = EH;
				return 1;
			case EH:
				Root->CSCB = LH;
				return 2;
			case LH:
				BalanceLeft(Root);
				return 1;
			}
		}

		//Root->x < x
		//chen vao ben phai
		else
		{
			Res = InsertNode(Root->pRight, x);

			if (Res < 2) return Res;

			//Res >= 2
			switch (Root->CSCB)
			{
			case LH:
				Root->CSCB = EH;
				return 1;
			case EH:
				Root->CSCB = RH;
				return 2;
			case RH:
				BalanceRight(Root);
				return 1;
			}
		}
	}

	Root = CreateAVLNode(x);
	return 2;
}





//Duyet theo muc
void Level(AVLTree Root)
{
	if (Root != NULL) {
		cout << "\t\t" <<Root->data.a <<" : " <<Root->data.b<< " -- "<< Root->CSCB << endl;
		Level(Root->pLeft);
		Level(Root->pRight);
	}
}

void Input(AVLTree &Root)
{
	int x;
	string c = "exit";
	do
	{ 
		AV x;
		cout << "bam exit de thoat ";
		cout << "nhap tieng anh : ";
		getline(cin, x.a);
		cout << "\nnhap tieng viet : ";
		getline(cin, x.b);
		if (strcmp(x.a.c_str() , c.c_str()) == 0) break;
		InsertNode(Root, x);
	} while (1);
}

void search(AVLTree t,string key) {
	if (t != NULL)
	{
		if (strcmp(t->data.a.c_str(), key.c_str()) == 0) {
			cout << t->data.a << " : " << t->data.b << endl;
		}
		else 	if (strcmp(t->data.b.c_str(), key.c_str()) == 0) {
			cout << t->data.a << " : " << t->data.b << endl;
		}
		search(t->pLeft, key);
		search(t->pRight, key);
	}
}

void Doc_File_A_V(ifstream & filein, AV & a) {
	getline(filein, a.a, ':');
	getline(filein, a.b);
}
void DeleteNode(AVLTree &t) {



}
void Menu(AVLTree &t) {
	while (true) {
		system("cls");
		int luoichon;
		std::cout << "======MENU======\n";
		std::cout << "\t1.them bang ban phim\n";
		std::cout << "\t2.them bang ban file\n";
		std::cout << "\t3. duyet cay\n";
		std::cout << "\t4. Tim kiem \n";
		std::cout << "\t0. Thoat \n";
		std::cout << "======END======\n";
		std::cout << "nhap luoi chon : ";
		cin >> luoichon;
		if (luoichon == 1) {
			AV d;
			string mover;
			std::fflush(stdin);
			getline(cin, mover);
			std::fflush(stdin);
			std::wcout << "\n nhap tu bang tieng anh : ";
			getline(cin, d.a);
			std::fflush(stdin);
			std::wcout << "\n Nhap tu bang tieng viet : ";
			getline(cin, d.b);
			InsertNode(t, d);
		}
		else if (luoichon == 2) {
			ifstream filein;
			filein.open("anh_viet.txt", ios_base::in | ios_base::out);
			while (filein.eof() == false) {
				AV sv;
				Doc_File_A_V(filein, sv);
				InsertNode(t, sv);
			}
			cout << " doc file thanh cong :v \n";
			system("pause");
			filein.close();
		}
		else if (luoichon == 3) {
			Level(t);
			system("pause");
		}
		else if (luoichon == 4) {
			string key,mover;
			getline(cin, mover);
			std::cout << "\n Nhap tu can tim kiem : "; 
			getline(cin, key);
			search(t, key);
			system("pause");
		}
		else
			break;
	}

}
int main()
{
	AVLTree Root;
	CreateAVLTree(Root);
	Menu(Root);
	system("pause");
}