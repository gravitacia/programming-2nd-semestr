#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point
{
private:
    float x, y;
public:
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(float _x, float _y) : x(_x), y(_y){}

    void operator= (const Point &point)
    {
        x = point.getX();
        y = point.getY();
    }

    void operator= (float Z)
    {
        x = Z;
        y = Z;
    }

    void Print()
    {
        cout << "X = " << x << " " << "Y = " << y << endl;
    }

    float getX() const
    {
        return x;
    }
    float getY() const
    {
        return y;
    }

};

class Broken
{
protected:
    float distanceToPoint(Point &a, Point &b)
    {
        return sqrt(pow((a.getX() - b.getX()),2)+pow((a.getY() - b.getY()),2));
    }
    vector<Point> arrPoint;
public:
    Broken(){}
    Broken(Point arr[], int k)
    {
        for (int i = 0 ; i < k; i++)
            arrPoint.push_back(arr[i]);
    }

    virtual void operator= (const vector<Point> &b)
    {
        for (int i = 0; i < b.size(); i++)
        {
            arrPoint[i] = b[i];
        }
    }

    virtual float getL()
    {
        float l = 0;
        for (int i = 0; i < arrPoint.size() - 1; i++)
        {
            l += distanceToPoint(arrPoint[i], arrPoint[i + 1]);
        }
        return l;
    }
    void Print()
    {
        cout << "Broken consists of " << arrPoint.size() << endl;
        for (int i = 0; i < arrPoint.size(); i++)
        {
            cout << "X" << i << " = " << arrPoint[i].getX() << " Y" << i << " = " << arrPoint[i].getY() << endl;
        }
    }

};

class ClosedBroken : public Broken
{
public:
    ClosedBroken(){}
    ClosedBroken(Point arr[], int size) : Broken(arr, size){}

    virtual float getL()
    {
        float l = Broken :: getL();
        l += distanceToPoint(arrPoint[0], arrPoint[arrPoint.size() - 1]);
        return l;
    }
};

class Polygon : public ClosedBroken
{
protected:
    vector<float> edge;
    vector<float> angle;

    struct Vector
    {
        float x, y;
    };

    vector<Vector> vect;

    void Edge()
    {
        float temp;
        for (int i = 0; i < arrPoint.size() - 1; i++)
        {
            temp = distanceToPoint(arrPoint[i], arrPoint[i + 1]);
            edge.push_back(temp);
        }
        temp = distanceToPoint(arrPoint[arrPoint.size() - 1], arrPoint[0]);
        edge.push_back(temp);
    }
    void Vect()
    {
        Vector temp;
        for (int i = 0; i < arrPoint.size() - 1; i++)
        {
            temp.x = arrPoint[i+1].getX() - arrPoint[i].getX();
            temp.y = arrPoint[i+1].getY() - arrPoint[i].getY();
            vect.push_back(temp);
        }
        temp.x = arrPoint[0].getX() - arrPoint[arrPoint.size() - 1].getX();
        temp.y = arrPoint[0].getY() - arrPoint[arrPoint.size() - 1].getY();
        vect.push_back(temp);
    }
    void Angle()
    {
        float scalarP, an;
        scalarP = vect[0].x * vect[arrPoint.size() - 1].x + vect[0].y * vect[arrPoint.size() - 1].y;
        an = acos(scalarP / sqrt(vect[0].x * vect[0].x + vect[0].y * vect[0].y) *
                  sqrt(vect[vect.size() - 1].x * vect[vect.size() - 1].x + vect[vect.size() - 1].y * vect[vect.size() - 1].y));
        angle.push_back(an);
        for (int i = 0; i < arrPoint.size() - 1; i++)
        {
            scalarP = vect[i].x * vect[i+1].x + vect[i].y * vect[i+1].y;
            an = acos(scalarP / sqrt(vect[0].x * vect[0].x + vect[0].y * vect[0].y) *
                      sqrt(vect[vect.size() - 1].x * vect[vect.size() - 1].x + vect[vect.size() - 1].y * vect[vect.size() - 1].y));
            angle.push_back(an);
        }
    }
public:
    Polygon(Point arr[], int k)
    {
        for (int i = 0 ; i < k; i++)
            arrPoint.push_back(arr[i]);
        Edge();
        Vect();
        Angle();
        check();
    }
    void kill()
    {
        arrPoint.clear();
    }
    void check()
    {
        float sumAngle = 0;
        for (int i = 0; i < angle.size(); i++)
            sumAngle += angle[i];
        if ( sumAngle == 180*(arrPoint.size() - 2) )
        {
            for (int i = 0; i < arrPoint.size(); i++)
                arrPoint[i] = NULL;
        }
    }
    float Perimeter()
    {
        float p = 0;
        for (int i = 0; i < arrPoint.size(); i++)
            p += edge[i];
        return p;
    }
    float Square()
    {
        float square = 0;
        for (int i = 0; i < arrPoint.size() - 1; i++)
        {
            square += arrPoint[i].getX() * arrPoint[i + 1].getY();
        }
        square += arrPoint[arrPoint.size() - 1].getX() * arrPoint[0].getY();
        for (int i = 0; i < arrPoint.size() - 1; i++)
        {
            square -= arrPoint[i + 1].getX() * arrPoint[i].getY();
        }
        square -= arrPoint[0].getX() * arrPoint[arrPoint.size() - 1].getY();
        return (0.5) * abs(square);
    }

};

class Triangle : public Polygon
{
public:
    Triangle(Point arr[], int size) : Polygon(arr, size)
    {
        if (Check() == false)
            kill();
    }
    bool Check()
    {
        bool check = true;
        float k1 = 0, k2 = 0, k3 = 0;
        float random;
        random = rand()%2000000 - 1000000;
        k1 = (arrPoint[0].getY() + random) / (arrPoint[0].getX() + random);
        k2 = (arrPoint[1].getY() + random) / (arrPoint[1].getX() + random);
        k3 = (arrPoint[2].getY() + random) / (arrPoint[2].getX() + random);
        if (k1 == k2 && k2 == k3 && k3 == k1)
        {
            check = false;
            return check;
        }
    }
};

class Trapezoid : public Polygon
{
public:
    Trapezoid(Point arr[], int size) : Polygon(arr, size)
    {
        if (Check() == false)
            kill();
    }
    float S(float a, float b, float c)
    {
        float s = 0, p = 0;
        p = (a + b + c) / 2;
        s = sqrt(p * (p - a) * (p - b) * (p - c));
        return s;
    }
    bool Check()
    {
        bool check = true;
        float an1, an2, an3, an4, ab, bc, cd, da, ac, bd;
        ab = distanceToPoint(arrPoint[0], arrPoint[1]);
        bc = distanceToPoint(arrPoint[1], arrPoint[2]);
        cd = distanceToPoint(arrPoint[2], arrPoint[3]);
        da = distanceToPoint(arrPoint[3], arrPoint[0]);
        ac = distanceToPoint(arrPoint[0], arrPoint[2]);
        bd = distanceToPoint(arrPoint[1], arrPoint[3]);
        float s1 = S(bc, cd, bd), s2 = S(ab, da, bd);
        an1 = asin((2 * s1) / (bc * bd));
        an2 = asin((2 * s2) / (da * bd));
        an3 = asin((2 * s2) / (ab * bd));
        an4 = asin((2 * s2) / (bd * cd));
        if ( an1 == an2 && an3 == an4 && bc != da )
        {
            check = false;
            return check;
        }
    }
};

class RegularPolygon : public Polygon
{
public:
    RegularPolygon(Point arr[], int size) : Polygon(arr, size)
    {
        checkRegular();
    }
    void checkRegular()
    {
        bool check = true;
        for (int i = 0; i < edge.size() - 1; i++)
        {
            if (edge[i] != edge[i + 1])
                check = false;
        }
        if (edge[0] != edge[edge.size() - 1])
            check = false;

        for (int i = 0; i < angle.size() - 1; i++)
        {
            if (angle[i] != angle[i + 1])
                check = false;
        }
        if (angle[0] != angle[angle.size() - 1])
            check = false;
        if (check == false)
        {
            for (int i = 0; i < arrPoint.size(); i++)
                arrPoint[i] = NULL;
        }
    }
};

int main()
{

    return 0;
}