%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 500
char *storeData[MAX_SIZE];
int ind = 0;
int indFinal = 0;
int ci = 0;
typedef struct node{
   char *nodeName;
   struct node *prev;
   struct node *left;
   struct node *middle;
   struct node  *right;
   char *leftName, *middleName, *rightName, *finalName;
}node;
node *root;
int connectNode(node *parents){
   if(ci==0){
      root = parents;
      printf("root is : %s\n", root->nodeName);
   }

   if(!strcmp(parents->nodeName, "INT")){
      node *childRight = (node*)malloc(sizeof(node));
      parents->right = childRight;
      childRight->prev = parents;
      childRight->nodeName = (char*)malloc(sizeof(char)*strlen(parents->prev->finalName)+1);
      strcpy(childRight->nodeName, parents->prev->finalName);
      }
   if(!strcmp(parents->nodeName, "DOUBLE")){
      node *childRight = (node*)malloc(sizeof(node));
      parents->right = childRight;
      childRight->prev = parents;
      childRight->nodeName = (char*)malloc(sizeof(char)*strlen(parents->prev->finalName)+1);
      strcpy(childRight->nodeName, parents->prev->finalName);
   }
   if(!strcmp(parents->nodeName, "STRING")){
      node *childRight = (node*)malloc(sizeof(node));
      parents->right = childRight;
      childRight->prev = parents;
      childRight->nodeName = (char*)malloc(sizeof(char)*strlen(parents->prev->finalName)+1);

      strcpy(childRight->nodeName, parents->prev->finalName);
   }

  if(ci==indFinal)
      return 0;
   
   if(!strcmp(parents->nodeName, storeData[ci])){
   parents->leftName = (char*)malloc(sizeof(char)*strlen(storeData[ci+1])+1);
   parents->middleName = (char*)malloc(sizeof(char)*strlen(storeData[ci+2])+1);
   parents->rightName = (char*)malloc(sizeof(char)*strlen(storeData[ci+3])+1);
   parents->finalName = (char*)malloc(sizeof(char)*strlen(storeData[ci+4])+1);
   strcpy(parents->leftName, storeData[ci+1]);
   strcpy(parents->middleName, storeData[ci+2]);
   strcpy(parents->rightName, storeData[ci+3]);
   strcpy(parents->finalName, storeData[ci+4]);
   //printf("finalName is %s\n", parents->finalName);
   node *childRight = (node*)malloc(sizeof(node));
   node *childMiddle = (node*)malloc(sizeof(node));
   node *childLeft = (node*)malloc(sizeof(node));
   parents->right = childRight;
   childRight->prev = parents;
   parents->middle = childMiddle;
   childMiddle->prev = parents;
   parents->left = childLeft;
   childLeft->prev = parents;
   childLeft->nodeName = (char*)malloc(sizeof(char)*strlen(storeData[ci+1])+1);
   childMiddle->nodeName = (char*)malloc(sizeof(char)*strlen(storeData[ci+2])+1);
   childRight->nodeName = (char*)malloc(sizeof(char)*strlen(storeData[ci+3])+1);
   strcpy(childRight->nodeName, parents->rightName);
   strcpy(childMiddle->nodeName, parents->middleName);
   strcpy(childLeft->nodeName, parents->leftName);
   //printf("childRightName is %s\n", childRight->nodeName);
   //printf("childMiddleName is %s\n", childMiddle->nodeName);
   //printf("childLeftName is %s\n", childLeft->nodeName);
   ci += 5;
   //printf("%d\n", ci);
   connectNode(childRight);
   connectNode(childMiddle);
   connectNode(childLeft);
   return 0;
   }
   else{
      //printf("not Same\n");
      return 0;
   }
}

int printNode(int space, node *parents){
   if(parents == NULL)
      return 0;
   
   int i;
   if(strcmp(parents->nodeName, "NULL")){
      for(i=0; i<space; i++)
      printf(" ");
      space+=7;
      printf("| %s\n", parents->nodeName);
   }   
   printNode(space, parents->right);
   printNode(space, parents->middle);
   printNode(space, parents->left);
   return 0;
}

int findNameString(node *parents, char *find){
   	if(!strcmp(parents->nodeName, &find)){
	   //printf("Correct!!!\n");
	   //printf("it is %s\n", parents->prev->prev->prev->right->left->right->nodeName);
		node * temp = parents;
	//printf("temp is %s\n", temp->nodeName); 
		temp = parents->prev->prev->prev->right->left->right;
	//printf("temp is %s\n", temp->nodeName); 
	  	 printf("%s : %s\n", &find, temp->nodeName);
	  	 return 0;
	}
	//printf("gogogo\n");
	if(parents->right != NULL)
		findNameString(parents->right, find);
	if(parents->middle != NULL)
		findNameString(parents->middle, find);
	if(parents->left != NULL)
		findNameString(parents->left, find);
	return 0;
}

int changeNameString(node *parents, char *find, char *change){
	if(!strcmp(parents->nodeName, &find)){
		printf("success\n");
		node * temp;
		temp = parents->prev->prev->prev->right->left->right;
		printf("Original->%s : %s\n", &find, temp->nodeName);
		strcpy(temp->nodeName, &change);
		printf("After Change->%s : %s\n", &find, temp->nodeName);
		return 0;
	}
	if(parents->right != NULL)
		changeNameString(parents->right, find, change);
	if(parents->middle != NULL)
		changeNameString(parents->middle, find, change);
	if(parents->left != NULL)
		changeNameString(parents->left, find, change);
	return 0;
}
int printJson(node *parents){
	if(!strcmp(parents->nodeName, "STRING") || !strcmp(parents->nodeName, "INT") || !strcmp(parents->nodeName, "DOUBLE")){
		printf("%s ", parents->right->nodeName);
		return 0;
	}
	else if(!strcmp(parents->nodeName, "LBRACE")){
		printf("{\n");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "RBRACE")){
		printf("}\n");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "LBRACKET")){
		printf("[\n");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "RBRACKET")){
		printf("]\n");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "COLON")){
		printf(": ");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "COMMA")){
		printf(",\n");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "TRUE")){
		printf("true ");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "FALSE")){
		printf("false ");
		return 0;
	}
	else if(!strcmp(parents->nodeName, "TNULL")){
		printf("null ");
		return 0;
	}

	if(parents->left != NULL)
		printJson(parents->left);
	if(parents->middle != NULL)
		printJson(parents->middle);
	if(parents->right != NULL)
		printJson(parents->right);
	return 0;
}

%}

%union {   
      int i;
      double d;
   char str[100];
}
%token INT DOUBLE LBRACE RBRACE LBRACKET RBRACKET COLON COMMA TRUE FALSE TNULL STRING
%%
object:   LBRACE RBRACE 
{
   printf("object -> LBRACE + RBRACE\n");
   storeData[ind++] = "object";
   storeData[ind++] = "LBRACE";
   storeData[ind++] = "RBRACE";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
}
| LBRACE members RBRACE 
{
   printf("object -> LBRACE + members + RBRACE\n");
   storeData[ind++] = "object";
   storeData[ind++] = "LBRACE";
   storeData[ind++] = "members";
   storeData[ind++] = "RBRACE";
   storeData[ind++] = "NULL";
};


members:pair 
{
   printf("members -> pair\n");
   storeData[ind++] = "members";
   storeData[ind++] = "pair";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";

}
   | pair COMMA members 
{
   printf("members -> pair + COMMA + members\n");
   storeData[ind++] = "members";
   storeData[ind++] = "pair";
   storeData[ind++] = "COMMA";
   storeData[ind++] = "members";
   storeData[ind++] = "NULL";
};

pair:   namestring COLON value 
{
   printf("pair -> namestring + COLON + value\n");
   storeData[ind++] = "pair";
   storeData[ind++] = "namestring";
   storeData[ind++] = "COLON";
   storeData[ind++] = "value";
   storeData[ind++] = "NULL";
};

array:   LBRACKET RBRACKET 
{   
   printf("array -> LBRACKET + RBRACKET\n");
   storeData[ind++] = "array";
   storeData[ind++] = "LBRACKET";
   storeData[ind++] = "RBRACKET";
   storeData[ind++] = NULL;
   storeData[ind++] = NULL;

}
   | LBRACKET elements RBRACKET 
{
   printf("array -> LBRACKET + elements + RBRACKET\n");
   storeData[ind++] = "array";
   storeData[ind++] = "LBRACKET";
   storeData[ind++] = "elements";
   storeData[ind++] = "RBRACKET";
   storeData[ind++] = "NULL";
};

elements: value 
{
   printf("elements -> value\n");
   storeData[ind++] = "elements";
   storeData[ind++] = "value";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
}
   | value COMMA elements 
{
   printf("elements -> value + COMMA + elements\n");
   storeData[ind++] = "elements";
   storeData[ind++] = "value";
   storeData[ind++] = "COMMA";
   storeData[ind++] = "elements";
   storeData[ind++] = "NULL";
};
value: STRING 
{
   printf("value -> STRING : %s\n", yylval.str);
   storeData[ind++] = "value";
   storeData[ind++] = "STRING";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind] = (char*)malloc(sizeof(char)*strlen(yylval.str)+1);
   strcpy(storeData[ind++], yylval.str);
}
   | INT 
{
   printf("value -> INT : %s\n", yylval.str);
   storeData[ind++] = "value";
   storeData[ind++] = "INT";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind] = (char*)malloc(sizeof(char)*strlen(yylval.str)+1);
   strcpy(storeData[ind++], yylval.str);

}
   | DOUBLE 
{
   printf("value -> DOUBLE : %s\n", yylval.str);
   storeData[ind++] = "value";
   storeData[ind++] = "DOUBLE";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind] = (char*)malloc(sizeof(char)*strlen(yylval.str)+1);
   strcpy(storeData[ind++], yylval.str);

}
   | object 
{
   printf("value ->  object\n");
   storeData[ind++] = "value";
   storeData[ind++] = "object";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
}
   | array 
{
   printf("value -> array\n");
   storeData[ind++] = "value";
   storeData[ind++] = "array";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";

}
   | TRUE 
{
   printf("value -> TRUE\n");
   storeData[ind++] = "value";
   storeData[ind++] = "TRUE";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";

}
   | FALSE 
{
   printf("value -> FALSE\n");
   storeData[ind++] = "value";
   storeData[ind++] = "FALSE";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
}
   | TNULL 
{
   printf("value -> NULL\n");
   storeData[ind++] = "value";
   storeData[ind++] = "TNULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";

};

namestring: STRING
{
   printf("namestring -> STRING : %s\n", yylval.str);
   storeData[ind++] = "namestring";
   storeData[ind++] = "STRING";
   storeData[ind++] = "NULL";
   storeData[ind++] = "NULL";
   storeData[ind] = (char*)malloc(sizeof(char)*strlen(yylval.str)+1);
   strcpy(storeData[ind++], yylval.str);
}


%%

main()
{
   yyparse();
   printf("Exit yypars()\n");
   printf("---------------------Show Table--------------------\n");
   int i , j, k, num;
   char *temp = NULL;

   for(i = 0; i < MAX_SIZE;){
      if(storeData[i] == NULL)
         break;
      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("\n");
   }

               /* reverse Table */
   //printf("Start Test!!\n");
   indFinal = ind;
   num = ind / 5 / 2;
   //printf("num : %d " , num);
   for(i = 0, j = 0; i < num; i++){
      ind -= 5;
      for(k = 0; k < 5; k++){
         temp = (char*)malloc(sizeof(char)*strlen(storeData[j])+1);
         strcpy(temp, storeData[j]);
         storeData[j] = storeData[ind];
         storeData[ind] = temp;
         j++;
         ind++;
      }
      ind -= 5;
   }

printf("\n\n-------------Reverse Table--------------------\n\n");
   for(i = 0; i < MAX_SIZE;){
      if(storeData[i] == NULL)
         break;

      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("%s ", storeData[i++]);
      printf("\n");
   }
// 여기서부터 노드 동적할당하면됨 몇개? num*2개만큼
//int lastNode = num * 2;
//node *Node = (node*)malloc(sizeof(node)*lastNode);
//Node[0].nodeName = (char*)malloc(sizeof(char)*strlen(storeData[0])+1);
//strcpy(Node[0].nodeName, storeData[0]);
// Node[0].nodeName = storeData[0];
// node *head = &Node[0];
//printf("%s\n", head->nodeName);
node *head;
head = (node*)malloc(sizeof(node));
head->nodeName = (char*)malloc(sizeof(char)*strlen(storeData[0])+1);
strcpy(head->nodeName, storeData[0]);
//printf("Before in Func\n");
//printf("indFinal is : %d\n", indFinal);
connectNode(head);
printf("\n\n---------------------------------\n\n");
printf("root is : %s\n\n", root->nodeName);
printNode(0, root);
int menu;
char *find;
char *change;
	while(1){
	printf("------------------------------------------------------\n");
		printf("Menu\n");
		printf("1. Print Parse Tree \n"); 
		printf("2. JSON file value print\n");
		printf("3. JSON file value modify\n");
		printf("4. JSON file show print\n");
		printf("5. EXIT Program\n");
		printf("Select Menu.\n");
		scanf("%d", &menu);
		switch(menu){
			case 1:
				printf("You select 1 number menu\n");
	printf("------------------------------------------------------\n");
				printNode(0, root);
				break;
			case 2:
				printf("You select 2 number in menu\n");
	printf("------------------------------------------------------\n");
				printf("Enter value you want to find\n");
				find = (char*)malloc(sizeof(char)*100);
				scanf("%s", &find);
				//printf("find is : %s\n", &find);
				findNameString(root, find);
				break;
			case 3:
				printf("You select 3 number in menu\n");
	printf("------------------------------------------------------\n");
				printf("Enter value you want to find\n");
				find = (char*)malloc(sizeof(char)*100);
				scanf("%s", &find);
				printf("Enter value you want to change\n");
				change = (char*)malloc(sizeof(char)*100);
				scanf("%s", &change);
				changeNameString(root, find, change);
				break;
			case 4:
				printf("You select 4 number in menu\n");
	printf("------------------------------------------------------\n");
				printJson(root);
				break;
			case 5:
				printf("You select 5 number in menu\n");
				printf("EXIT Program.\n");
				exit(1);
			default:
				printf("Enter Only 1~5\n");
		}
	}
}