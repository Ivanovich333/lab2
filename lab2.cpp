#include <iostream>
#include <fstream>
using namespace std;

class Vector {
    double* p = nullptr; // Указатель на массив, задающий вектор
    int n = 0; // Размерность вектора (число элементов)
    friend const Vector operator+(const double* left, const Vector& right); // Объявляю оператор сложения дружественной функцией
    friend ostream& operator<<(ostream& os, const Vector& v); // Объявляю оператор вывода дружественной функцией
    friend istream& operator>>(istream& is, Vector& v); // Объявляю оператор ввода дружественной функцией
public:
    // Конструктор, создающий объект вектор на основе обычного одномерного массива размерности n
    Vector(double* p, int n) {
        this->n = n;
        this->p = new double[n]; // Выделение памяти под вектор
        for (int i = 0; i < n; i++) this->p[i] = p[i]; // Копирование значений из переданного массива
    }

    // Конструктор, создающий пустой объект вектор заданной размерности
    Vector(int n) : n(n) {
        p = new double[n]; // Выделение памяти под вектор
    }

    // Конструктор копирования
    Vector(const Vector& V) {
        n = V.n;
        p = new double[n];
        for (int i = 0; i < n; i++)
            p[i] = V.p[i];
    }

    // Конструктор перемещения
    Vector(Vector&& V) {
        std::swap(p, V.p); // Обмен указателями на массивы
        std::swap(n, V.n); // Обмен значениями размерностей
    }

    // Функция печати вектора
    void print() const {
        for (int i = 0; i < n; i++)
            cout << p[i] << " ";
        cout << endl;
    }

    // Перегрузка оператора доступа к элементу вектора по индексу
    double& operator[](int index) {
        return p[index];
    }

    // Перегрузка оператора присваивания с копированием
    Vector& operator =(const Vector& v2) {
        if (this != &v2) {
            n = v2.n;
            if (p != nullptr) delete[] p; // Освобождаем память старого вектора
            p = new double[n]; // Выделяем память для нового вектора
            for (int i = 0; i < n; i++) p[i] = v2.p[i]; // Копируем значения из другого вектора
        }
        return *this; // Возвращаем ссылку на текущий объект
    }

    // Перегрузка оператора присваивания с перемещением
    Vector& operator =(Vector&& v2) {
        if (this != &v2) {
            std::swap(p, v2.p); // Обмен указателями на массивы
            std::swap(n, v2.n); // Обмен значениями размерностей
        }
        return *this; // Возвращаем ссылку на текущий объект
    }
    // Деструктор
    ~Vector() {
        if (p != nullptr) delete[] p; // Освобождаем память, если она была выделена
    }
};
ostream& operator<<(ostream& os, const Vector& v) { // Перегруженный оператор вывода в поток
    for (int i = 0; i < v.n; i++) // Вывод значений вектора через поток вывода
        os << v.p[i] << " ";
    return os;
}

istream& operator>>(istream& is, Vector& v) { // Перегруженный оператор ввода из потока
    for (int i = 0; i < v.n; i++) // Считывание значений вектора из потока ввода
        is >> v.p[i];
    return is;
}
// Перегрузка оператора сложения
const Vector operator+(const double* left, const Vector& right) {
    Vector result(right.n); // Создаем новый объект вектора
    for (int i = 0; i < right.n; i++) result.p[i] = right.p[i]+left[i]; // Заполняем новый вектор суммами значений из двух объектов
    return result; // Возвращаем новый вектор
}

int main() {
    ifstream inputFile("input.txt");
    int size;
    inputFile >> size;
    double* values = new double[size];
    for (int i = 0; i < size; ++i) {
        inputFile >> values[i];
    }
    Vector V1(values, size);
    double* scalar = new double[size];
    for (int i = 0; i < size; ++i) {
        inputFile >> scalar[i];
        cout << scalar[i];
    }
    cout << endl << V1 << endl;
    Vector V2 = scalar + V1;
    cout << V2;
    return 0;
}
