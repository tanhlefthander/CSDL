#pragma once
#include <iostream>
#include <string>
using namespace std;

class PhuThuocHam // X -> Y
{
private:
    string X;
    string Y;
public:
    PhuThuocHam(){};
    PhuThuocHam(string a, string b){
        this->X= a;
        this->Y= b;
    }
    void setX(string x){
        X= x;
    }
    void setY(string x){
        Y= x;
    }
    string x(){return X;}
    string y(){return Y;}
    friend ostream & operator << (ostream & out, PhuThuocHam p){
        out<<p.X<<"->"<<p.Y;
        return out;
    }
};
