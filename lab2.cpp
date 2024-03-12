#include <iostream>
using namespace std;

class Vector {
    double* p = nullptr; // Указатель на массив, задающий вектор
    int n = 0; // Размерность вектора (число элементов)
    friend const Vector operator+(const double* left, const Vector& right); // Объявляю функцию сложения как дружественную
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
// Перегрузка оператора присваивания
const Vector operator+(const double* left, const Vector& right) {
    Vector result(right.n); // Создаем новый объект вектора
    for (int i = 0; i < right.n; i++) result.p[i] = right.p[i]+left[i]; // Заполняем новый вектор суммами значений из двух объектов
    return result; // Возвращаем новый вектор
}

int main() {
    double m1[] = {5.2, 1, 3, 4};
    Vector V1(m1, 4);
    double* num = new double[5]{1.8,2,3,4};
    Vector V2 = num + V1;
    V2.print();
    return 0;
}
