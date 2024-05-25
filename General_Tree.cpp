#include<iostream>
using namespace std;

typedef	   	char	Node_Type;

 class G_Tree;   // forward reference

 //********************************************************************
 
class Node
{
public:
	Node();
	Node(Node_Type);

	Node*	Left_Most_Child();

	Node*	Right_Sibling();

	Node_Type	Label_Node_Val();

	void	Set_LM_Child(Node*);
	
	void	Set_RS_Sibling(Node*);

	void	Set_Label_node(Node_Type);

	void	Set_G_T_Address(G_Tree*);

	G_Tree*	G_T_Address_Val();

	void	Print_Label_node();

	void	Preorder();

	void	Postorder();

	 

	~Node();

private:

	Node_Type	Label_node;

	Node*	LM_Child;

	Node*	R_Sibling;

	 G_Tree*	G_T_Address;

};	//class Node

//*********************************************************************

 Node::Node()
{
	LM_Child=NULL;
	R_Sibling=NULL;
	//cout<<endl<<"Node    #"<<this<<"    is constructed";
}

 //*******************************************************************

Node::Node(Node_Type n)
{
	Label_node=n;
	LM_Child=NULL;
	R_Sibling=NULL;

	//cout<<endl<<"Node    #"<<this<<"    is constructed";
}

//*********************************************************************
 
Node*	Node::Left_Most_Child(){

	return	LM_Child;
} 

//*********************************************************************

Node::~Node()
{
	//cout<<endl<<"Node    #"<<this<<"    is Destructed";
}

//********************************************************************

Node*	Node::Right_Sibling(){
	return R_Sibling; }

//*********************************************************************

Node_Type	Node::Label_Node_Val(){
	return Label_node;}

//***********************************************************************

void	Node::Set_LM_Child(Node*  ptr	) {
	LM_Child=ptr;
}

//**************************************************************************

void	Node::Set_RS_Sibling(Node*	ptr){
	R_Sibling=ptr;
}

//**************************************************************************

void	Node::Print_Label_node(){cout<<","<<Label_node;}

//**************************************************************************

void	Node::Set_Label_node(Node_Type r)	{Label_node=r;}

//**************************************************************************

void	Node::Set_G_T_Address(G_Tree* g)	{G_T_Address=g;}

//***************************************************************************

G_Tree*	 Node::G_T_Address_Val()	{return(G_T_Address);}

//**************************************************************************

void	Node::Preorder(){
					Print_Label_node();
			Node*	C=Left_Most_Child();
					while(C!=NULL){
						C->Preorder();
						C=C->Right_Sibling();
					}
}

//************************************************************************

void	Node::Postorder(){
					
			Node*	C=Left_Most_Child();
					while(C!=NULL){
						C->Postorder();
						C=C->Right_Sibling();
					}
					Print_Label_node();
}

//**************************************************************************
 

//**************************************************************************
//			Class   G_Tree
//******************************************************************************

class G_Tree
{
public:
	G_Tree();
	G_Tree(Node_Type);
	void	Create(int,G_Tree**,Node_Type);
	Node*	Root_PTR();
	void	PREORDER();
	void	POSTORDER();
    Node*	PARENT( G_Tree&,const G_Tree&);
	 

	~G_Tree();

private:

	Node	Root;

	 };

//*******************************************************************************

G_Tree::G_Tree()
{
	//Root_Ptr=NULL;	//NUll Tree
	Root_PTR()->Set_G_T_Address(this);

	//cout<<endl<<"G_Tree    #"<<this<<"    is constructed";
}

//*********************************************************************************

G_Tree::G_Tree(Node_Type n) :	Root(n)  
                   {Root_PTR()->Set_G_T_Address(this);
				//cout<<endl<<"G_Tree    #"<<this<<"    is constructed";
}

//******************************************************************************

G_Tree::~G_Tree()
{
	//cout<<endl<<"G_Tree    #"<<this<<"    is Destructed";
}

//******************************************************************************

Node*	G_Tree::Root_PTR(){return	&Root;}

//*****************************************************************************

void	G_Tree::Create(int	n ,G_Tree** G_Tree_Table,Node_Type r)

{
	 	//Root_Ptr= Root_PTR();
		 Root_PTR()->Set_Label_node(r);

	for(int i=n-1;i>0;i--) 
			G_Tree_Table[i-1]->Root_PTR()->Set_RS_Sibling(G_Tree_Table[i]->Root_PTR());

		 Root_PTR()->Set_LM_Child(G_Tree_Table[0]->Root_PTR());

	  
	 
}

//****************************************************************************

void	G_Tree::PREORDER(){

			 cout<<endl<<"PreOrder List :"<<endl<<endl ;
			 Root_PTR()->Preorder();
			 cout<<endl<<endl<<"*****************************************"<<endl;
}

//***************************************************************************

void	G_Tree::POSTORDER(){

			 cout<<endl<<"PostOrder List :"<<endl<<endl;
			 Root_PTR()->Postorder();
			 cout<<endl<<endl<<"************************************"<<endl; 
}

//***************************************************************************
 
Node*	G_Tree::PARENT(G_Tree& N ,const G_Tree& root){ 
	 
	if(&root==&N){
		cout<<endl<<"Root  has not parent";
		return	NULL;
	}

	else{
		   Node*    P=this->Root_PTR();
		   Node*	Rs=this->Root_PTR()->Left_Most_Child();

			while(Rs!=NULL){
				if(Rs!=N.Root_PTR()){ 
					Node*Temp= Rs->G_T_Address_Val()->PARENT(N,root);
					if(Temp != NULL)
						return Temp;
					else
						Rs=Rs->Right_Sibling();
				}
				else
			  	 	return P;
			
			}
	}
	return	NULL;
}

//***************************************************************************
 
void	Parenthood(G_Tree& A,G_Tree& root){
			cout<<endl<<"Parent(";
			A.Root_PTR()->Print_Label_node();
			cout<<")=";
			root.PARENT(A,root)->Print_Label_node();
			cout<<endl;
}

//************************************************************************

void	 Proper_Ancestor_List(G_Tree& N , G_Tree& root){

	 

	cout<<endl<<"proper ancestor list(";N.Root_PTR()->Print_Label_node();
	cout<<"):";
	G_Tree*	p=&N;
	while( p !=&root){
		 root.PARENT(*p,root)->Print_Label_node();
		p=root.PARENT(*p,root)->G_T_Address_Val();

	}
	cout<<endl<<endl;
}

 
 

int main(){

	G_Tree	T21('E');
	G_Tree	T22('H');
	G_Tree	T23('L');
	G_Tree	T2;

	G_Tree*	G_Table1[]={&T21,&T22,&T23};
	T2.Create(3,G_Table1,'B');

	G_Tree	T1('A');
	G_Tree	T3('C');
	G_Tree*	G_table2[]={&T1,&T2,&T3};
	G_Tree	T4;
			T4.Create(3,G_table2,'D');
			
			T4.PREORDER();

			T4.POSTORDER();

			Parenthood(T3,T4);

			Parenthood(T2,T4);

			Parenthood(T22,T4);

			Parenthood(T21,T4);  
			cout<<endl<<endl;

			Proper_Ancestor_List(T21,T4);

		

			return 0;

}