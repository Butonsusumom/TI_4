#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <vector>
#include <fstream>
using namespace std;


vector <int> PervRoots;

#define ID_BUTTON_CIPHER 1001
#define ID_BUTTON_DECIPHER 1002
#define ID_BUTTON_FILEOPEN 1003
#define ID_EDIT_FILE 1005
#define ID_EDIT_P 1006
#define ID_EDIT_Q 1007
#define ID_EDIT_D 1008
#define ID_EDIT_E 1009
#define ID_EDIT_ROOTS 10010
#define ID_EDIT_EXIT 10011
#define ID_EDIT_RES 10029
#define ID_LABEL_P 10012
#define ID_LABEL_Q 10013
#define ID_LABEL_D 10014
#define ID_LABEL_E 10015
#define ID_LABEL_H1 10019
#define ID_LABEL_M1 10020
#define ID_LABEL_H2 10024
#define ID_LABEL_M2 10025
#define ID_LABEL_M3 10026
#define ID_LABEL_S 10021
#define ID_LABEL_ROOTS 10016
#define ID_LABEL_EXIT 10017
#define ID_LABEL_FILE 10018
#define ID_LABEL_FI 10022
#define ID_LABEL_R 10023
#define ID_LABEL_S2 10027
#define ID_LABEL_RES 10028

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

char szClassName[] = "CG_WAPI_Template";
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;
HWND hEdit4;
HWND hEdit5;
HWND hEdit6;
HWND hEdit7;
HWND hWndButton;
HWND hWndButton1;
HWND hWndButton2;
HWND hWndButton3;
HWND TitleLabel1;
HWND TitleLabel2;
HWND TitleLabel3;
HWND TitleLabel4;
HWND TitleLabel5;
HWND TitleLabel6;
HWND TitleLabel7;
HWND TitleLabel8;
HWND TitleLabel9;
HWND TitleLabel10;
HWND TitleLabel11;
HWND TitleLabel12;
HWND TitleLabel13;
HWND TitleLabel14;
HWND TitleLabel15;
HWND TitleLabel16;
HWND TitleLabel17;




//=================================================BEGIN ALGORITHMTH=======================================================

//Find array of simple diveders
vector <long long> find_prime_factors(long long n) {
	vector <long long> Arr;
	for (long long i = 2; i*i <= n; ++i) {
		if (n % i == 0) {
			Arr.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	}
	if (n != 1) {
		Arr.push_back(n);
	}
	return Arr;
}
// Help Fast exponentiation modulo
long long mul(long long a, long long b, long long m) {
	if (b == 1)
		return a;
	if (b % 2 == 0) {
		long long t = mul(a, b / 2, m);
		return (2 * t) % m;
	}
	return (mul(a, b - 1, m) + a) % m;
}

//Fast exponentiation modulo
long long pows(long long a, long long b, long long m) {
	if (b == 0)
		return 1;
	if (b % 2 == 0) {
		long long t = pows(a, b / 2, m);
		return mul(t, t, m) % m;
	}
	return (mul(pows(a, b - 1, m), a, m)) % m;
}

//Find NOD, Evklid algorithm
long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a%b);
}

//check if number is simple
bool ferma(long long x) {
	if (x == 2)
		return true;
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		long long a = (rand() % (x - 2)) + 2;
		if (gcd(a, x) != 1)
			return false;
		if (pows(a, x - 1, x) != 1)
			return false;
	}
	return true;
}
//Euclid Algorithm
long long euclidAlg(long long a, long long b) {
	long long d0, d1, d2, y0, y1, y2, q;
	d0 = a;
	d1 = b;
	y0 = 0;
	y1 = 1;
	while (d1 > 1) {

	q = d0 / d1;
	d2 = d0 % d1;
	y2 = y0 - q * y1;
	d0 = d1;
	d1 = d2;
	y0 = y1;
	y1 = y2;
	}
	return(y1);
}

//Fast a^z mod n
int Fastexp(long long a, long long z, long long n) {
	long long a1 = a;
	long long z1 = z;
	long long x = 1;
	while (z1 != 0) {
		while (z1 % 2 == 0) {
			z1 /= 2;
			a1 = (a1*a1) % n;
		}
		z1--;
		x = (x*a1) % n;
	}
	return x;
}

vector<int> FindRoots(long long p) {
	vector <long long> simple = find_prime_factors(p - 1);
	vector<int> res;
	string s;
	bool flag;
	for (long long g = 2; g < p; g++) {
		flag = true;
		for (int j = 0; j < simple.size(); j++) {
			if (Fastexp(g, (p - 1) / simple[j], p) == 1) flag = false;
			else {
				if ((j == simple.size() - 1) && (flag)) { res.push_back(g); s = s + to_string(g) + "\r\n"; }
			}
		}
	}
	string s1;
	char ex[10000];
	s1 = "There are " + to_string(res.size()) + " roots\r\n"+s;
//	SetWindowText(hEdit6, s1.c_str());

	return res;
}

long long CheckP(string s) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}

		if (ferma(res)) return res;
	
	return 0;
}





long long CheckK(string s, long long p) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (res > 1) {
		if (res < p - 1) {
			if (gcd(res, p) == 1) return res;
		}
	}
	return 0;
}

bool isCoprime(long long a, long long b) {
	for (long long gcd = a; ; gcd = b, b = a % b, a = gcd)
		if (!b) return gcd == 1;
}

long long CheckD(string s, long long f) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (res > 1) {
		if (res < f) {
			if (isCoprime(f, res))
			return res;
		}
	}
	return 0;
}

long long CheckE(string s, long long f) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (res > 1) {
		if (res < f) {
			if (isCoprime(f,res))
			return res;
		}
	}
	return 0;
}

long long CheckG(string s) {
	long long res = atoll(s.c_str());
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9'))
			return 0;
	}
	if (find(PervRoots.begin(), PervRoots.end(), res) != PervRoots.end()) {
		return res;
	}
	return 0;
}


 
int Hash1(char name[500], char cipher_namename[500],long long r) {
	int H = 100;
	string s;
	unsigned char byte;

	ifstream in(name, ios::binary);
	if (!in) {
		MessageBox(NULL, "Invalid file input", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		return -1;
	}
	else {
		ofstream out(cipher_namename, ios::binary);
		s = "H0=" + to_string(H);
		SetWindowText(TitleLabel5, s.c_str());
		in.read((char*)&byte, sizeof(unsigned char));
		
		while (!in.eof()) {
			out.write((char*)&byte, sizeof(unsigned char));
			H = ((H + byte)*(H + byte)) % r;
			in.read((char*)&byte, sizeof(unsigned char));
		}
		out.close();
		in.close();
		return H;
	}
}

int Hash2(char name[500], long long r) {
	int H = 100;
	string s;
	unsigned char byte;

	ifstream in(name, ios::binary);
	if (!in) {
		MessageBox(NULL, "Invalid file input", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		return -1;
	}
	else {

		s = "H0=" + to_string(H);
		SetWindowText(TitleLabel13, s.c_str());
		in.read((char*)&byte, sizeof(unsigned char));

		while ((!in.eof())&&(byte !='|')) {
			H = ((H + byte)*(H + byte)) % r;
			in.read((char*)&byte, sizeof(unsigned char));
		}

		in.close();
		return H;
	}
}


void Check(long long r, long long e) {
	long long m,ms,S,c;
	string s, ex;
	char name[500];
	GetWindowText(hEdit1, name, 500);
	m = Hash2(name, r);
	if (m != -1) {
		s = "m=" + to_string(m);
		SetWindowText(TitleLabel15, s.c_str());

		


		ifstream in(name);
		s = "";
		while (getline(in, ex)) {
			s = s + ex;
		}
		in.close();

		S = 0;
		bool flag=true;
		char ch[1];
		int i = s.rfind("| ");
		if (i == string::npos)  S = 0;
		else {
			i += 2;
			while ((i != s.size())&&(flag)) {
				if ((s[i] != '0') && (s[i] != '1') && (s[i] != '2') && (s[i] != '3') && (s[i] != '4') && (s[i] != '5') && (s[i] != '6') && (s[i] != '7') && (s[i] != '8') && (s[i] != '9')) {
					flag = false;
					S = 0;
				}
					else {
						ch[0] = s[i];
						S = S * 10 + atoi(ch);
						i++;
					}
				
			}
			
		}

		s = "S=" + to_string(S);
		SetWindowText(TitleLabel16, s.c_str());

		ms = Fastexp(S,e,r);
		s = "m'=" + to_string(ms);
		SetWindowText(TitleLabel14, s.c_str());

		if (m == ms) {
			SetWindowText(hEdit7, "YES");
		}
		else
			SetWindowText(hEdit7, "NO");

	}
}


void Sign(long long r, long long fi, long long d) {
	long long H,e,S;
	char name[500];
	char cipher_namename[500];
	string s,ex;
	GetWindowText(hEdit1, name, 500); 

	strcpy_s(cipher_namename, name);
	strcat_s(cipher_namename, "(cipher).txt");
	
	H = Hash1(name, cipher_namename,r);
	if (H != -1) {
		s = "m=" + to_string(H);
		SetWindowText(TitleLabel7, s.c_str());

		e = euclidAlg(fi,d);
		if (e < 0)  e = e + fi;
		s = "e=" + to_string(e);
		SetWindowText(TitleLabel4, s.c_str());

		S = Fastexp(H,d,r);
		s = "S=" + to_string(S);
		SetWindowText(TitleLabel8, s.c_str());

		ofstream out(cipher_namename,ios_base::app);
		out << "| " << S ;
		out.close();

		ifstream file(cipher_namename);
		s = "";
		while (getline(file, ex)) {
			s = s + ex;
		}
		file.close();

		SetWindowText(hEdit6, s.c_str());

	}
}
//=======================================END ALGORITHM===========================================================


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wc;

	// Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 127, 80)); 
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	// Регистрируем класс окна
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Не могу зарегистрировать класс окна!", "Ошибка", MB_OK);
		return 0;
	}

	// Создаем основное окно приложения
	hWnd = CreateWindow(
		szClassName,                // Имя класса                   
		"RSA Digital Signature", // Текст заголовка
		WS_OVERLAPPEDWINDOW,        // Стиль окна                                             
		50, 50,                   // Позиция левого верхнего угла  
		800, 800,                  // Ширина и высота окна    
		(HWND)NULL,                // Указатель на родительское окно NULL    
		(HMENU)NULL,               // Используется меню класса окна              
		(HINSTANCE)hInstance,       // Указатель на текущее приложение
		NULL);                  // Передается в качестве lParam в событие WM_CREATE

	if (!hWnd)
	{
		MessageBox(NULL, "Не удается создать главное окно!", "Ошибка", MB_OK);
		return 0;
	}


	// Показываем наше окно
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	PAINTSTRUCT  ps;
	HDC          hdc;
	//SetTimer(hWnd, 2, 100, NULL);
	// Выполняем цикл обработки сообщений до закрытия приложения
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);

	}
	return (lpMsg.wParam);
}

LRESULT onCreateWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	/*
	 hWndButton = CreateWindow("button", "Click Me", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
		30, 30, 100, 20, hWnd, (HMENU)ID_BUTTON_FILEOPEN, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	UpdateWindow(hWndButton);*/


	 hWndButton2 = CreateWindow("button", "Signature", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		140, 380, 100, 40, hWnd, (HMENU)ID_BUTTON_CIPHER, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	UpdateWindow(hWndButton2);

	 hWndButton3 = CreateWindow("button", "Check", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		140, 620, 100, 40, hWnd, (HMENU)ID_BUTTON_DECIPHER, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
	UpdateWindow(hWndButton3);


	 hEdit1 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		130, 30, 620, 20, hWnd, (HMENU)ID_EDIT_FILE, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit2 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 100, 210, 20, hWnd, (HMENU)ID_EDIT_P, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit3 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 160, 210, 20, hWnd, (HMENU)ID_EDIT_Q, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit4 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 280, 210, 20, hWnd, (HMENU)ID_EDIT_D, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit5 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		30, 520, 210, 20, hWnd, (HMENU)ID_EDIT_E, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit6 = CreateWindow("Edit", NULL, WS_VSCROLL | WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE,
		 280, 280, 470, 140, hWnd, (HMENU)ID_EDIT_EXIT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 hEdit7 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		 330, 490, 40, 20, hWnd, (HMENU)ID_EDIT_RES, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);





	

	 TitleLabel1 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, enter  simple number p", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 70, 210, 20, hWnd, (HMENU)ID_LABEL_P, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel2 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, enter  simple number q", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 130, 210, 20, hWnd, (HMENU)ID_LABEL_Q, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel3 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, enter close exponent d", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 250, 210, 20, hWnd, (HMENU)ID_LABEL_D, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel4 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "e=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 310, 100, 20, hWnd, (HMENU)ID_LABEL_E, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel5 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "H0=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 340, 100, 20, hWnd, (HMENU)ID_LABEL_H1, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel7 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "m=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 370, 100, 20, hWnd, (HMENU)ID_LABEL_M1, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel8 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "S=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 400, 100, 20, hWnd, (HMENU)ID_LABEL_S, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);


	 TitleLabel9 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Exit file", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		280, 250, 80, 20, hWnd, (HMENU)ID_LABEL_EXIT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel10 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "r=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 280, 70, 300, 20, hWnd, (HMENU)ID_LABEL_FI, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel11 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "fi(r)=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 280, 100, 300, 20, hWnd, (HMENU)ID_LABEL_R, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);


	 TitleLabel12 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Please, enter open exponent e", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 490, 210, 20, hWnd, (HMENU)ID_LABEL_E, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);




	 TitleLabel13 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "H0=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 550, 100, 20, hWnd, (HMENU)ID_LABEL_H2, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel14 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "m'=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 580, 100, 20, hWnd, (HMENU)ID_LABEL_M3 , (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel15 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "m=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		30, 610, 100, 20, hWnd, (HMENU)ID_LABEL_M2, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel16 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "S=", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 640, 100, 20, hWnd, (HMENU)ID_LABEL_S2, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

	 TitleLabel17 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Result:", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 280, 490, 50, 20, hWnd, (HMENU)ID_LABEL_RES, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);





	 TitleLabel6 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "   File Name", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
		 30, 30, 100, 20, hWnd, (HMENU)ID_LABEL_FILE, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);




	return 0;
}

LRESULT onButtonCipher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	long long p, k, x, g, y,q,fi,r,d;
	char buff[200];
	string s,str;
	GetWindowText(hEdit2,buff,200);
	s = buff;
	p = CheckP(s);
	if (p != 0) {
		GetWindowText(hEdit3, buff, 200);
		s = buff;
		q = CheckP(s);
		r = q * p;
		if ((q != 0)&&(r>100) && (q != p)) {
			GetWindowText(hEdit4, buff, 200);
			s = buff;
			fi =(p-1)*(q-1) ;
				str = "r=" + to_string(r);
				SetWindowText(TitleLabel11, str.c_str());
				str = "fi(r)=" + to_string(fi);
				SetWindowText(TitleLabel10, str.c_str());
			d = CheckD(s, fi);
			if (d != 0) {
				Sign(r,fi,d);
			}
			else {
				MessageBox(NULL, "Invalid input d", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
				SetWindowText(hEdit4, "");
			}
		}
		else {
			MessageBox(NULL, "Invalid input q", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
			SetWindowText(hEdit3, "");
		}
	}
	else {
		MessageBox(NULL,"Invalid input p"," Try again", MB_OK| MB_DEFBUTTON1 |MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		SetWindowText(hEdit2, "");
	}
	return 0;
}

LRESULT onButtonDeCipher(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	long long p, k, x, g, y,q,r,e,fi,d;
	char buff[200];
	string s,str;
	GetWindowText(hEdit2, buff, 200);
	s = buff;
	p = CheckP(s);
	if (p != 0) {
		GetWindowText(hEdit3, buff, 200);
		s = buff;
		q = CheckP(s);
		r = p * q;
		if ((q != 0) && (r > 100)&& (q!=p)) {
			GetWindowText(hEdit5, buff, 200);
			s = buff;
			fi = (p - 1)*(q - 1);
			str = "r=" + to_string(r);
			SetWindowText(TitleLabel11, str.c_str());
			str = "fi(r)=" + to_string(fi);
			SetWindowText(TitleLabel10, str.c_str());
			e = CheckE(s, fi);
			if (e != 0) {
				Check(r,e);
			}
			else {
				MessageBox(NULL, "Invalid input e", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
				SetWindowText(hEdit4, "");
			}
		}
	    else {
			MessageBox(NULL, "Invalid input q", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
			SetWindowText(hEdit4, "");
		}
	}
	else {
		MessageBox(NULL, "Invalid input p", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		SetWindowText(hEdit2, "");
	}
	return 0;
}


LRESULT onButtonOpenFile(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
/*	OPENFILENAME ofn;       // common dialog box structure
	TCHAR szFile[260];       // if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = _countof(szFile);
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = _T("c:/work");
	ofn.Flags = OFN_EX_NOPLACESBAR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		// use ofn.z 
	}*/
	//SetWin
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		return onCreateWindow(hWnd, message, wParam, lParam);

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUTTON_FILEOPEN:
			return onButtonOpenFile(hWnd, message, wParam, lParam);

		case ID_BUTTON_CIPHER:
			return onButtonCipher(hWnd, message, wParam, lParam);

		case ID_BUTTON_DECIPHER:
			return onButtonDeCipher(hWnd, message, wParam, lParam);
		}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam); //освобождаем очередь приложения от нераспознаных
}

