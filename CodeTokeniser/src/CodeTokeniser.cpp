//============================================================================
// Name        : CodeTokeniser.cpp
// Author      : Vaibhav Pallod
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;


struct Literal{
int address ;
string literal;
};

struct Symbol{
int address ;
int position;
int symValue;
};

struct UST{

	string lexene;
	string type;
	int index;
	string token;

	UST(string lexene,string type,int index,string token){
		this->lexene=lexene;
		this->type=type;
		this->index=index;
		this->token=token;
	};

};

class Hashtable{
private:
    int litPos=0,symPos=0;

	set<string> kwt={
			"auto",
			"break",
			"if",
			"else",
			"do",
			"while",
			"for",
			"int",
			"float",
			"char",
			"double",
			"switch",
			"return",

	};

	set<char> term={
			'(',
			')',
			'{',
			'}',
			'[',
			']',
			'-',
			'+',
			'*',
			'/',
			',',
			'.',
			'?',
			'>',
			'<',
			'&',
			'%',
			'!',
			':',
			'=',
			';'

	};

	map<string,Symbol> mSymbol;
    map<int,Literal> mLiteral;
    vector<UST> ustTable;
public:

	void tokeniseInput(){
		int termPos=0;
		string inpCodePath="G:/Codeblocks/CodeTokeniser/inpcode.txt";
			ifstream file(inpCodePath);
			if(file.is_open()){
//				cout<<" _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
//				cout<<"|\tLexene\tType\tIndex\t|\n";
				cout<<"Lexene\tType\tIndex\tToken\n";


				string line;
				while(getline(file,line,'\n')){
					queue<char> q;
					string iskeyword="";
					for(unsigned int i=0;i<line.length();i++){
						q.push(line[i]);
					}

					for(unsigned int i=0;i<line.length();i++){
						if(isalpha(q.front())!=0 ||(isdigit(q.front())!=0 && !iskeyword.empty())){
							iskeyword+=q.front();
							q.pop();
						}else{

							if(q.front()==' '||q.front()=='\t'|| term.find(q.front())!=term.end() ){

								// Do comments part here
								if(!iskeyword.empty()){
										if(kwt.find(iskeyword)!=kwt.end()){
										auto itr=kwt.find(iskeyword);
										int pos=distance(kwt.begin(),itr);
//										cout<<"|\t"<<iskeyword<<"\tKWT\t"<<pos<<"\t|"<<endl;
										ustTable.push_back(UST(iskeyword,"KWT",pos,iskeyword));

		//								iskwt="YES";
										iskeyword.clear();
									}else{
										if(mSymbol.find(iskeyword)==mSymbol.end()){
//											cout<<"|\t"<<iskeyword<<"\tSYM\t"<<symPos<<"\t|"<<endl;
											ustTable.push_back(UST(iskeyword,"SYM",symPos,"ID"+to_string(symPos)));

											if(iskeyword.length()>1){
												Symbol symobj;
												symobj.position=symPos++;
												symobj.address=0;
												symobj.symValue=0;
												mSymbol.insert({iskeyword,symobj});
											}

										}
										else{
											int dis=distance(mSymbol.begin(),mSymbol.find(iskeyword));
//											cout<<"|\t"<<iskeyword<<"\tSYM\t"<<dis<<"\t|"<<endl;
											ustTable.push_back(UST(iskeyword,"SYM",symPos,"ID"+to_string(dis)));

										}
										iskeyword.clear();

									}

								}

								if(q.front()==' '||q.front()=='\t'){
									while(q.front()==' '||q.front()=='\t'){
										q.pop();
									}
								}
								else if(term.find(q.front())!=term.end() ){

									string temp;
									temp+=q.front();
									q.pop();

									if(q.front()=='/'){        						 // VAlidating comments
										break;
									}
									else if(q.front()==temp[0] || q.front()=='='){
										temp+=q.front();
										q.pop();
										i++;
										ustTable.push_back(UST(temp,"KWT",termPos++,temp));
//										cout<<"|\t"<<temp<<"\tTERM\t"<<termPos<<"\t|\n";
									}
									else{
										ustTable.push_back(UST(temp,"KWT",termPos++,temp));
//										cout<<"|\t"<<temp<<"\tTERM\t"<<termPos<<"\t|\n";
									}
								}

							}else if(q.front()=='"'){
								q.pop();
								string argtype="";
								while( i<line.length() && (q.front()!='"')){
									argtype+=q.front();
									q.pop();
									i++;
								}
								q.pop();
//								cout<<"|\t"<<argtype<<"\tLIT\t"<<litPos<<"\t|\n";
								ustTable.push_back(UST(argtype,"LIT",litPos,"LT"+to_string(litPos)));


								Literal litobj;
								litobj.address=0;
								litobj.literal=argtype;
								mLiteral.insert({litPos++,litobj});
								i++;
							}else if(isdigit(q.front())!=0){
								string temp;
								temp+=q.front();
//								cout<<"|\t"<<temp<<"\tLIT\t"<<litPos<<"\t|"<<endl;
								ustTable.push_back(UST(temp,"LIT",litPos,"LT"+to_string(litPos)));

								Literal litobj;
								litobj.address=0;
								litobj.literal=to_string(q.front()-48);


								mLiteral.insert({litPos++,litobj});
								q.pop();
							}





						}

					}



				}
//				cout<<"|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";

			}

	}


    void printTables(){

//        cout<<endl<<"-----------------------------------------"<<endl<<endl;

        for(auto itr=ustTable.begin();itr!=ustTable.end();itr++){

        	cout<<itr->lexene<<"\t"<<itr->type<<"\t"<<itr->index<<"\t"<<itr->token<<endl;

        }


        cout<<endl<<"-----------------------------------------"<<endl<<endl;

        cout<<endl<<"-----------------------------------------"<<endl<<endl;
        cout<<"SYMBOL TABLE\n _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
        cout<<"| Sym\tPos\tAddr\t|\n";

        for(auto itr=mSymbol.begin();itr!=mSymbol.end();itr++){

            cout<<"| "<<itr->first<<"\t"<<itr->second.position<<"\t"<<itr->second.address<<"\t| "<<endl;

        }
        cout<<"|_ _ _ _ _ _ _ _ _ _ _ _|"<<endl<<endl<<"LITERAL TABLE\n _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
        cout<<"| Lit\tPos\tAddr\t|\n";
        for(auto itr=mLiteral.begin();itr!=mLiteral.end();itr++){

            cout<<"| "<<itr->second.literal<<"\t"<<itr->first<<"\t"<<itr->second.address<<"\t| "<<endl;

        }
        cout<<"|_ _ _ _ _ _ _ _ _ _ _ _|";
//        cout<<endl<<endl<<"POOL TABLE\n _ _"<<endl;
//
//        for(int i=0;i<poolTable.size();i++){
//
//            cout<<"| "<<i<<" | "<<endl;
//
//        }
////        cout<<endl<<"-----------------------------------------"<<endl;
//        cout<<"|_ _|";
        cout<<endl<<"-----------------------------------------"<<endl<<endl;

    }

};

int main() {

	freopen("output.txt","w",stdout);

	Hashtable ht;
	ht.tokeniseInput();
	ht.printTables();
	return 0;
}



/*

stringstream s(line);
					string word;
					while(getline(s,word,' ')){
						string iskwt="NO";
						int asciicode=0;

						for(unsigned int i=0;i<word.length();i++){
							asciicode=(int)word[i];

							if((asciicode>96 &&asciicode<123 )||(asciicode>64 &&asciicode<91)){
								int j=i;
								string str="";
								str+=word[i];
								i++;
								while((asciicode>96 &&asciicode<123 )||(asciicode>64 &&asciicode<91)){
									j++;
									i++;
									if(word[j]=='\0'){
										break;
									}else{
										asciicode=(int)word[j+1];
										str+=word[j];
									}
								}
								if(kwt.find(str)!=kwt.end()){
									auto itr=kwt.find(str);
									int pos=distance(kwt.begin(),itr);
									cout<<"|\t"<<str<<"\tKWT\t"<<pos<<"\t|"<<endl;
									iskwt="YES";
								}else{
									if(mSymbol.find(str)==mSymbol.end()){
										cout<<"|\t"<<str<<"\tSYM\t"<<symPos<<"\t|"<<endl;
										if(str.length()>1){
											Symbol symobj;
											symobj.position=symPos++;
											symobj.address=0;
											symobj.symValue=0;
											mSymbol.insert({str,symobj});
										}
									}
									else{
										cout<<"|\t"<<str<<"\tSYM\t"<<distance(mSymbol.begin(),mSymbol.find(str))<<"\t|"<<endl;

									}
								}
							}
							else if(word[i]=='"'){
								string argtype="";
								while( i<word.length() && (word[++i]!='"')){
									argtype+=word[i];
								}
								cout<<"|\t"<<argtype<<"\tLIT\t"<<litPos<<"\t|\n";
								Literal litobj;
								litobj.address=0;
								litobj.literal=argtype;
								mLiteral.insert({litPos++,litobj});
								i++;
							}else if(asciicode<58 && asciicode>47){

								cout<<"|\t"<<word[i]-48<<"\tLIT\t"<<litPos<<"\t|"<<endl;

								Literal litobj;
								litobj.address=0;
								litobj.literal=to_string(word[i]-48);
								mLiteral.insert({litPos++,litobj});
								i++;

							}

							while(word[i]==' '||word[i]=='\0')
								i++;

							if(i<word.length())
							cout<<"|\t"<<word[i]<<"\tTERM\t"<<termPos++<<"\t|\n";


						}

					}


 */




