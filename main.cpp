#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>

using namespace std;

//reserved words
string rword[20]=
{"","short","int","float","double","char",//0-5
"if","else","while","for","return",//6-10
"break","continue","define","include","getchar",//11-15
"scanf","printf","main"};//16-18

map<string,int>vars,defs;//int determines type(1-5)
//static var
char ch;string str;

/*
getchara();if(not '{')getword();if(not rwords)getsent();
*/
void getchara()
{
	ch=getchar();
	while(ch!=EOF&&(ch==' '||ch=='\n'||ch=='\t'))
		ch=getchar();
}

void getword()
{
	str.clear();
	str.push_back(ch);
	getchara();
	while(ch!=EOF&&((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')))
	{
		str.push_back(ch);
		ch=getchar();
	}
}

void getsent()
{
	while(ch!=EOF&&ch!='\n'&&ch!=';')
	{
		str.push_back(ch);
		ch=getchar();
	}
}

void getpara()
{
	while(ch!=EOF&&ch!=')')
	{
		str.push_back(ch);
		ch=getchar();
	}
}

void getpara_noand()
{
	while(ch!=EOF&&ch!=')')
	{
		if(ch!='&')str.push_back(ch);
		ch=getchar();
	}
}

int apply_num()
{
	static int num=0;
	return ++num;
}

int handlesent(int lastnum);
int handlefunc(int lastnum);
int handleif(int lastnum);
int handlewhile(int lastnum);
int handlefor(int lastnum);

int handlesent(int lastnum)
{
	getword();
	/*if(str==rword[6])
		return handleif(lastnum);
	else if(str==rword[8])
		return handlewhile(lastnum);
	else if(str==rword[9])
		return handlefor(lastnum);
	else*/if(str==rword[16])
	{
		int now;
		do ch=getchar();while(ch!='"');
		do ch=getchar();while(ch!='"');
		getchara();getchara();str.clear();
		getpara_noand();
		printf("a%d[label=\"Input\n%s\" shape=\"box\"]\n",now=apply_num(),str.c_str());
		printf("a%d->a%d\n",lastnum,now);
		return now;
	}
	else if(str==rword[17])
	{
		int now;
		do ch=getchar();while(ch!='"');
		do ch=getchar();while(ch!='"');
		getchara();getchara();str.clear();
		getpara_noand();
		printf("a%d[label=\"Print\n%s\" shape=\"box\"]\n",now=apply_num(),str.c_str());
		printf("a%d->a%d\n",lastnum,now);
		return now;
	}
	else
	{
		int now;
		getsent();
		printf("a%d[label=\"%s\" shape=\"box\"]\n",now=apply_num(),str.c_str());
		printf("a%d->a%d\n",lastnum,now);
		return now;
	}
}

int handlefunc(int lastnum)
{
	int now=lastnum;
	if(ch!='{')
		now=handlesent(now);
	else
	{
		getchara();
		while(ch!='}')
		{
			now=handlesent(now);
			getchara();
		}
	}
	return now;
}

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
			putchar('\\'),putchar(ch);
			ch=getchar();
			while(ch!='"'&&ch!=EOF)
				putchar(ch),ch=getchar();
			if(ch=='"')putchar('\\'),putchar(ch);
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

	int now;
	printf("digraph main{\na%d[label=\"Begin\" shape=\"oval\"]\n",now=apply_num());

	while(ch!='{')getchara();
	int lastnum=handlefunc(now);
	printf("a%d[label=\"End\" shape=\"oval\"]\n",now=apply_num());
	printf("a%d->a%d\n}",lastnum,now);

	freopen("CON","r",stdin);
	freopen("CON","w",stdout);
	system(".\\Graphviz_2.44.1\\bin\\dot -Tpng temp_1.dot -o Flowchart.png");
	//system("del code_temp.c");
	//system("del temp_1.dot");
	puts("Finished.");
	system("pause");
	return 0;
}
