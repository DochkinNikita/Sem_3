#include <iostream>
#include <math.h>

using namespace std;
const double Pi = 3.1415926535;

class Figure
{
public:

    virtual double Calc_Square()
    {
        return 0;
    }
    virtual Figure* GetType()
    {
        return new Figure;
    }

};

class Circle : public Figure
{
private:
    double r;
public:
    Circle();
    Circle(double);
    virtual double Calc_Square();
    virtual Figure* GetType()
    {
        return new Circle(r);
    }

};

class Triangle : public Figure
{
private:
    double a, b, c;
    bool Check(double, double, double);
public:
    Triangle();
    Triangle(double, double, double);
    virtual double Calc_Square();
    virtual Figure* GetType()
    {
        return new Triangle(a, b, c);
    }
};

class FourPointedStar : public Figure
{
private:
    double d; // Длинна основания луча
public:
    FourPointedStar();
    FourPointedStar(double);
    virtual double Calc_Square();
    virtual Figure* GetType()
    {
        return new FourPointedStar(d);
    }

};

class Cylinder
{
private:
    Figure* f;
    double h;

public:
    Cylinder(double, Figure*);
    double CalcValume();

};

Circle::Circle()
{
    cout << "\n- Конструктор Circle -";
    r = 4;
}

Circle::Circle(double new_r)
{
    if (new_r > 0)
    {
        cout << "\n- Конструктор Circle() -";
        r = new_r;
    }
    else
    {
        cout << "\n Неверное значение радиуса! ";
        return;
    }
}

double Circle::Calc_Square()
{
    return r * r * Pi;
}


bool Triangle::Check(double a, double b, double c)
{
    if (c < a + b && a < b + c && b < c + a)
    {
        return true;
    }
    else
    {
        cout << "\n\n * Значения треугольника неверные! ";
        return false;
    }
}

Triangle::Triangle()
{
    cout << "\n- Конструктор Tringle -";
    a = 3;
    b = 4;
    c = 5;
}

Triangle::Triangle(double new_a, double new_b, double new_c)
{
    if (Check(new_a, new_b, new_c))
    {
        cout << "\n- Конструктор Tringle() -";
        a = new_a;
        b = new_b;
        c = new_c;
    }

    else
        return;

}

double Triangle::Calc_Square()
{
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));  // Формула Герона
}

Cylinder::Cylinder(double new_h, Figure* new_f)
{
    h = new_h;
    f = new_f->GetType();
}

double Cylinder::CalcValume()
{
    return h * (f->Calc_Square());
}


FourPointedStar::FourPointedStar()
{
    cout << "\n- Конструктор FourPointedStar -";
    d = 5;

}

FourPointedStar::FourPointedStar(double new_d)
{
    if (new_d > 0)
    {
        cout << "\n- Конструктор FourPointedStar() -";
        d = new_d;
    }
    else
    {
        cout << "\n Неверное значение длинны основания луча! ";
        return;
    }
}

double FourPointedStar::Calc_Square()
{
    double AreaPentagon = d*d;  // Площадь внутреннего квадрата
    double AreaTriangle = (d * d * sqrt(3)) / 4;
    return AreaPentagon + AreaTriangle * 4;

}

short int MENU();

int main()
{
    system("chcp 1251"); system("cls");
    double S;
    Figure* f = nullptr;
    Cylinder* c;
    int v;
    v = MENU();
    if (v == 1)
    {
        double a, b, c;
        cout << "\n\n Введите стороны треугольника\n";
        cin >> a >> b >> c;
        f = new Triangle(a, b, c);

    }
    if (v == 2)
    {
        double r;
        cout << "\n\n Введите радиус круга\n";
        cin >> r;
        f = new Circle(r);
    }
    if (v == 3)
    {
        double d;
        cout << "\n\n Введите длинну основания луча\n";
        cin >> d;
        f = new FourPointedStar(d);
    }

    cout << "\n Введите высоту фигуры: ";
    cin >> v;
    c = new Cylinder(v, f);
    delete f;
    f = new Circle(1); // Для примера, изменяю данные первичного указателя.
    S = c->CalcValume();
    cout << endl << "\n Объем фигуры = " << S << endl;
    return 0;
}


short int MENU()
{
    short int v;
    cout << "Выбирете фигуру"
        << "\n\n 1.) Треугольник"
        << "\n 2.) Круг"
        << "\n 3.) Четырехконечная звезда"
        << "\n\n #>";
    cin >> v;
    return v;
}

