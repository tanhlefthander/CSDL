#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "PhuThuocHam.h"
using namespace std;

class TapPhuThuocHam // X -> Y
{
private:
    int n;
    vector< PhuThuocHam > ds;
    bool kiemTraCon(string a, string b){ // kiểm tra a có phải là tập con của b
        map< char , bool > m;
        for(int i=0; i< b.size(); i++) m[b[i]] = true;
        for(int i=0; i< a.size(); i++)
            if(!m[a[i]]) return false;
        return true;
    }
    void push(string &a, string b, map<char, bool > &m){ // thêm vào chuỗi a 1 chuỗi b sao cho ko có kí tự nào lặp lại 2 lần
        for(int i=0; i<b.size();i++){
            char c = b[i];
            if(!m[c]){
                m[c]= true;
                a+= c;
            }
        }
    }
    bool daBo(string a, map< char , bool > m){ // kiểm tra xem a đã bị bỏ chưa
        for(int i=0;i<a.size();i++)
            if(!m[a[i]]) return true;
        return false;
    }
public:
    TapPhuThuocHam(){};
    string layBaoDong(string s){
        vector< PhuThuocHam > ds1 = ds;
        vector< PhuThuocHam > ds2;
        string r;
        map<char, bool> m; // kiểm tra nhữ chữ cái đã tồn tại trong r
        push(r,s,m);
        do{
            s= r;
            for(int i=0;i<ds1.size();i++){
                PhuThuocHam p= ds1[i];
                if(kiemTraCon(p.x(),r)) push(r,p.y(),m);
                else ds2.push_back(p);// lưu lại những pth chưa xét đc
            }
            ds1= ds2;
        }while(s!= r);
        return r;
    }
    int Size(){
        return ds.size();
    }
    PhuThuocHam operator [] (int p){
        return ds[p];
    }
    string layBaoDong(string s, int pos){ // tính bao đóng ko xét phụ thuộc hàm thứ pos trong ds
        vector< PhuThuocHam > ds1 = ds;
        vector< PhuThuocHam > ds2;
        string r;
        map<char, bool> m; // kiểm tra nhữ chữ cái đã tồn tại trong r
        push(r,s,m);
        do{
            s= r;
            for(int i=0;i<ds1.size();i++){
                if(i==pos) continue;
                PhuThuocHam p= ds1[i];
                if(kiemTraCon(p.x(),r)) push(r,p.y(),m);
                else ds2.push_back(p);// lưu lại những pth chưa xét đc
            }
            ds1= ds2;
        }while(s!= r);
        return r;
    }
    string rutKhoa (string k,string R){
        string r;
        for(int i=0; i< k.size() ; i++){
            r= k;
            r.erase(r.begin()+i);
            //cout<<r<<"+ : "<<layBaoDong(r)<<endl;
            if(kiemTraCon(R,layBaoDong(r))) return rutKhoa(r,R);
        }
        return k;
    }
    string layKhoa( string R){ // lấy khóa cho lược đồ quan hệ R
        map< char , bool > m; // m[c] = true khi nó thuộc chuỗi đáp án và ngược lại
        for(int i=0;i<R.size();i++)
            m[R[i]]= true;
        for(int i=0;i<n;i++){
            PhuThuocHam p= ds[i];
            if(daBo(p.x(),m)) continue;
            if(kiemTraCon(p.x(),R)){
                string b= p.y();
                for(int j=0;j<b.size();j++) m[b[j]]= false;
            }
        }
        string r;
        for(int i=0;i<R.size();i++)
            if(m[R[i]]) r+= R[i];
        //cout<<r<<endl;
        return rutKhoa(r,R);
    }
    TapPhuThuocHam layTapCucTieu(){
        TapPhuThuocHam t;
        vector< PhuThuocHam > res;
        // phân rã
        PhuThuocHam p;
        string s;
        for(int i=0; i<ds.size();i++){
            p= ds[i];
            s= p.y();
            for(int j=0;j<s.size();j++)
                res.push_back(PhuThuocHam(p.x(),string()+s[j]));
        }
        t.n= res.size();
        t.ds= res;

        // loại bỏ vế phải
        for(int i=0;i<t.n;i++){
            s= t.layBaoDong(t.ds[i].x(),i);
            if(kiemTraCon(t.ds[i].y(),s)){
                //cout<<"Bo "<<t.ds[i]<<endl;
                t.ds.erase(t.ds.begin()+i);
                i--;
                t.n--;
            }
        }
        // loại bỏ vế trái

        for(int i=0;i<t.n;i++){
            s=t.ds[i].x();
            if(s.size()<=1) continue;
            //cout<<s<<endl;
            int j=0;
            while(s.size() > 1){
                string r= s;
                r.erase(r.begin()+j);
                //cout<<r<<endl;
                string bd= t.layBaoDong(r);
                //cout<<bd<<endl;
                if(kiemTraCon(t.ds[i].y(),bd)){
                    s= r;
                    //cout<<s<<endl;
                    continue;
                }
                if(kiemTraCon(string()+ s[j],bd)){
                    s= r;
                    //cout<<s<<endl;
                    continue;
                }
                j++;
                if(j==s.size()) break;
            }
            //cout<<s<<endl;
            t.ds[i].setX(s);
        }
        return t;
    }
    friend istream & operator >> (istream & in, TapPhuThuocHam &p){
        in>>p.n;
        string a,b;
        for(int i=0;i<p.n;i++){
            in>>a>>b;
            p.ds.push_back(PhuThuocHam(a,b));
        }
        return in;
    }
    friend ostream & operator << (ostream & out, TapPhuThuocHam p){
        out<<"{";
        for(int i=0;i<p.n;i++){
            out<<p.ds[i];
            if(i!=p.n-1) out<<", ";
        }
        out<<"}";
        return out;
    }
    string hopNhat(string a, string b){ // hop 2 chuoi
        map< char , bool > m;
        string r;
        for(int i=0; i< a.size();i++){
            m[a[i]] = true;
            r+= a[i];
        }
        for(int i=0; i< b.size();i++){
            if(!m[a[i]])
                r+= a[i];
        }
        return r;
    }
    vector< string > layChuan3NF(string r){
        vector < string > res;
        cout<<"*Lay phan ra chuan 3NF*"<<endl;
        cout<<"R= "<<r<<endl;
        TapPhuThuocHam Fc = layTapCucTieu();
        cout<<"Fc= "<<Fc<<endl;
        string k = layKhoa(r);
        cout<<"Khoa k= "<<k<<endl;
        //nhóm
        string a,b;
        vector < bool > mark(Fc.Size());
        for(int i= 0;i< Fc.Size();i++){
            if(mark[i]) continue;
            a= Fc[i].x();
            b= Fc[i].y();
            mark[i]= true;
            for(int j= i+1;j< Fc.Size();j++){
                if(mark[j]) continue;
                if(a==Fc[j].x()){
                    b+= Fc[j].y();
                    mark[j]= true;
                }
            }
            //cout<<a<<b<<endl;
            res.push_back(a+b);
        }
        cout<<"   ==> p = (";
        bool check= false; // kiem tra bao toan phu thuoc moi noi ko mat ko
        for(int i=0; i< res.size();i++){
            cout<<res[i]<<" ";
            if(kiemTraCon(k,res[i])) check = true;
        }
        cout<<")"<<endl;
        if(check) cout<<"Phan ra p bao toan phu thuoc va co noi khong mat"<<endl;
        else{
            cout<<"Khong bao toan phu thuoc va co noi khong mat !"<<endl;
            cout<<"Noi vao phan ra tap khoa k"<<endl;
            res[0] = hopNhat(res[0],k);
            cout<<"   ==> p = (";
            for(int i=0; i< res.size();i++){
                cout<<res[i]<<" ";
            }
            cout<<")"<<endl;
        }
        return res;
    }
    string xoa2KiTu(string s,int x1, int x2){
        if(x1> x2){
            s.erase(s.begin()+x1);
            s.erase(s.begin()+x2);
        }else{
            s.erase(s.begin()+x2);
            s.erase(s.begin()+x1);
        }
        return s;
    }
    bool thuoc(char c, string s){
        for(int i=0;i< s.size();i++)
            if(s[i]==c) return true;
        return false;
    }
    string thuTucPhanRa(string r, vector< string > &res){
        string Y = r,k,y;
        if(r.size()<3){
            return string();
        }
        cout<<"* Y= " << Y<<endl;
        char A,B,pos; // pos lưa vị trí kí tự chưa xóa trogn lần xét cuối
        for(int i=0;i<Y.size()-1;i++){
            A= Y[i];
            for(int j=0; j<Y.size();j++){
                if(i==j) continue;
                B=Y[j];
                y = xoa2KiTu(Y,i,j);
                k= layBaoDong(y);
                if(thuoc(A,k)){
                    Y.erase(Y.begin()+j);
                    cout<<" ("<<A<<" "<<B<<")  "<<'('<<y<<")+ = "<<k<<" => Y= "<<Y<<endl;
                    pos= i;
                    j--;
                    continue;
                }
                if(thuoc(B,k)){
                    Y.erase(Y.begin()+i);
                    cout<<A<<" "<<B<<" "<<'('<<y<<")+ = "<<k<<" => Y= "<<Y<<endl;
                    pos= j;
                    i--;
                    break;
                }
            }
        }
        cout<<"     => "<<Y<<" khong phan ra duoc nua => "<<Y<<" la luoc do trong phan ra."<<endl<<endl;
        //cout<<r<<endl;
        res.push_back(Y);
        if(Y==r) return string();
        r.erase(r.begin()+pos);
        return r;
    }
    vector < string > layChuanBCNF(string r){
        vector< string > res;
        cout<<"*Lay phan ra chuan BCNF*"<<endl;
        cout<<"R= "<<r<<endl;
        while(r.size()!=0){
            r= thuTucPhanRa(r,res);
        }
        cout<<"     =====> p = (";
        for(int i=0; i< res.size();i++){
            cout<<res[i]<<" ";
        }
        cout<<")";
        return res;
    }

};
