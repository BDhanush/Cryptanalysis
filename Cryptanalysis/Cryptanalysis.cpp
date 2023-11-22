#include <iostream>
#include <set>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <math.h>
#include <vector>

using namespace std;
using namespace std::chrono;

unordered_map<char,float> englishFreq= { {'A', 0.08167}, {'B', 0.01492}, {'C', 0.02782}, {'D', 0.04253}, {'E', 0.12702}, {'F', 0.02228},
{'G', 0.02015}, {'H', 0.06094}, {'I', 0.06996}, {'J', 0.00153}, {'K', 0.00772}, {'L', 0.04025},
{'M', 0.02406}, {'N', 0.06749}, {'O', 0.07507}, {'P', 0.01929}, {'Q', 0.00095}, {'R', 0.05987},
{'S', 0.06327}, {'T', 0.09056}, {'U', 0.02758}, {'V', 0.00978}, {'W', 0.02360}, {'X', 0.00150},
{'Y', 0.01974}, {'Z', 0.00074} };

double standDev(unordered_map<char,float>& freq,unordered_map<char,float>& englishFreq,int key)
{
    double stdDev=0;
    for(auto& j:freq)
    {
        char c=j.first;
        c='A'+(26+c-'A'-key)%26;
        stdDev+=pow((englishFreq[c]-j.second),2);
    }
    return stdDev;
}

int minStandDev(unordered_map<char,float>& freq,unordered_map<char,float>& englishFreq)
{
    double mini=INT_MAX;
    int key=-1;
    for(int i=1;i<=26;i++)
    {
        double stdDev=standDev(freq,englishFreq,i);
        if(stdDev<mini)
        {
            mini=stdDev;
            key=i;
        }
    }
    return key;
}

pair<string,int> caesarDecrypt(string& caesar)
{
    unordered_map<char,float> freq;
    for(char c='A';c<='Z';c++)
    {
        freq[c]=0;
    }
    for(char& i:caesar)
    {
        freq[i]++;
    }
    for(auto& i:freq)
    {
        i.second/=caesar.length();
    }

    int key=minStandDev(freq,englishFreq);
    pair<string,int> plainKey;
    for(char& i:caesar)
    {
        plainKey.first+=(char)('A'+(26+i-'A'-key)%26);
    }
    plainKey.second+=key;
    return plainKey;

}

void caesarCryptanalysis()
{
    string caesar;
//    cout<<"Input cipher text:\n";
    fstream cipher;
    cipher.open("CaesarCipher.txt");
    cipher>>caesar;
//    cin>>caesar;
    cout<<"Caesar Cipher Crytanalysis\n";
    cout<<"Cipher text:\n"<<caesar<<"\n";

    auto start = high_resolution_clock::now();
    pair<string,int> plainKey=caesarDecrypt(caesar);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Plain text:\n";
    cout<<plainKey.first;
    cout<<"\n";
    cout<<"Key: "<<plainKey.second<<"\n";
    cout<<"Time taken: "<<duration.count()<<" microseconds\n\n";

}

void findFactors(int n,vector<int>& factors)
{
    for(int i=1;i<=sqrt(n);i++)
    {
        if (n%i == 0)
        {
            if (n/i != i)
            {
                factors[n/i]++;
            }
            factors[i]++;
        }
    }
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

void vigenereCrytanalysis()
{
    string vigenere;
//    cout<<"Input cipher text:\n";
    fstream cipher;
    cipher.open("VigenereCipher.txt");
    cipher>>vigenere;
//    cin>>vigenere;
    cout<<"Vigenere Cipher Crytanalysis\n";
    cout<<"Cipher text:\n"<<vigenere<<"\n";

    string key;
    fstream file;
    string filename;
    filename = "EnglishWords.txt";
    file.open(filename.c_str());
    auto start = high_resolution_clock::now();
//    vector<int> factors(vigenere.length()+1);
//    unordered_map<string,int> lastTri;
//    for(int i=0;i<=vigenere.length()-3;i++)
//    {
//        string tri=vigenere.substr(i,3);
//        auto itr=lastTri.find(tri);
//        if(itr!=lastTri.end())
//        {
//            if(i-itr->second>0)
//                findFactors(i-itr->second,factors);
//        }
//        lastTri[tri]=i+3;
//    }
//    int maxi=0,keyL=0;
//    for(int i=2;i<factors.size();i++)
//    {
//        if(factors[i]>maxi)
//        {
//            maxi=factors[i];
//            keyL=i;
//        }
//    }
//    cout<<"\n"<<keyL<<"\n";
//    vector<string> caesar(keyL);
//    for(int i=0;i<vigenere.length();i++)
//    {
//        caesar[i%keyL]+=vigenere[i];
//    }
//    string key="";
//    for(int i=0;i<caesar.size();i++)
//    {
//        key+='A'+caesarDecrypt(caesar[i]).second;
//    }
    double mini=INT_MAX;
    string minKey="";
    while(file>>key)
    {
        unordered_map<char,float> freq;
        int j=0;
        bool b=true;
        for(int i=0;i<key.length();i++)
        {
            key[i]-=32;
        }
        for(int i=0;i<vigenere.length();i++)
        {
            if(!('A'<=vigenere[i] && vigenere[i]<='Z'))
            {
                continue;
            }
            if(key[j%key.length()]<'A' || key[j%key.length()]>'Z')
            {
                b=false;
                break;
            }
            freq[(char)('A'+(26+vigenere[i]-'A'-(key[(j++)%key.length()]-'A'))%26)]++;
        }
        for(char c='A';c<='Z';c++)
        {
            freq[c]/=vigenere.length();
        }
        if(b){
            double stdDev=standDev(freq,englishFreq,0);

//            cout<<key<<" "<<stdDev<<"\n";
            if(mini>stdDev)
            {
                minKey=key;
                mini=stdDev;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Plain text:\n";
    vigenereDecrypt(vigenere,minKey);
    cout<<"Key: "<<minKey<<"\n";
    cout<<"Time taken: "<<duration.count()<<" microseconds\n\n";

}

int main()
{
    ios_base::sync_with_stdio(false);

    int t=1;

    //input for caesar cipher
    /*
    MUYDJUDTJERUWYDEDJXUVYHIJEVVURHKQHOKDHUIJHYSJUTIKRCQHYDUMQHVQHUMUIXQBBUDTUQLEHYDIFYJUEVJXYIJEAUUFJXUKDYJUTIJQJUIEVQCUHYSQDUKJHQBYDJXUULUDJEVJXYIDEJIKSSUUTYDWMUCQAUCUNYSEQFHEFEIQBEVQBBYQDSUEDJXUVEBBEMYDWRQIYICQAUMQHJEWUJXUHCQAUFUQSUJEWUJXUHWUDUHEKIVYDQDSYQBIKFFEHJQDTQDKDTUHIJQDTYDWEDEKHFQHJJXQJCUNYSEYIJEHUSEDGKUHJXUBEIJJUHHYJEHOYDJUNQIDUMCUNYSEQDTQHYPEDQJXUIUJJBUCUDJYDTUJQYBYIBUVJJEOEKOEKMYBBYDVEHCJXUFHUIYTUDJEVJXUQRELUCEIJIUSHUJBOQIIEEDQIJXUEKJRHUQAEVMQHMYJXJXUKDYJUTIJQJUIEVQCUHYSQYISUHJQYDQDTQTTJXUIKWWU
    */

    //input for vigenere cipher
    /*
    VVGPLWKEPIAFWKIFOMTAHUFLJLGMCBNDGVXRRDLQKXCHRPQAGCRTSCHKUFSTYFFAWOCDJBEQRTAZDAFIDIAURBKPGLBNFTTJDBTVSTLLXRRSEGFZTBAYYDRZRDTDXXRRNEUSRSGOOCUKYCTGGYXNRRPAAIHRRQGJLTVTPVALTFANYKXIAWSGUATUEDCUNRVTJMXYEEEOZQOITEYCJXCVPSCJBSZAIGETLVTTQOAEATSCCXYYEYELAIFEIYUMLLTSCKTMROCJGGGRREFSGPYATLLXXGLPLYMHJHPLLAEXEJGKTLFOCYFWOZLJBWYIAEOYFWIFUDCVHNYYZLUXWRUDCLAEAAXCGYOAEEGEXPNDTLEHSGOQRZXCNSPQLAOHGSRZXKRYSYKTSZAWJWKLRNRRZMHNNEFWILNIYRWQTVNEFGLEPADCKPEHSPRZXKNSTQCBMRTSMVTLGHZSYACUACJWLBNBMYYXAYSZQMVCRSDDMELLBCMCXSBMPTAZEAECCUBPUECQOXDBNZRZTVRAYWFHTRFCMEAIZSZUWVAATVLGPHBWSCVBDGHTQEXTUOOAGGSVSEQAGFVNOGFZRRPPYLXDFUMQLKIAGDGFMOGHPCFVRLPECVMEKTEFSMWVLWYDEOJTSCSMTNCVCJMOTUPQKMHRKPWDXNTTSMFVELOFDAGDGHPIWRLRNRRZROHCLLUHNPAECFTTRAWJLAEFUMQLKIAGDRGFAXELDJXQHEYAQTNNLJQALOAIEGXMHRTPVLBSYOYEWGOHGSGLUEPOXCKIOFSTZDXTBDPAJRPGTSCUBPUECRWQTQUCGFZTUEIVLAFEIPBETNPRPYLXDNDPAJRPGIZLEXTUOODGKPBLJYDIHNBPRAVAYCTNZXRFIYADNDVNRTAZEAECCUBPUECRZBSZEEFGWIFKYMOGAFIYBWQOSCZGFVIQEYAWTNQAWJGPTBDPDAGEVFLLWGCEYARWWTRXEFSWBREYCFVRLPECVNSVNRKGGONLAFSUEGINYDHRCOWWSEPUAMCLBCNLNGHAEEAWMFZTBGFCKLTUEVCQEEAGEFLAEBTSCJWEPRJNLBOAMPRZHDFLZUWKOSCZSJLEVSEFWURHTPDGKCRTZKSDEGHTQXTSGECWGNCBUWBGUSRRGCLAERNNPQITRDECPMTBGFCKLTUEVCQEEAGEFLAIFWTJDTLYOHWGNTBLTKAMTUEAMKLIOIWGLBEFFZPTKUGEQMJVEJHTAZVOASTQLLIATCWAGGNLWBAYFRRPLLIOFSTZAEIGIPQXHRNGTTWGLRNRRZTNQARGNXNNLAFSUEGTSCCXYTEYCJTLYYZLDRCBNDGKMSBNWMOXRYEERWKSJHTAZXAFEEFWMAFKLESBNGOXYCXTUEOCUKYCTTMFFOEEOGXYIPUWRQHUNLDMUTNPRPYLXYBUCMOGAYPSYTXTBRPTWGAQDNFSKAPTPPKGUZBPPKIUACESSMIBNPRUMHRBPQLPALTZQWVUEEGGYXNRRPAAIHRRTQLHCUOZQWTVRRJJGGGXEJGLPAFFCCINEATHFWGTUIDAAIHRRHYKLTVLWGFNSRTZAZHOFEPLLBRRCSSFDSBFLZGHKGOPLUKYCTGCJRIZPZPLTNGMPQKTGRSEFWOITEYCJXCVPSCJLHBUWBFMBRUDCVMHBURFKBNPETRALNGSPAMKENNJKGKEUOHCNXRVTHYKNSRDOSJBNTTSPWXCRNESJBEFWTRZHUGBPGFZBEOVC
    */

    while(t--)
    {
        caesarCryptanalysis();
        vigenereCrytanalysis();
    }
    return 0;
}
