// Supermarket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
//global variable declaration
int k = 7, r = 0, flag = 0;
COORD coord = { 0, 0 };

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm, dd, yy;
};

ofstream fout;
ifstream fin;

class item
{
    int itemno;
    char name[25];
    date d;
public:
    void add()
    {
        cout << "\n\n\tShomare item: ";
        cin >> itemno;
        cout << "\n\n\tName item: ";
        cin >> name;
        //gets(name);
        cout << "\n\n\tTarikhe tolid(dd-mm-yy): ";
        cin >> d.mm >> d.dd >> d.yy;
    }
    void show()
    {
        cout << "\n\tshomare item: ";
        cout << itemno;
        cout << "\n\n\tName item: ";
        cout << name;
        cout << "\n\n\ttarikh : ";
        cout << d.mm << "-" << d.dd << "-" << d.yy;
    }
    void report()
    {
        gotoxy(3, k);
        cout << itemno;
        gotoxy(13, k);
        puts(name);
    }
    int retno()
    {
        return(itemno);

    }

};

class amount : public item
{
    float price, qty, tax, gross, dis, netamt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;

void amount::add()
{
    item::add();
    cout << "\n\n\tgheimat: ";
    cin >> price;
    cout << "\n\n\tkeifiat: ";
    cin >> qty;
    cout << "\n\n\tdarsade maliat: ";
    cin >> tax;
    cout << "\n\n\tdarsade takhfif: ";
    cin >> dis;
    calculate();
    fout.write((char*)&amt, sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross = price + (price * (tax / 100));
    netamt = qty * (gross - (gross * (dis / 100)));
}
void amount::show()
{
    fin.open("itemstore.dat", ios::binary);
    fin.read((char*)&amt, sizeof(amt));
    item::show();
    cout << "\n\n\tgheimat: ";
    cout << netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23, k);
    cout << price;
    gotoxy(33, k);
    cout << qty;
    gotoxy(44, k);
    cout << tax;
    gotoxy(52, k);
    cout << dis;
    gotoxy(64, k);
    cout << netamt;
    k = k + 1;
    if (k == 50)
    {
        gotoxy(25, 50);
        cout << "LOTFAN YEK KELID BEZANID...";
        _getch();
        k = 7;
        system("cls");
        gotoxy(30, 3);
        cout << " MOSHAKHASAT ITEM ";
        gotoxy(3, 5);
        cout << "SHOMARE";
        gotoxy(13, 5);
        cout << "NAME";
        gotoxy(23, 5);
        cout << "GHEYMAT";
        gotoxy(33, 5);
        cout << "KEIFIAT";
        gotoxy(44, 5);
        cout << "MALIAT";
        gotoxy(52, 5);
        cout << "DEDUCTION";
        gotoxy(64, 5);
        cout << "GHEIMAT";
    }
}

void amount::pay()
{
    show();
    cout << "\n\n\n\t\t*********************************************";
    cout << "\n\t\t                 JOZIAT                  ";
    cout << "\n\t\t*********************************************";
    cout << "\n\n\t\tGHEYMAT                     :" << price;
    cout << "\n\n\t\tKEIFIAT                  :" << qty;
    cout << "\n\t\tMALIAT              :" << tax;
    cout << "\n\t\tTAKHFIF         :" << dis;
    cout << "\n\n\n\t\tBAHA              :Rs." << netamt;
    cout << "\n\t\t*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    fstream tmp("temp.dat", ios::binary | ios::out);
menu:
    system("cls");
    gotoxy(25, 2);
    cout << "Super Market Billing ";
    gotoxy(25, 3);
    cout << "===========================\n\n";
    cout << "\n\t\t1.gozareshe kharid\n\n";
    cout << "\t\t2.ezafe/hezf/Edite Item\n\n";
    cout << "\t\t3.joziat item\n\n";
    cout << "\t\t4.Exit\n\n";
    cout << "\t\tLotfan tanzim marboote ra entekhab konid: ";
    int ch, ff;
    float gtotal;
    cin >> ch;
    switch (ch)
    {
    case 1:
    ss:
        system("cls");
        gotoxy(25, 2);
        cout << "gozareshe kharid";
        gotoxy(25, 3);
        cout << "================\n\n";
        cout << "\n\t\t1.hame item ha\n\n";
        cout << "\t\t2.bargash be menu asli\n\n";
        cout << "\t\tLotfan tanzim marboote ra entekhab konid: ";
        int cho;
        cin >> cho;
        if (cho == 1)
        {
            system("cls");
            gotoxy(30, 3);
            cout << " gozareshe kharid ";
            gotoxy(3, 5);
            cout << "shmare item";
            gotoxy(13, 5);
            cout << "NAME";
            gotoxy(23, 5);
            cout << "GHEYMAT";
            gotoxy(33, 5);
            cout << "KEIFIAT";
            gotoxy(44, 5);
            cout << "MALIAT %";
            gotoxy(52, 5);
            cout << "TAKHFIF %";
            gotoxy(64, 5);
            cout << "BAHA";
            fin.open("itemstore.dat", ios::binary);
            if (!fin)
            {
                cout << "\n\nfile peida nashod...";
                goto menu;
            }
            fin.seekg(0);
            gtotal = 0;
            while (!fin.eof())
            {
                fin.read((char*)&amt, sizeof(amt));
                if (!fin.eof())
                {
                    amt.report();
                    gtotal += amt.retnetamt();
                    ff = 0;
                }
                if (ff != 0) gtotal = 0;
            }
            gotoxy(17, k);
            cout << "\n\n\n\t\t\tmajmoo=" << gtotal;
            _getch();
            fin.close();
        }
        if (cho == 2)
        {
            goto menu;
        }
        goto ss;
    case 2:
    db:
        system("cls");
        gotoxy(25, 2);
        cout << "Bill Editor";
        gotoxy(25, 3);
        cout << "=================\n\n";
        cout << "\n\t\t1.ezafe kardane joziate item\n\n";
        cout << "\t\t2.Edite joziate item\n\n";
        cout << "\t\t3.hazfe joziate item\n\n";
        cout << "\t\t4.bargash be menu asli ";
        int apc;
        cin >> apc;
        switch (apc)
        {
        case 1:
            fout.open("itemstore.dat", ios::binary | ios::app);
            amt.add();
            cout << "\n\t\tItem ezafe shod!";
            _getch();
            goto db;

        case 2:
            int ino;
            flag = 0;
            cout << "\n\n\tshomare item ra braie edit vared konid :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);
            fout.open("itemstore.dat", ios::binary | ios::app);
            if (!fin)
            {
                cout << "\n\nFile peida nashod...";
                goto menu;
            }
            fin.seekg(0);
            r = 0;
            while (!fin.eof())
            {
                fin.read((char*)&amt, sizeof(amt));
                if (!fin.eof())
                {
                    int x = amt.item::retno();
                    if (x == ino)
                    {
                        flag = 1;
                        fout.seekp(r * sizeof(amt));
                        system("cls");
                        cout << "\n\t\tjoziate item\n";
                        amt.show();
                        cout << "\n\n\t\tjoziat item ra vared konid\n";
                        amt.add();
                        cout << "\n\t\tjoziat item edit shod";
                    }
                }
                r++;
            }
            if (flag == 0)
            {
                cout << "\n\t\titem peida nashod!";
                _getch();
                goto db;
            }
            fin.close();
            _getch();
            goto db;

        case 3:
            flag = 0;
            cout << "\n\n\tname item ra baraye hazf vared konid :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);
            if (!fin)
            {
                cout << "\n\nFile peida nashod...";
                goto menu;
            }
            //fstream tmp("temp.dat",ios::binary|ios::out);
            fin.seekg(0);
            while (fin.read((char*)&amt, sizeof(amt)))
            {
                int x = amt.item::retno();
                if (x != ino)
                    tmp.write((char*)&amt, sizeof(amt));
                else
                {
                    flag = 1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat", ios::trunc | ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat", ios::binary | ios::in);
            if (!tmp)
            {
                cout << "Error in File";
                goto db;
            }
            while (tmp.read((char*)&amt, sizeof(amt)))
                fout.write((char*)&amt, sizeof(amt));
            tmp.close();
            fout.close();
            if (flag == 1)
                cout << "\n\t\tItem ba movafaghiat hazf shod";
            else if (flag == 0)
                cout << "\n\t\tItem vojood nadarad";
            _getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout << "\n\n\t\tentekhabe eshtebah!!";
            _getch();
            goto db;
        }
    case 3:
        system("cls");
        flag = 0;
        int ino;
        cout << "\n\n\t\tshomare item ra vared konid :";
        cin >> ino;
        fin.open("itemstore.dat", ios::binary);
        if (!fin)
        {
            cout << "\n\nFile peida nashod...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while (fin.read((char*)&amt, sizeof(amt)))
        {
            int x = amt.item::retno();
            if (x == ino)
            {
                amt.pay();
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            cout << "\n\t\tItem vojood nadarad....!";
        _getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20, 20);
        cout << "AYA MIKHAHID KHAREJ SHAVID (Y/N)?";
        char yn;
        cin >> yn;
        if ((yn == 'Y') || (yn == 'y'))
        {
            gotoxy(12, 20);
            system("cls");
            cout << "************************** THANKS **************************************";
            _getch();
            exit(0);
        }
        else if ((yn == 'N') || (yn == 'n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout << "\n\n\t\tentekhabe eshtebah....!";
        _getch();
        goto menu;
    }
    return 0;
}