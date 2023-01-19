#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include<queue>
#include <vector>
#define SYM '+'||'^'
#define op(x) (x=='+' || x=='~' || x=='^' || x=='-')
using namespace std;

string* separator(string statement){
    int count{0};
    int lopindex{0};
    string* head =  new string[3];
    string left;
    string right;
    if((statement.length()!=1)&&(statement.at(1)!='~')){
        for(int j{0};j<statement.length();j++){
            if(statement.at(j)=='(') count++;
            else if(statement.at(j)==')') count--;
            if(count==1 && op(statement.at(j))){
                lopindex=j;
            }
        }
        head[1]=statement.at(lopindex);
        statement = statement.substr(1,statement.length()-2);
        head[0]=statement.substr(0,lopindex-1);
        head[2]=statement.substr(lopindex,statement.length()-lopindex);
    }
    return head;

}

bool signcheck(string (*table)[4], int k){
    string (*row) = table[k];
    char signinitial;
    char signchk;
    if (row[1][1]=='e')
    {
        signinitial = row[1][0];
        int a = row[2][0]-'0';
        signchk = separator(table[a-1][0])[1][0];
    }
    else if (row[1][1]=='i'){
        signinitial = row[1][0];
        signchk = separator(row[0])[1][0]; 
    }
    else if (row[1]=="MT"){
        signinitial = '-';
        int a = row[2][0]-'0';
        signchk = separator(table[a-1][0])[1][0];
    }
    cout << signchk << " : " << signinitial << endl;
    if (signchk==signinitial) return 1;
    else return 0;

}

int andintr (string (*table)[4], int k){
    string statement = table[k][0];
    int a = table[k][2][0]-'0';
    int b = table[k][3][0]-'0'; 
    string pre1,pre2;
    string check1 = table[a-1][0];
    string check2 = table[b-1][0];
    pre1=separator(statement)[0];
    pre2=separator(statement)[2];
    /* -FOR DEBUGGING:*/
    cout << pre1 << " : " << check1 << endl;
    cout << pre2 << " : " << check2 << endl;
    if (pre1.compare(check1)==0) {
        if(pre2.compare(check2)==0) return 1;
        else  return 0;
    }
    else return 0;

}
int andel(string (*table)[4], int k, int dex){
    string statement = table[k][0];
    int a = table[k][2][0]-'0';
    string temp = table[a-1][0];
    string check;
    if(dex==1) check=separator(temp)[0];
    else check=separator(temp)[2];
    /* -FOR DEBUGGING:*/
    cout << check << " : " << statement << endl; 

    if(check == statement) return 1;
    else return 0;
}
int orintr(string (*table)[4], int k, int dex){
    int a = table[k][2][0]-'0';
    string check = table[a-1][0];
    string statement = table[k][0];
    string temp;
    if(dex==1) temp = separator(statement)[0];
    else temp = separator(statement)[2];
    /* -FOR DEBUGGING:*/
    cout << check << " : " << temp << endl;

    if(check == temp) return 1;
    else return 0;
}
int implel(string (*table)[4], int k){
    string statement = table[k][0];
    int a = table[k][2][0]-'0';
    int b = table[k][3][0]-'0'; 
    string checkt2 = table[a-1][0];
    string check1 = table[b-1][0];
    string check2,pre;
    pre = separator(checkt2)[0];
    check2 = separator(checkt2)[2];
    /* -FOR DEBUGGING:*/
    cout << checkt2 << endl;
    cout << check1 << " : " << pre << endl;
    cout << check2<< " : " << statement << endl;
   
    if((check1==pre)&&(check2==statement)) return 1;
    else return 0;
}
int mt(string (*table)[4], int k){
    string statement = table[k][0];
    int a = table[k][2][0]-'0';
    int b = table[k][3][0]-'0'; 
    string checkt2 = table[a-1][0];
    string check1 = table[b-1][0];
    string check2,pre;
    pre = "(~" + (separator(checkt2))[2] + ")";
    check2 = "(~"+ (separator(checkt2))[0] + ")";
    /* -FOR DEBUGGING:*/
    cout << check1 << " : " << pre << endl;
    cout << check2<< " : " << statement << endl;
    
    if((check1==pre)&&(check2==statement)) return 1;
    else return 0;
}

int main()
{
    
    //input fn begin

    int n =2;
    cin >> n;
    cin.ignore();
    string input[n][4];
    for (int i{0}; i < n; i++)
    {
        string dummy;
        getline(cin, input[i][0], '/');
        getline(cin, dummy);
        
        if(dummy=="P"){
            input[i][1]=dummy;
            input[i][2]="0";
            input[i][3]="0";
        }
        else{
            int slash = dummy.find('/');
            input[i][1] = dummy.substr(0,slash);
            if((input[i][1]=="^i")||(input[i][1]=="-e")||(input[i][1]=="MT")){
                int slash2 = dummy.find_last_of('/');
                input[i][2]=dummy.substr(slash+1,1);
                input[i][3]=dummy.substr(slash2+1,dummy.length());
            }
            else{
                input[i][2]=dummy.substr(slash+1,dummy.length());
                input[i][3]="0";
            }
        }
           
    }
    int result{0};
    string (*table)[4] = input;

    //input fn end

    // -FOR DEBUGGING:
    // for(int k{0}; k<n; k++){
    //     cout << table[k][0] << ";" << table[k][1] << ";"<< table[k][2] << ";"<< table[k][3] << endl;
    // }


    for(int j{0}; j<n; j++){
        if (table[j][1]=="P") result++;
        else if((table[j][1]=="^i")&&(signcheck(table,j))) result+=andintr(table,j);
        else if((table[j][1]=="+i1")&&(signcheck(table,j))) result+=orintr(table,j,1);
        else if((table[j][1]=="+i2")&&(signcheck(table,j))) result+=orintr(table,j,2);
        else if((table[j][1]=="^e1")&&(signcheck(table,j))) result+=andel(table,j,1);
        else if((table[j][1]=="^e2")&&(signcheck(table,j))) result+=andel(table,j,2);
        else if((table[j][1]=="-e")&&(signcheck(table,j))) result+=implel(table,j);
        else if((table[j][1]=="MT")&&(signcheck(table,j))) result+=mt(table,j);
    }
    // //FOR DEBUGGING:  
    cout << result;
    //cout << signcheck(table[0]);

    if (result == n) cout << "Valid proof";
    else cout << "Invalid proof";

  
    //cout << separatornew("(((a^b)+(b^c))^(c+d))")->at(0);
    
    /* Testing separator function*//*
    cout << separator("p")[0] << " + " << separator("p")[1] << endl;
    cout << separator("~p")[0] << " + " << separator("¬p")[1] << endl;
    cout << separator("~(<statement>)")[0] << " + " << separator("~(<statement>)")[1] << endl;
    cout << separator("((<statement>).(<statement>))")[0] << " + " << separator("((<statement>).(<statement>))")[1] << endl;
    cout << separator("((<statement>)+(<statement>))")[0] << " + " << separator("((<statement>)+(<statement>))")[1] << endl;
    cout << separator("((<statement>)-(<statement>))")[0] << " + " << separator("((<statement>)-(<statement>))")[1] << endl;
    */ //test:successful. :)

    
}
