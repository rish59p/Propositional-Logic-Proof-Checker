#include <iostream>
#include <cctype>
#include <string>

using namespace std;

string* separator(string statement){

    string* head =  new string[2];
    int count{0}; int keep{0};
    if(statement.at(0)=='('){
        if(statement.at(1)!='('){
            head[0] = statement.substr(1,1);
            if(statement.at(3)!='(') head [1] = statement.substr(3,1);
            else head[1] = statement.substr(4,statement.length()-keep-6);
        }
        else{
            keep=0;
            while(!((!count)&&(keep))){
                if (statement.at(keep+1)=='(') count++;
                else if (statement.at(keep+1)==')') count--;
                keep++;
            }
            head[0] = statement.substr(2,keep-2); 
            if(statement.at(keep+2)=='('){
                head[1] = statement.substr(keep+3,statement.length()-keep-5);
            }
            else head[1] = statement.substr(keep+2,1);
        }
        
    }
    else if(statement.at(0)=='~'){
        head[0] = statement;
        head[1] = "-";
    }
    else {
        head[0] = statement;
        head[1] = "-";
    } 
    return head;

}

bool signcheck(string (*table)[4], int k){
    string (*row) = table[k];
    if((row[1][0]=='-')||(row[1]=="MT")){
        int a = table[k][2][0]-'0';
        string statement = table[a-1][0];
        string pre1 = separator(statement)[0];
        string pre2 = separator(statement)[1];
        if(statement.at(1)=='(') statement.erase(0,pre1.length()+3);
        else statement.erase(0,pre1.length()+1);
        // debugging : 
        cout << statement << endl;
        if(statement.at(1)=='(') statement.erase(1,pre1.length()+3);
        else statement.erase(1,pre1.length()+1);
        if(statement[0]=='-') return 1;
        else return 0;
    }
    else{
        string statement = row[0];
        string pre1 = separator(statement)[0];
        string pre2 = separator(statement)[1];
        if(statement.at(1)=='(') statement.erase(0,pre1.length()+3);
        else statement.erase(0,pre1.length()+1);
        // debugging : 
        cout << statement << endl;
        if(statement.at(1)=='(') statement.erase(1,pre1.length()+3);
        else statement.erase(1,pre1.length()+1);
        // debugging : 
        cout << pre1 << " : " << pre2 << endl << statement;
        if(statement[0]==row[1][0]) return 1;
        else return 0;
    }

}
int andintr (string (*table)[4], int k){
    string statement = table[k][0];
    int a = table[k][2][0]-'0';
    int b = table[k][3][0]-'0'; 
    string pre1,pre2;
    string check1 = table[a-1][0];
    string check2 = table[b-1][0];
    if(check1.at(0)=='('){
        pre1 = "(" + separator(statement)[0] + ")";
    }
    else{
        pre1 = separator(statement)[0];
    }
    if(check2.at(0)=='('){
        pre2 = "(" + separator(statement)[1] + ")";
    }
    else{
        pre2 = separator(statement)[1];
    }
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
    if(statement.at(0)=='(') check = "("+ (separator(temp)[dex-1])+")";
    else check = (separator(temp)[dex-1]);
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
    if(check.at(0)=='(') temp = "("+ (separator(statement)[dex-1])+")";
    else temp = (separator(statement)[dex-1]);
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
    if(check1.at(0)=='(') string pre = "(" + separator(checkt2)[0] + ")";
    else  pre = separator(checkt2)[0];
    if(statement.at(0)=='(') string check2 = "(" + separator(checkt2)[1] + ")";
    else  check2 = separator(checkt2)[1];
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
    if(check1.at(1)=='(') pre = "~(" + (separator(checkt2))[1] + ")";
    else  pre = "~" + (separator(checkt2))[1];
    if(statement.at(1)=='(') check2 = "~(" + (separator(checkt2))[0] + ")";
    else  check2 = "~"+ (separator(checkt2))[0];
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

    /* -FOR DEBUGGING:
    // for(int k{0}; k<n; k++){
    //     cout << table[k][0] << ";" << table[k][1] << ";"<< table[k][2] << ";"<< table[k][3] << endl;
    // }
    */

    for(int j{0}; j<n; j++){
        if (table[j][1]=="P") result++;
        else if((table[j][1]=="^i")&&(signcheck(table,j))) result+=andintr(table,j);
        else if((table[j][1]=="+i1")&&(signcheck(table,j))) result+=orintr(table,j,1);
        else if((table[j][1]=="+i2")&&(signcheck(table,j))) result+=orintr(table,j,2);
        else if((table[j][1]=="^e1")&&(signcheck(table,j))) result+=andel(table,j,1);
        else if((table[j][1]=="^e2")&&(signcheck(table,j))) result+=andel(table,j,2);
        else if((table[j][1]=="-e")) result+=implel(table,j);
        else if((table[j][1]=="MT")) result+=mt(table,j);
    }
    // //FOR DEBUGGING:  
    cout << result;
    //cout << signcheck(table[0]);

    if (result == n) cout << "valid proof";
    else cout << "invalid proof";
   

    /* Testing separator function*//*
    cout << separator("p")[0] << " + " << separator("p")[1] << endl;
    cout << separator("~p")[0] << " + " << separator("¬p")[1] << endl;
    cout << separator("~(<statement>)")[0] << " + " << separator("~(<statement>)")[1] << endl;
    cout << separator("((<statement>).(<statement>))")[0] << " + " << separator("((<statement>).(<statement>))")[1] << endl;
    cout << separator("((<statement>)+(<statement>))")[0] << " + " << separator("((<statement>)+(<statement>))")[1] << endl;
    cout << separator("((<statement>)-(<statement>))")[0] << " + " << separator("((<statement>)-(<statement>))")[1] << endl;
    */ //test:successful. :)

    
}