#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef pair < string , string > PhuThuocHam; // Phụ thuộc hàm

////////////////////////////////////////////////////////////////

int n;// số phụ thuộc hàm
vector< PhuThuocHam > dsPTH; // danh sách phụ thuộc hàm


void nhapDs(){
    cin>>n;
    string a,b;
    for(int i=0;i<n;i++){
        cin>>a>>b;
        dsPTH.push_back(PhuThuocHam(a,b));
    }
}
void xuatDs(){
    cout<<"{  ";
    for(int i=0;i<n;i++){
        cout<<dsPTH[i].first<<"->"<<dsPTH[i].second<<"  ";
    }
    cout<<"}"<<endl;
}
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
string layLuocDo(string s) // lấy lược đồ từ s+
{
    vector< PhuThuocHam > ds = dsPTH;
    vector< PhuThuocHam > ds2;
    string r;
    map<char, bool> m; // kiểm tra nhữ chữ cái đã tồn tại trong r
    push(r,s,m);
    do{
        s= r;
        for(int i=0;i<ds.size();i++){
            PhuThuocHam p= ds[i];
            if(kiemTraCon(p.first,r)) push(r,p.second,m);
            else ds2.push_back(p);// lưu lại những pth chưa xét đc
        }
        ds= ds2;
    }while(s!= r);
    return r;
}
bool daBo(string a, map< char , bool > m){ // kiểm tra xem a đã bị bỏ chưa
    for(int i=0;i<a.size();i++)
        if(!m[a[i]]) return true;
    return false;
}
string rutKhoa (string k,string R){
    string r;
    for(int i=0; i< k.size() ; i++){
        r= k;
        r.erase(r.begin()+i);
        cout<<r<<"+ : "<<layLuocDo(r)<<endl;
        if(kiemTraCon(R,layLuocDo(r))) return rutKhoa(r,R);
    }
    return k;
}
string layKhoa( string R){ // lấy khóa cho lược đồ quan hệ R
    map< char , bool > m; // m[c] = true khi nó thuộc chuỗi đáp án và ngược lại
    for(int i=0;i<R.size();i++)
        m[R[i]]= true;
    for(int i=0;i<dsPTH.size();i++){

        PhuThuocHam p= dsPTH[i];
        if(daBo(p.first,m)) continue;
        if(kiemTraCon(p.first,R)){
            string b= p.second;
            for(int j=0;j<b.size();j++) m[b[j]]= false;
        }
    }
    string r;
    for(int i=0;i<R.size();i++)
        if(m[R[i]]) r+= R[i];
    //cout<<r<<endl;
    return rutKhoa(r,R);
}

