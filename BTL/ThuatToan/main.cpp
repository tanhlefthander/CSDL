#include <iostream>
#include <string>
#include <vector>
#include "TapPhuThuocHam.h"
#include <cstdio>
using namespace std;
int main(){
    freopen("data.txt","r",stdin);
    TapPhuThuocHam t;
    cin>>t;
    cout<<"F= "<<t<<endl;
    //cout<<t.layBaoDong("BD");
    //cout<<t.layKhoa("BOSQID");
    //cout<<t.layTapCucTieu()<<endl;
    t.layChuan3NF("CTHRSG");
    cout<<endl;
    t.layChuanBCNF(string("CTHRSG"));
    return 0;
}
