#include <iostream>

class Matrix {
public:
    Matrix();
    void read(std::istream& in);
    Matrix mat_add(const Matrix& other) const;
    void write(std::ostream& out) const;

private:
    static const int N = 10;
    int value[N][N];
};

Matrix::Matrix() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            value[i][j] = 0;
        }
    }
}

void Matrix::read(std::istream& in) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            in >> value[i][j];
        }
    }
}

Matrix Matrix::mat_add(const Matrix& other) const {
    Matrix result;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result.value[i][j] = value[i][j] + other.value[i][j];
        }
    }
    return result;
}

void Matrix::write(std::ostream& out) const {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j > 0) {
                out << ' ';
            }
            out << value[i][j];
        }
        out << '\n';
    }
}

int main() {
    Matrix a;
    Matrix b;
    a.read(std::cin);
    b.read(std::cin);
    Matrix sum = a.mat_add(b);
    sum.write(std::cout);
    return 0;
}
