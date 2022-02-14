#include <vector>
#include <iostream>

class Polynom {
private:
    std::vector<double> data;

    /*
     * Max degree of polynom could decrease after += and -= operations.
     * To maintain correct max degree we need to remove leading zeros.
     */
    void removeLeadingZeros();
public:
    /*
     * Default empty constructor
     */
    Polynom() {}

    /*
     * Creates polynom from vector A, where p = A.size()
     * a[0] * x^(p - 1) + a[1] * x^(p - 2) + ... + a[p - 1] * x^0
     */
    Polynom(const std::vector<double> &other) {
        data = other;
        std::reverse(data.begin(), data.end());
    }

    /*
     * Copy constructor
     */
    Polynom(const Polynom &other) {
        data = other.data;
    }

    /*
     * Default destructor
     */
    ~Polynom() {}

    /*
     * Returns max degree of polynom
     */
    size_t size() const;

    double& operator[](int index);
    const double& operator[](int index) const;
    Polynom& operator=(const Polynom &other);

    Polynom operator -() const;
    Polynom operator -(const Polynom &other) const;
    Polynom operator +(const Polynom &other) const;
    Polynom operator *(double t) const;
    Polynom operator *(const Polynom &other) const;
    Polynom operator /(double t) const;

    Polynom& operator += (const Polynom &other);
    Polynom& operator -= (const Polynom &other);
    Polynom& operator *= (double t);
    Polynom& operator *= (const Polynom &other);
    Polynom& operator /= (double t);

    bool operator == (const Polynom &other) const;
    bool operator != (const Polynom &other) const;

    friend std::ostream& operator<< (std::ostream &out, const Polynom &polynom);
    friend std::istream& operator>> (std::istream &in, Polynom &polynom);
};

size_t Polynom::size() const {
    return data.size();
}

void Polynom::removeLeadingZeros() {
    while (this->size() > 1 && this->data.back() == 0) this->data.pop_back();
}

double& Polynom::operator[](int index) {
    return data[index];
}

const double& Polynom::operator[](int index) const {
    return data[index];
}

Polynom& Polynom::operator=(const Polynom &other)  {
    this->data = other.data;
    return *this;
}

Polynom Polynom::operator-(const Polynom &other) const {
    Polynom res = *this;
    for (int i = 0; i < data.size(); ++i) {
        if (i == other.data.size()) break;
        res.data[i] -= other.data[i];
    }
    for (size_t i = res.data.size(); i < other.data.size(); ++i) {
        res.data.push_back(-other.data[i]);
    }
    res.removeLeadingZeros();
    return res;
}

Polynom Polynom::operator-() const {
    return (Polynom() - *this);
}

Polynom Polynom::operator+(const Polynom &other) const {
    Polynom res = *this;
    for (int i = 0; i < res.data.size(); ++i) {
        if (i == other.data.size()) break;
        res.data[i] += other.data[i];
    }
    for (size_t i = res.data.size(); i < other.data.size(); ++i) {
        res.data.push_back(other.data[i]);
    }
    res.removeLeadingZeros();
    return res;
}

Polynom Polynom::operator*(const double t) const {
    Polynom res = *this;
    for (double& coof: res.data) coof *= t;
    res.removeLeadingZeros();
    return res;
}

Polynom Polynom::operator*(const Polynom &other) const {
    Polynom res(std::vector<double>(this->size() + other.size() - 1, 0.0));
    for (int i = 0; i < size(); ++i) {
        for (int j = 0; j < other.size(); ++j) {
            res[i + j] += data[i] * other[j];
        }
    }
    return res;
}

Polynom Polynom::operator/(const double t) const {
    Polynom res = *this;
    for (double& coof: res.data) coof /= t;
    return res;
}

bool Polynom::operator==(const Polynom &other) const {
    if (this->size() != other.size()) return false;
    for (int i = 0; i < size(); ++i) {
        if (this->data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool Polynom::operator!=(const Polynom &other) const {
    return !(this->operator==(other));
}

Polynom &Polynom::operator+=(const Polynom &other) {
    this->data = (*this + other).data;
    return *this;
}

Polynom &Polynom::operator-=(const Polynom &other) {
    this->data = (*this + other).data;
    return *this;
}

Polynom &Polynom::operator*=(double t) {
    this->data = (*this * t).data;
    return *this;
}

Polynom &Polynom::operator*=(const Polynom &other) {
    this->data = (*this * other).data;
    return *this;
}

Polynom &Polynom::operator/=(double t) {
    this->data = (*this / t).data;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Polynom &polynom) {
    bool flag = true;
    for (int i = polynom.data.size() - 1; i >= 0; --i) {
        if (polynom.data[i] == 0) continue;
        if (!flag) out << " + ";
        flag = false;
        out << polynom.data[i] << "*x^" << i;
    }
    return out;
}

/*
 * Reads polynom from istream
 * First, it reads the size of the polynomial, and then the coefficients, starting with the maximum degree
 */
std::istream &operator>>(std::istream &in, Polynom &polynom) {
    unsigned int size;
    in >> size;
    polynom.data.resize(size);
    for (int i = 0; i < size; ++i) in >> polynom.data[i];
    reverse(polynom.data.begin(), polynom.data.end());
    return in;
}

int main() {
    Polynom a, b;
    std::cin >> a >> b;
    std::cout << a + b;
    return 0;
}