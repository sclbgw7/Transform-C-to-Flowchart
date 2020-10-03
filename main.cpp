#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

//reserved words
string rword[19]=
{"","short","int","float","double","char",//0-5
"if","else","while","for","return",//6-10
"break","continue","define","include","getchar",//11-15
"scanf","printf"};//16-17

int main()
{

	//freopen("code.cpp","r",stdin);
	//freopen("temp_1.dot","w",stdout);
	//read

	//puts("digraph gr1{a;b;c;d;test_yyhyyds;aa->b;b->d;c->d;}");

	//write


	//freopen("CON","r",stdin);
	//freopen("CON","w",stdout);
	system(".\\Graphviz_2.44.1\\bin\\dot -Tpng temp_1.dot -o Flowchart.png");
	puts("Finished.");
	system("pause");
	return 0;
}
