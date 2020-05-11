#include<iostream>
#include<cstring>
#include<math.h>
#include<ctype.h>
#include<stdio.h>

using namespace std;
#define max 30

int i,j,top1 = -1;
char stacks[max][max];


struct stack
{
 int data[max];
 int top;
};

/*------------------------------------------------------------
  CONVERSION FUNCTIONS PROTOTYPE
-------------------------------------------------------------*/

void post_to_in(char[],char[]);                //FUNCTION TO CONVERT POSTFIX TO
void convert_in(char);                        //INFIX EXPRESSION

void pre_to_in(char[],char[]);                 //FUNCTION TO CONVERT PREFIX TO
void convert_infix(char);                     //INFIX EXPRESSION

void pre_to_post(char[],char[]);               //FUNCTION TO CONVERT PREFIX TO
void convert_postfix(char);                    //POSTFIX EXPRESSION

void post_to_pre(char[],char[]);                //FUNCTION TO CONVERT POSTFIX TO
void convert_prefix(char);                           //PREFIX EXPRESSION

void parenthesis_post(char[],char[]);          //FUNCTION TO CONVERT INFIX TO POSTFIX(PARENTHESIS)
void parenthesis_pre(char[],char[]);           //FUNCTION TO CONVERT INFIX TO PREFIX(PARENTHESIS)

/*------------------------------------------------------------
  END OF  FUNCTION PROTOTYPE
--------------------------------------------------------------*/

/*-------------------------------------------------------------
  INITIALIZATION OF TOP
--------------------------------------------------------------*/

void init(stack *s)
{
 s ->top = -1;
}

/*------------------------------------------------------------
  END OF INITIALIZATION
-------------------------------------------------------------*/

/*------------------------------------------------------------
     PUSH AND POP FUNCTIONS
-------------------------------------------------------------*/
int pop(stack *s)
{
 int x;
 x = s ->data[s ->top];
 s ->top = s ->top-1;
 return(x);
}
void push(stack *s,int x)
{
 s ->top = s ->top+1;
 s ->data[s ->top] = x;
}

/*------------------------------------------------------------
  END OF PUSH AND POP
--------------------------------------------------------------*/

/*------------------------------------------------------------
  FUNCTION FOR EVALUATION OF POSTFIX AND PREFIX EXPRESSION
--------------------------------------------------------------*/
int evaluate(char x,int op1,int op2)
{
 if(x == '+') return(op1 + op2);
 if(x == '-') return(op1 - op2);
 if(x == '*') return(op1 * op2);
 if(x == '/') return(op1 / op2);
 if(x == '%') return(op1 % op2);
 if(x == '^') return(pow(op1,op2));
}

void eval_pre(char exp[])
{
 stack s;
 char x;
 int op1,op2,val;
 init(&s);
 for(i = strlen(exp) - 1;i >= 0;i --)
 {
  x = exp[i];
  if(isalpha(x))
  {
   cout<<"\nEnter the value of "<<x<<":";
   cin>>val;
   push(&s,val);
  }
  else
  {
   op1 = pop(&s);
   op2 = pop(&s);
   val = evaluate(x,op1,op2);
   push(&s,val);
  }
 }
  val = pop(&s);
  cout<<"\nValue of Expression="<<val;
}

void eval_post(char exp[])
{
 stack s;
 char x;
 int op1,op2,val;
 init(&s);
 for(i = 0;i < strlen(exp);i ++)
 {
  x = exp[i];
  if(isalpha(x))
  {
   cout<<"\nEnter the value of "<<x<<":";
   cin>>val;
   push(&s,val);
  }
  else
  {
   op2 = pop(&s);
   op1 = pop(&s);
   val = evaluate(x,op1,op2);
   push(&s,val);
  }
 }
  val = pop(&s);
  cout<<"\nValue of Expression="<<val;
}
/*------------------------------------------------------------
 END OF EVALUATION FUNCTION
--------------------------------------------------------------*/

/*------------------------------------------------------------
 FUNCTION FOR CONVERSIONS OF EXPRESSIONS
--------------------------------------------------------------*/

void conversion()
{
 char ans; int ch;
 char in[30],post[30],pre[30];
 do
 {
  cout<<"\n**Conversion Menu**";
  cout<<"\n1.Infix to Postfix(Including Fully Parenthiesis).\n2.Infix to Prefix(Including Full Parenthesis)."
       <<"\n3.Postfix to Infix.\n4.Postfix to Prefix."
      <<"\n5.Prefix to Infix.\n6.Prefix to Postfix.";
  cout<<"\nEnter choice:";
  cin>>ch;
  switch(ch)
  {
   case 1:
	   cin.ignore();
	   cout<<"\nEnter Expression:";
	   cin>>in;
	   parenthesis_post(in,post);
	   break;
   case 2:
	   cin.ignore();
	   cout<<"\nEnter Expresssion:";
	   cin>>in;
	   parenthesis_pre(in,pre);
	   break;
   case 3:
	   cin.ignore();
	   cout<<"\nEnter Expression:";
	   cin>>post;
	   post_to_in(post,in);
	   break;
   case 4:
	   cin.ignore();
	   cout<<"\nEnter Expression:";
	   cin>>post;
	   post_to_pre(post,pre);
	   break;
   case 5:
	   cin.ignore();
	   cout<<"\nEnter Expression:";
	   cin>>pre;
	   pre_to_in(pre,in);
	   break;
   case 6:
	   cin.ignore();
	   cout<<"\nEnter Expression:";
	   cin>>pre;
	   pre_to_post(pre,post);
	   break;
    default: cout<<"\nINVALID CHOICE!!!!!!!!!";
  }
  cout<<"\nWant to Continue in Conversion Menu(y/n):";
  cin>>ans;
 }while(ans == 'y' || ans == 'Y');
}

/*------------------------------------------------------------
  FUNCTION TO CONVERT INFIX TO POSTFIX(PARENTHESIS)
--------------------------------------------------------------*/

void parenthesis_post(char in[],char post[])
{
 stack s;
 char x,tok;
 init(&s);
 j = 0;
 for(i = 0;in[i] != '\0';i ++)
 {
  tok = in[i];
  if(isalnum(tok))
    post[j++] = tok;
  else if(tok == ')')
    post[j++] = pop(&s);
  else if(tok != '(')
    push(&s,tok);
 }
 post[j] = '\0';
 cout<<"\nPostfix Expression:"<<post;
}

/*------------------------------------------------------------
  END OF FUNCTION
--------------------------------------------------------------*/

/*------------------------------------------------------------
 FUNCTION TO CONVERT INFIX TO PREFIX(PARENTHESIS)
--------------------------------------------------------------*/

void parenthesis_pre(char in[],char pre[])
{
 stack s,s1;
 char x,tok;
 init(&s); init(&s1);
 j = 0;
 for(i = strlen(in) - 1;i >= 0;i --)
 {
  tok = in[i];
  if(isalnum(tok))
     push(&s1,tok);
  else if(tok == '(')
   { x = pop(&s); push(&s1,x); }
  else if(tok != ')')
   push(&s,tok);
 }
 while(s1.top != -1)
  { pre[j++] = pop(&s1); }
 pre[j] = '\0';
 cout<<"\nPrefix Expression:"<<pre;
}

/*------------------------------------------------------------
  END OF FUNCTION
--------------------------------------------------------------*/

/*------------------------------------------------------------
  FUNCTION TO CONVERT POSTFIX TO PREFIX EXPRESSION
--------------------------------------------------------------*/

void post_to_pre(char post[],char pre[])
{
 char x,str1[30];
 for(i = 0;i < strlen(post);i ++)
 {
  x = post[i];
  if(isalnum(x))
  {
   str1[0] = x;
   str1[1] = '\0';
   top1 = top1 + 1;
   strcpy(stacks[top1],str1);
  }
  else
    convert_prefix(x);
 }
 strcpy(pre,stacks[top1]);
 cout<<"\nPrefix Expression:"<<pre;
}
void convert_prefix(char x)
{
 char str1[30];
 str1[0] = x;
 str1[1] = '\0';
 strcat(str1,stacks[top1 - 1]);
 strcat(str1,stacks[top1]);
 top1 = top1-1;
 strcpy(stacks[top1],str1);
}

/*------------------------------------------------------------
  END OF FUNCTION
--------------------------------------------------------------*/

/*------------------------------------------------------------
  FUNCTION TO CONVERT PREFIX TO POSTFIX EXPRESSION
--------------------------------------------------------------*/

void pre_to_post(char pre[],char post[])
{
 char x,str1[30];
 for(i = strlen(pre) -1;i >= 0;i --)
 {
  x = pre[i];
  if(isalnum(x))
  {
   str1[0] = x;
   str1[1] = '\0';
   top1 = top1+1;
   strcpy(stacks[top1],str1);
  }
  else
    convert_postfix(x);
 }
 strcpy(post,stacks[top1]);
 cout<<"\nPostfix Expression:"<<post;
}
void convert_postfix(char x)
{
 char str1[30],str2[30];
 str2[0] = x;
 str2[1] = '\0';
 strcpy(str1,stacks[top1]);
 strcat(str1,stacks[top1 - 1]);
 strcat(str1,str2);
 top1 = top1-1;
 strcpy(stacks[top1],str1);
}

/*------------------------------------------------------------
  END OF FUNCTION
--------------------------------------------------------------*/

/*------------------------------------------------------------
  FUNCTION TO CONVERT POSTFIX TO INTFIX EXPRESSION
--------------------------------------------------------------*/

void post_to_in(char post[],char in[])
{
 char x,str1[30];
 for(i = 0;post[i] != '\0';i ++)
 {
  x = post[i];
  if(isalnum(x))
  {
   str1[0] = x;
   str1[1] = '\0';
   top1 = top1+1;
   strcpy(stacks[top1],str1);
  }
  else
    convert_in(x);
 }
 strcpy(in,stacks[top1]);
 cout<<"\nInfix Expression:"<<in;
}
void convert_in(char x)
{
 char str1[30],str2[30];
 str1[0] = '(';
 str1[1] = '\0';
 strcat(str1,stacks[top1 - 1]);
 str2[0] = x;
 str2[1] = '\0';
 strcat(str1,str2);
 strcat(str1,stacks[top1]);
 str2[0] = ')';
 str2[1] = '\0';
 strcat(str1,str2);
 top1 = top1-1;
 strcpy(stacks[top1],str1);
}

/*------------------------------------------------------------
  END OF FUNCTION
--------------------------------------------------------------*/

/*------------------------------------------------------------
  FUNCTION TO CONVERT PREFIX TO INTFIX EXPRESSION
--------------------------------------------------------------*/

void pre_to_in(char pre[],char in[])
{
 char x,str1[30];
 for(i = strlen(pre) -1;i >= 0;i --)
 {
  x = pre[i];
  if(isalnum(x))
  {
   str1[0] = x;
   str1[1] = '\0';
   top1 = top1+1;
   strcpy(stacks[top1],str1);
  }
  else
    convert_infix(x);
 }
 strcpy(in,stacks[top1]);
 cout<<"\nInfix Expression:"<<in;
}
void convert_infix(char x)
{
 char str1[30],str2[30];
 str1[0] = '(';
 str1[1] = '\0';
 strcat(str1,stacks[top1]);
 str2[0] = x;
 str2[1] = '\0';
 strcat(str1,str2);
 strcat(str1,stacks[top1 - 1]);
 str2[0] = ')';
 str2[1] = '\0';
 strcat(str1,str2);
 top1 = top1-1;
 strcpy(stacks[top1],str1);
}

/*------------------------------------------------------------
  END OF FUNCTION
--------------------------------------------------------------*/

/*------------------------------------------------------------
  END OF CONVERSION FUNCTIONS
--------------------------------------------------------------*/

/*------------------------------------------------------------
  MAIN FUNCTION
--------------------------------------------------------------*/

int main()
{

 int op1,op2,ch;
 char exp[40],x,ans;
 do
 {
  cout<<"\n****STACK APPLICATION****";
  cout<<"\n\n---->MENU<----";
  cout<<"\n1.Evaluation of postfix Expression.\n2.Evaluation of prefix Expression.\n3.Conversions";
  cout<<"\nEnter choice:";

  cin>>ch;
  switch(ch)
  {
   case 1:
	   cin.ignore();
	   cout<<"\nEnter the Expression:";
	   cin>>exp;
	   eval_post(exp);
	   break;
   case 2:
	   cin.ignore();
	   cout<<"\nEnter the Expression:";
	   cin>>exp;
	   eval_pre(exp);
	   break;
   case 3: conversion();
	   break;
    default: cout<<"\nINVALID CHOICE!!!!!!!!!";
  }
  cout<<"\nWant to Continue in Main Menu(y/n):";
  cin>>ans;
 }while(ans == 'y' || ans == 'Y');
 return 0;
}
/*------------------------------------------------------------
  END OF MAIN FUNCTION
--------------------------------------------------------------*/

