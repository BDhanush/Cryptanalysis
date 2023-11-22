#include <iostream>
#include <set>
#include <fstream>
#include <time.h>

using namespace std;

int caesarEncrypt(string& text)
{
    int key=1+rand()%26;
    for(int i=0;i<text.length();i++)
    {
        if(!('A'<=text[i] && text[i]<='Z'))
        {
            cout<<text[i];
            continue;
        }
        cout<<(char)('A'+(text[i]+key-'A')%26);
    }
    cout<<"\n";
    return key;
}

void caesarDecrypt(string& text,int key)
{
    for(int i=0;i<text.length();i++)
    {
        if(!('A'<=text[i] && text[i]<='Z'))
        {
            cout<<text[i];
            continue;
        }
        cout<<(char)('A'+(26+text[i]-key-'A')%26);
    }
}

string vigenereEncrypt(string& text)
{
    int keyl=1+rand()%text.length();
    string key="";
    for(int i=0;i<keyl;i++)
    {
        key+=('A'+rand()%26);
    }
    int j=0;
    for(int i=0;i<text.length();i++)
    {
        if(!('A'<=text[i] && text[i]<='Z'))
        {
            cout<<text[i];
            continue;
        }
        cout<<(char)('A'+(text[i]-'A'+key[(j++)%key.length()]-'A')%26);
    }
    cout<<"\n";
    return key;
}

void vigenereDecrypt(string& text,string key)
{
    int j=0;
    for(int i=0;i<text.length();i++)
    {
        if(!('A'<=text[i] && text[i]<='Z'))
        {
            cout<<text[i];
            continue;
        }
        cout<<(char)('A'+(26+text[i]-'A'-(key[(j++)%key.length()]-'A'))%26);
    }
    cout<<"\n";
}

string useKeyPFE(char a,char b,char key[5][5])
{
    int i1,j1,i2,j2;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(key[i][j]==a)
            {
                i1=i;
                j1=j;
            }
            if(key[i][j]==b)
            {
                i2=i;
                j2=j;
            }
        }
    }
    string e="";
    if(i1==i2)
    {
        e+=key[(i1+1)%5][j1];
        e+=key[(i2+1)%5][j2];
    }else if(j1==j2)
    {
        e+=key[i1][(j1+1)%5];
        e+=key[i2][(j2+1)%5];
    }else{
        e+=key[i1][j2];
        e+=key[i2][j1];
    }
    return e;
}

string useKeyPFD(char a,char b,char key[5][5])
{
    int i1,j1,i2,j2;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(key[i][j]==a)
            {
                i1=i;
                j1=j;
            }
            if(key[i][j]==b)
            {
                i2=i;
                j2=j;
            }
        }
    }
    string e="";
    if(i1==i2)
    {
        e+=key[(5+i1-1)%5][j1];
        e+=key[(5+i2-1)%5][j2];
    }else if(j1==j2)
    {
        e+=key[i1][(5+j1-1)%5];
        e+=key[i2][(5+j2-1)%5];
    }else{
        e+=key[i1][j2];
        e+=key[i2][j1];
    }
    return e;
}

string playfairEncrypt(string& text)
{
    for(int i=0;i<text.length();i++)
    {
        if(text[i]=='J')
        {
            text[i]='I';
        }
        if(i-1>=0 && text[i-1]==text[i])
        {
            text.insert(i,"X");
        }
    }
    if(text.length()%2)
    {
        text+='Z';
    }
    string key="RANDOM";
    char grid[5][5];
    set<char> s;
    for(char c='A';c<='Z';c++)
    {
        if(c!='J')
        {
            s.insert(c);
        }
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(5*i+j<key.length()){
                grid[i][j]=key[5*i+j];
                s.erase(key[5*i+j]);
            }else{
                grid[i][j]=*(s.begin());
                s.erase(s.begin());
            }
        }
    }
    for(int i=0;i<text.length();i+=2)
    {
        string e=useKeyPFE(text[i],text[i+1],grid);
        text[i]=e[0];
        text[i+1]=e[1];
        cout<<e;
    }
    cout<<"\n";
    return key;

}

void playfairDecrypt(string& text,string& key)
{
    char grid[5][5];
    set<char> s;
    for(char c='A';c<='Z';c++)
    {
        if(c!='J')
        {
            s.insert(c);
        }
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(5*i+j<key.length()){
                grid[i][j]=key[5*i+j];
                s.erase(key[5*i+j]);
            }else{
                grid[i][j]=*(s.begin());
                s.erase(s.begin());
            }
        }
    }
    for(int i=0;i<text.length();i+=2)
    {
        string e=useKeyPFD(text[i],text[i+1],grid);
        text[i]=e[0];
        text[i+1]=e[1];
        cout<<e;
    }
    cout<<"\n";

}

int encrypt(int n,string& text)
{
    switch(n)
    {
    case 1:
        {
            int key=caesarEncrypt(text);
            cout<<"key: "<<key<<"\n";
        }
        break;
    case 2:
        {
            string key=vigenereEncrypt(text);
            cout<<"key: "<<key<<"\n";
        }
        break;
    case 3:
        {
            string key=playfairEncrypt(text);
            cout<<"key: "<<key<<"\n";
        }
        break;
    }
}

int decrypt(int n,string& text)
{
    switch(n)
    {
    case 1:
        {
            int key;
            cout<<"Enter key: ";
            cin>>key;
            cout<<"\n";
            caesarDecrypt(text,key);
        }
        break;
    case 2:
        {
            string key;
            cout<<"Enter key: ";
            cin>>key;
            cout<<"\n";
            vigenereDecrypt(text,key);
        }
        break;
    case 3:
        {
            string key;
            cout<<"Enter key: ";
            cin>>key;
            cout<<"\n";
            playfairDecrypt(text,key);
        }
        break;
    }
}

void select()
{
    int n;
    cout<<"Select an encryption/decryption algorithm (your text should contain uppercase characters only: \n";
    cout<<"Caesar cipher, 1\n";
    cout<<"Vigenere cipher, 2\n";
    cout<<"Playfair cipher, 3\n";
    cout<<"Enter a valid number: ";
    cin>>n;
    cout<<"\n";
    cout<<"Do you want to encrypt(1) or decrypt(2)?\n";
    cout<<"Enter a valid number: ";
    int ed;
    cin>>ed;
    cout<<"\n";
    string text;
    fstream file;
    string filename;
    filename = "process.txt";
    file.open(filename.c_str());
    file>>text;
//    cin>>text;

    if(ed==1)
    {
        encrypt(n,text);
    }else if(ed==2)
    {
        decrypt(n,text);
    }

}

int main()
{
    ios_base::sync_with_stdio(false);

    int t=1;
    srand(time(0));

    while(t--)
    {
        select();
    }
    return 0;
}
