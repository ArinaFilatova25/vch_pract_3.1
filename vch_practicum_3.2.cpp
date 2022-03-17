// vch_practicum_3.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <locale>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;


double f_1(double x) { return exp(1.5*x); }
double f(double x) { return x*x/(1+x*x); }
double f_p1(double x) { return 2*x/((1+x*x)*(1+x*x)); }
double f_p2(double x) {
    return (2 - 6 * x * x) / ((1 + x * x) * (1 + x * x) * (1 + x * x));
}

 vector<double> centr_razn_proizv(int m,double h, vector <pair<double, double>> tab_podgot) {
    vector <double> f_p;

    f_p.push_back((- 3 * tab_podgot[0].second + 4 * tab_podgot[1].second - tab_podgot[2].second) / (2 * h));
   
    for (int i = 1; i < (m - 1); i++) {
        f_p.push_back((tab_podgot[i+1].second - tab_podgot[i-1].second) / (2 * h));
    }

    f_p.push_back((3 * tab_podgot[m-1].second -4 * tab_podgot[m-2].second + tab_podgot[m-3].second) / (2 * h));

    return f_p;
 }

 vector<double> mod_centr_razn_proizv(int m, double h, vector <pair<double, double>> tab_podgot) {
     vector <double> f_p;

     f_p.push_back((-25 * tab_podgot[0].second + 48 * tab_podgot[1].second - 36*tab_podgot[2].second +16*tab_podgot[3].second-3*tab_podgot[4].second) / (12 * h));
     f_p.push_back((-25 * tab_podgot[1].second + 48 * tab_podgot[2].second - 36 * tab_podgot[3].second + 16 * tab_podgot[4].second - 3 * tab_podgot[5].second) / (12 * h));
     
     for (int i = 2; i < (m - 2); i++) {
         f_p.push_back((tab_podgot[i-2].second - 8*tab_podgot[i - 1].second+ 8 * tab_podgot[i +1].second - tab_podgot[i +2].second) / (12 * h));
     }

     f_p.push_back((-25 * tab_podgot[m-2].second + 48 * tab_podgot[m-3].second - 36 * tab_podgot[m-4].second + 16 * tab_podgot[m-5].second - 3 * tab_podgot[m-6].second) / (-12 * h));
     f_p.push_back((-25 * tab_podgot[m-1].second + 48 * tab_podgot[m-2].second - 36 * tab_podgot[m-3].second + 16 * tab_podgot[m-4].second - 3 * tab_podgot[m-5].second) / (-12 * h));

     return f_p;
 }
 
 vector<double> second_proizv(int m, double h, vector <pair<double, double>> tab_podgot) {
    vector <double> f_p;

    for (int i = 1; i < (m-1); i++) {
        f_p.push_back((tab_podgot[i + 1].second -2*tab_podgot[i].second +tab_podgot[i - 1].second) / (h*h));
    }
   
    return f_p;
 }

 void menu() {
     cout << "Выбирете действие:" << endl;
     cout << "1) Введите новые параметры" << endl;
     cout << "2) Завершить программу" << endl;
 }

int main()
{
    std::cout << std::setprecision(14) << std::fixed;
    setlocale(LC_ALL, "Rus");
    int m,k=1;
    double a, h;

    while (k == 1) {

        cout << "Введите число значений в таблице" << endl;
        cin >> m;
        cout << "Введите начальную точку" << endl;
        cin >> a;
        cout << "Введите шаг h>0" << endl;
        cin >> h;
        vector <pair<double, double>> tab_podgot;
        vector <pair<double, double>> tab_podgot_1;
        vector <double> f_proizv_1, f_1_proizv_1, f_mod_proizv_1, f_1_mod_proizv_1, f_proizv_2, f_1_proizv_2;


        for (int i = 0; i < m; i++) {
            tab_podgot.push_back(make_pair(a + h * i, f(a + h * i)));
        }
        cout << "Таблица для функции x^2/(1+x^2)" << endl;
        for (int i = 0; i < m; i++) {
            cout << "x" << i << "=" << tab_podgot[i].first << "    f(x" << i << ")=" << tab_podgot[i].second << endl;
        }

        cout << endl;
        for (int i = 0; i < m; i++) {
            tab_podgot_1.push_back(make_pair(a + h * i, f_1(a + h * i)));
        }
        cout << "Таблица для функции e^1.5x" << endl;
        for (int i = 0; i < m; i++) {
            cout << "x" << i << "=" << tab_podgot_1[i].first << "    f(x" << i << ")=" << tab_podgot_1[i].second << endl;
        }
        cout << endl;

        f_proizv_1 = centr_razn_proizv(m, h, tab_podgot);
        f_1_proizv_1 = centr_razn_proizv(m, h, tab_podgot_1);
        f_mod_proizv_1 = mod_centr_razn_proizv(m, h, tab_podgot);
        f_1_mod_proizv_1 = mod_centr_razn_proizv(m, h, tab_podgot_1);
        f_proizv_2 = second_proizv(m, h, tab_podgot);
        f_1_proizv_2 = second_proizv(m, h, tab_podgot_1);

        cout << "Решение задачи численного дифференцирования для функции x^2/(1+x^2)" << endl;
        for (int i = 0; i < m; i++) {
            cout << "x" << i << "=" << tab_podgot[i].first << "    f(x" << i << ")=" << tab_podgot[i].second <<
                "    f'(x" << i << ")чд=" << f_proizv_1[i] << "    |f'(x" << i << ")т-f'(x" << i << ")чд|=" << fabs(f_p1(a+h*i) - f_proizv_1[i]) <<
                "    f'(x" << i << ")чд_mod=" << f_mod_proizv_1[i] << "    |f'(x" << i << ")т-f'(x" << i << ")чд_mod|=" << fabs(f_p1(a+h*i) - f_mod_proizv_1[i]) << endl;
        }
        cout << endl;
        cout << "Вторая производная" << endl;
        for (int i = 0; i < (m - 2); i++) {
            cout << "x" << i + 1 << "=" << tab_podgot[i + 1].first << "    f(x" << i + 1 << ")=" << tab_podgot[i + 1].second <<
                "    f''(x" << i + 1 << ")чд=" << f_proizv_2[i] << "    |f''(x" << i+1 << ")т-f''(x" << i+1 << ")чд|=" << fabs(f_p2(a + h * (i + 1)) - f_proizv_2[i]) << endl;

        }
        cout << endl;
        cout << "Решение задачи численного дифференцирования для функции e^1.5x" << endl;
        for (int i = 0; i < m; i++) {
            cout << "x" << i << "=" << tab_podgot_1[i].first << "    f(x" << i << ")=" << tab_podgot_1[i].second <<
                "    f'(x" << i << ")чд=" << f_1_proizv_1[i] << "    |f'(x" << i << ")т-f'(x" << i << ")чд|=" << fabs(1.5*f_1(a+h*i) - f_1_proizv_1[i]) <<
                "    f'(x" << i << ")чд_mod=" << f_1_mod_proizv_1[i] << "    |f'(x" << i << ")т-f'(x" << i << ")чд_mod|=" << fabs(1.5*f_1(a+h*i) - f_1_mod_proizv_1[i]) <<endl;
        }
        cout << endl;
        cout << "Вторая производная" << endl;
        for (int i = 0; i < (m - 2); i++) {
            cout << "x" << i+1 << "=" << tab_podgot_1[i+1].first << "    f(x" << i+1 << ")=" << tab_podgot_1[i+1].second <<
                "    f''(x" << i+1 << ")чд=" << f_1_proizv_2[i] << "    |f''(x" << i+1 << ")т-f''(x" << i+1 << ")чд|=" << fabs(1.5 * 1.5 * f_1(a+h*(i+1)) - f_1_proizv_2[i]) << endl;
        }
        cout << endl;
        menu();
        k = 0;
        cin >> k;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
