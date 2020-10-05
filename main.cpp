#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>

using namespace std;

//reserved words
string rword[19]=
{"","short","int","float","double","char",//0-5
"if","else","while","for","return",//6-10
"break","continue","define","include","getchar",//11-15
"scanf","printf","main"};//16-18

map<string,int>vars,defs;//int determines type(1-5)
//static var
char ch;string str;

void getchara()
{
	ch=getchar();
	while(ch!=EOF&&(ch==' '||ch=='\n'||ch=='\t'))
		ch=getchar();
}

void getword()
{
	str.clear();
	getchara();
	while(ch!=EOF&&((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')))
	{
		str.push_back(ch);
		ch=getchar();
	}
}

int apply_num()
{
	static int num=0;
	return ++num;
}

int handlefunc(int lastnum);
int handleif(int lastnum);
int handlewhile(int lastnum);
int handlefor(int lastnum);

int main()
{
	//prehandle:define and notes
	freopen("code.c","r",stdin);
	freopen("code_temp.c","w",stdout);//ATENTION:should be code_temp0.c

	ch=getchar();
	while(ch!=EOF)
	{
		if(ch=='"')
		{
			putchar(ch);
			do ch=getchar(),putchar(ch);
			while(ch!='"'&&ch!=EOF);
		}
		else if(ch=='/')
		{
			ch=getchar();
			if(ch=='/')
			{
				do ch=getchar(); 
				while(ch!='\n'&&ch!=EOF);
				if(ch=='\n')putchar(ch);
			}
			else if(ch=='*')
			{
				while(ch!=EOF)
				{
					do ch=getchar(); 
					while(ch!='*'&&ch!=EOF);
					if(ch=='*')
					{
						ch=getchar();
						if(ch=='/')break;
					}
				}
			}
			else putchar('/'),putchar(ch);
		}
		else putchar(ch);
		ch=getchar();
	}

	/* handle define and include
	freopen("code_temp0.c","r",stdin);
	freopen("code_temp.c","w",stdout);

	system("del code_temp0.c");
	*/

	freopen("code_temp.c","r",stdin);
	freopen("temp_1.dot","w",stdout);

	int nownum;
	printf("digraph main{\na%d[label=\"Begin\" shape=\"oval\"]\n",nownum=apply_num());


	int lastnum=/*handlefunc()*/nownum;
	printf("a%d[label=\"End\" shape=\"oval\"]\n",nownum=apply_num());
	printf("a%d->a%d\n}",lastnum,nownum);

	freopen("CON","r",stdin);
	freopen("CON","w",stdout);
	system(".\\Graphviz_2.44.1\\bin\\dot -Tpng temp_1.dot -o Flowchart.png");
	system("del code_temp.c");
	system("del temp_1.dot");
	puts("Finished.");
	system("pause");
	return 0;
}
