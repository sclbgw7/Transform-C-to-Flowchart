#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <stack>

using namespace std;

//reserved words
string rword[20]=
{"","short","int","float","double","char",//0-5
"if","else","while","for","return",//6-10
"break","continue","define","include","getchar",//11-15
"scanf","printf","main"};//16-18

map<string,int>vars,defs;//int determines type(1-5)
//static var
char ch;string str,yorn;

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
	ch=getchar();
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
	str.clear();
	int flag=1;
	if(ch=='(')++flag;
	if(ch==')')--flag;
	while(ch!=EOF&&flag&&ch!=';')
	{
		str.push_back(ch);
		ch=getchar();
		if(ch=='(')++flag;
		if(ch==')')--flag;
	}
}

void getpara_noand()
{
	str.clear();
	int flag=1;
	if(ch=='(')++flag;
	if(ch==')')--flag;
	while(ch!=EOF&&flag&&ch!=')')
	{
		if(ch!='&')str.push_back(ch);
		ch=getchar();
		if(ch=='(')++flag;
		if(ch==')')--flag;
	}
}

int apply_num()
{
	static int num=0;
	return ++num;
}

void link(int a,int b)
{
	if(a==114514)return;
	printf("a%d->a%d[label=\"%s\"]\n",a,b,yorn.c_str());
	yorn.clear();
}

int handlesent(int lastnum);
int handlefunc(int lastnum);
int handleif(int lastnum);
int handlewhile(int lastnum);
int handlefor(int lastnum);
int handleelse(int lastnum);
int endif();

int isif=0;
stack<int>whead,wtail;
int handlesent(int lastnum)
{
	getword();
	for(int i=1;i<=5;i++)
	{
		if(str==rword[i])
		{
			str.clear();
			getchara();
			getsent();
			int now=apply_num();
			printf("a%d[label=\"Declaration\\n%s:%s\" shape=\"box\"]\n",now,str.c_str(),rword[i].c_str());
			link(lastnum,now);
			return now;
		}
	}
	if(str==rword[6])
		return handleif(lastnum);
	else if(str==rword[7])
		return handleelse(lastnum);
	else if(isif)lastnum=endif();
	if(str==rword[8])
		return handlewhile(lastnum);
	else if(str==rword[9])
		return handlefor(lastnum);
	else if(str==rword[11])//break
	{
		if(ch!=';')getchara();
		link(lastnum,wtail.top());
		return 114514;
	}
	else if(str==rword[12])//continue
	{
		if(ch!=';')getchara();
		link(lastnum,whead.top());
		return 114514;
	}
	else if(str==rword[16])
	{
		int now;
		do getchara();while(ch!='"');
		do getchara();while(ch!='"');
		getchara();getchara();
		getpara_noand();
		getchara();
		printf("a%d[label=\"Input %s\" shape=\"parallelogram\"]\n",now=apply_num(),str.c_str());
		link(lastnum,now);
		return now;
	}
	else if(str==rword[17])
	{
		int now;
		do getchara();while(ch!='"');
		do getchara();while(ch!='"');
		getchara();getchara();
		getpara();
		getchara();
		printf("a%d[label=\"Print %s\" shape=\"parallelogram\"]\n",now=apply_num(),str.c_str());
		link(lastnum,now);
		return now;
	}
	else
	{
		int now;
		getsent();
		printf("a%d[label=\"%s\" shape=\"box\"]\n",now=apply_num(),str.c_str());
		link(lastnum,now);
		return now;
	}
}

int handlefunc(int lastnum)
{
	int now=lastnum;
	getchara();
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
	if(isif)return endif();
	return now;
}

stack<int> lastif,lastend;
int handleif(int lastnum)
{
	int now=apply_num();
	if(ch==' ')getchara();
	getchara();
	getpara();
	printf("a%d[label=\"%s ?\" shape=\"diamond\"]\n",now,str.c_str());
	link(lastnum,now);
	yorn="Y";
	lastif.push(now);
	now=handlefunc(now);
	if(now!=114514)
	{
		lastend.push(apply_num());
		printf("a%d[shape=\"point\"]\n",lastend.top());
		link(now,lastend.top());
		isif=1;
		return lastend.top();
	}
	isif=1;
	lastend.push(114514);
	return 114514;
}

int handleelse(int lastnum)
{
	isif=0;
	yorn="N";
	int now=handlefunc(lastif.top()),le=lastend.top();
	if(le!=114514)link(now,le);
	lastif.pop();lastend.pop();
	return le;
}

int endif()
{
	isif=0;
	yorn="N";
	int le=lastend.top();
	if(le==114514)
	{
		le=apply_num();
		printf("a%d[shape=\"point\"]\n",le);
	}
	link(lastif.top(),le);
	lastif.pop();lastend.pop();
	return le;
}

int handlewhile(int lastnum)
{
	int now=apply_num(),lastwhile=now,tail=apply_num();
	printf("a%d[shape=\"point\"]\n",now);
	printf("a%d[shape=\"point\"]\n",tail);
	whead.push(now);
	wtail.push(tail);
	link(lastnum,now);
	printf("subgraph cluster_while_%d{\nlabel=\"while\"\ncolor=green\n",now);
	now=apply_num();
	int para=now;
	if(ch==' ')getchara();
	getchara();
	getpara();
	printf("a%d[label=\"%s ?\" shape=\"diamond\"]\n",now,str.c_str());
	link(lastwhile,now);
	yorn="Y";
	now=handlefunc(now);
	link(now,lastwhile);
	puts("}");
	yorn="N";
	link(para,tail);
	whead.pop();
	wtail.pop();
	return tail;
}

int handlefor(int lastnum)
{
	int now=apply_num(),isdec=0,tail=apply_num();
	if(ch=='(')getchara();
	getword();
	for(int i=1;i<=5;i++)
	{
		if(str==rword[i])
		{
			str.clear();
			getchara();
			getsent();
			printf("a%d[label=\"Declaration\\n%s:%s\" shape=\"box\"]\n",now,str.c_str(),rword[i].c_str());
			link(lastnum,now);
			isdec=1;
			break;
		}
	}
	if(!isdec)
	{
		getsent();
		printf("a%d[label=\"%s\" shape=\"box\"]\n",now,str.c_str());
		link(lastnum,now);
	}
	printf("subgraph cluster_while_%d{\nlabel=\"for\"\ncolor=blue\n",now);
	str.clear();
	getchara();getsent();
	lastnum=now,now=apply_num();
	printf("a%d[shape=\"point\"]\n",now);
	printf("a%d[shape=\"point\"]\n",tail);
	wtail.push(tail);
	int poi=now;
	link(lastnum,now);
	lastnum=now,now=apply_num();
	printf("a%d[label=\"%s ?\" shape=\"diamond\"]\n",now,str.c_str());
	int para=now;
	link(lastnum,now);
	lastnum=now,now=apply_num();
	getchara();getpara();
	printf("a%d[label=\"%s\" shape=\"box\"]\n",now,str.c_str());
	int last=now;
	link(last,poi);
	now=apply_num();
	printf("a%d[shape=\"point\"]\n",now);
	link(now,last);
	whead.push(now);
	yorn="Y";
	now=handlefunc(para);
	link(now,whead.top());
	puts("}");
	yorn="N";
	link(para,tail);
	whead.pop();
	wtail.pop();
	return tail;
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

	while(ch!=')')getchara();
	int lastnum=handlefunc(now);
	printf("a%d[label=\"End\" shape=\"oval\"]\n",now=apply_num());
	link(lastnum,now);puts("}");

	freopen("CON","r",stdin);
	freopen("CON","w",stdout);
	system(".\\Graphviz_2.44.1\\bin\\dot -Tpng temp_1.dot -o Flowchart.png");
	system("del code_temp.c");
	system("del temp_1.dot");
	puts("Finished.");
	system("pause");
	return 0;
}
