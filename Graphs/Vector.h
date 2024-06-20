#pragma once

template <class T>
class Vector {
private:
    int _size;
    T* v;
    typedef const T* iterate;

public:
    Vector() : _size(0), v(nullptr) {}//konstruktory

    Vector(int size) : _size(size) {
        v = new T[size];
    }

    Vector(int size, const T& initialValue) : _size(size) {
        v = new T[size];
        for (int i = 0; i < size; i++) {
            v[i] = initialValue;
        }
    }

    ~Vector() {
        delete[] v;
    }

    int GetSize() const {
        return this->_size;
    }

    T& operator[](int index) {
        return v[index];
    }

    const T& operator[](int index) const {
        return v[index];
    }

    Vector(const Vector<T>& other) : _size(other._size) {//konstukor kopiujacy
        v = new T[other._size];
        for (int i = 0; i < _size; ++i) {
            v[i] = other.v[i];
        }
    }

    Vector<T>& operator=(const Vector<T>& other) {//przypisanie
        if (this != &other) {
            delete[] v;
            _size = other._size;
            v = new T[_size];
            for (int i = 0; i < _size; ++i) {
                v[i] = other.v[i];
            }
        }
        return *this;
    }

    typename iterate begin() const {
        return v;
    }

    typename iterate end() const {
        return v + this->_size;
    }

    void resize(int newSize) {
        if (newSize > this->_size) {
            T* newV = new T[newSize];
            for (int i = 0; i < _size; ++i) {
                newV[i] = v[i];
            }
            delete[] v;
            v = newV;
        }
        _size = newSize;
    }
};
