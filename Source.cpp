#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };

string strSpec[] = { "����'�����i �����", "I����������", "���������� �� ������i��", "�i���� �� i����������", "������� ��������" };

struct Student
{
    string surnamed;
    int kurs;
    Spec spec;
    int physics;
    int math;
    union {
        int progr;
        int numb;
        int ped;
    };
};

void Create(char* FileName, Student* s, int amSt) {
    ofstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file '" << FileName << "'" << endl;
        exit(1);
    }
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "��i�����: ";
        cin >> s[i].surnamed;
        cout << "����: ";
        cin >> s[i].kurs;
        cout << "����i����i��� (0 - ����'�����i �����, 1 - I����������, 2 - ���������� �� ������i��, 3 - �i���� �� i����������, 4 - ������� ��������) ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "��i��� � �i����: ";
        cin >> s[i].physics;
        cout << "��i��� � ����������: ";
        cin >> s[i].math;
        if (s[i].spec == 0) {
            cout << "��i��� � �������������: ";
            cin >> s[i].progr;
        }
        else if (s[i].spec == 1) {
            cout << "��i��� � ��������� �����i�: ";
            cin >> s[i].numb;
        }
        else {
            cout << "��i��� � �������i��: ";
            cin >> s[i].ped;
        }
    }
}

void Print(char* FileName, Student* s, int amSt)
{
    ifstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;
    cout << "| � |    ��i�����   | ���� |      ����i����i���     | �i���� | ���������� | ������������� | �������i ������ | �������i�� |"
        << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < amSt; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << s[i].surnamed
            << "| " << setw(5) << right << s[i].kurs
            << "| " << setw(23) << left << strSpec[s[i].spec]
            << "| " << setw(7) << s[i].physics
            << "| " << setw(11) << right << s[i].math;
        if (s[i].spec == 0)
        {
            cout << "| " << setw(14) << right << s[i].progr
                << "| " << setw(16) << right << " "
                << "| " << setw(11) << right << " " << "| ";
        }
        else if (s[i].spec == 1)
        {
            cout << "| " << setw(14) << right << " "
                << "| " << setw(16) << right << s[i].numb
                << "| " << setw(11) << right << " " << "| ";
        }
        else
        {
            cout << "| " << setw(14) << right << " "
                << "| " << setw(16) << right << " "
                << "| " << setw(11) << right << s[i].ped << "| ";
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;
}

void Sort(char* FileName, Student* p, const int N)
{
    ifstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) 
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].spec > p[i1 + 1].spec || p[i1].spec == p[i1 + 1].spec && p[i1].math > p[i1 + 1].math)
                ||
                (p[i1].spec == p[i1 + 1].spec || p[i1].math == p[i1 + 1].math &&
                    p[i1].surnamed > p[i1 + 1].surnamed))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* indexSort(char* FileName, Student* s, int N)
{
    ifstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    int* P = new int[N];

    for (int i = 0; i < N; i++)
    {
        P[i] = i;
    }
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = P[i];
        for (j = i - 1; j >= 0 && ((s[P[j]].spec > s[value].spec)
            ||
            (s[P[j]].spec == s[value].spec &&
                s[P[j]].math > s[value].math)
            ||
            (s[P[j]].spec == s[value].spec || s[P[j]].math == s[value].math &&
                s[P[j]].surnamed > s[value].surnamed));
            j--)
        {
            P[j + 1] = P[j];
        }
        P[j + 1] = value;
    }
    return P;
}

int binSearch(char* FileName, Student* p, const int N, const Spec spec, const string prizv, const int math)
{
    ifstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].surnamed == prizv && p[m].spec == spec && p[m].math == math)
            return m;
        if ((p[m].spec < spec)
            ||
            (p[m].spec == spec &&
                p[m].math < math)
            ||
            p[m].spec == spec ||
            p[m].math < math &&
            p[m].surnamed < prizv)
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int amSt;
    int ispec;
    Spec spec;
    string lastName;
    int math;
    int found;
    cout << "ʳ������ ��������: ";
    cin >> amSt;
    Student* s = new Student[amSt];

    cin.get(); cin.sync();
    char FileName[81];
    cout << "������ ��'� �����:"; cin.getline(FileName, sizeof(FileName));

    int menuItem;
    do
    {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ��������� " << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� ����� " << endl;
        cout << " [4] - �������� ������������� �� ���� ����� " << endl;
        cout << " [5] - ������� ����� ��� ����������, �� ��������� ������� " << endl;
        cout << " �� �������� ������������ �������� �� �������� ������������ �� �������� �������� �����." << endl;
        cout << " [0] - ����� �� ���������� �������� " << endl;
        cout << "������ �������: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            Create(FileName, s, amSt);
            break;
        case 2:
            Print(FileName, s, amSt);
            break;
        case 3:
            Sort(FileName, s, amSt);
            break;
        case 4:
            indexSort(FileName, s, amSt);
            break;
        case 5:
            cout << "������ ����� ������:" << endl;
            cout << " �������: "; cin >> lastName;
            cout << endl;
            cout << " �������������: "; cin >> ispec;
            spec = (Spec)ispec;
            cout << endl;
            cout << " ������ � ����������: "; cin >> math;
            cout << endl;
            cin.get();
            cin.sync();

            if ((found = binSearch(FileName, s, amSt, spec, lastName, math)) != -1)
                cout << "�������� �������� � ������� " << found + 1 << endl;
            else
                cout << "�������� �������� �� ��������" << endl;
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);
    return 0;
}