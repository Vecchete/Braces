#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct stack{
    char reg;
    struct stack* next;
}Stack;

Stack* Free_Reg = NULL;

Stack * AlocaStack(char reg)//aloca o nó da pilha
{
	Stack* aux = (Stack*) malloc(sizeof(Stack));
	aux->reg = reg;
	aux->next = NULL;
	return aux;
}

void Push_Stack(char reg)//empilha
{
	Stack* aux = AlocaStack(reg);
	Stack * p;
	p = Free_Reg;
	if(p == NULL){
		p = aux;
	}else{
		while(p->next!= NULL){
			p = p->next;
		}
		p->next = aux;
	}
}


int Verifica_Stack()//verifica se está vazia
{
	Stack * p;
	p = Free_Reg;
	if(p == NULL){
		return 0;
    }else{
    	return 1;
    }
}

char Pop_Stack()//desempilha
{
	char temp;
	Stack * p;
	p = Free_Reg;
	if(p == NULL){
		return 0;
	}else{
		while(p->next!= NULL){
			p = p->next;
		}
		temp = p->reg;
		p = NULL;
		return temp;
	}
}

char Peek_Stack()//ultimo nó
{
	int temp;
	Stack * p;
	p = Free_Reg;
	if(p == NULL){
		return 0;
	}else{
		while(p->next!= NULL){
			p = p->next;
		}
		temp = p->reg;
		return p->reg;
	}
}

void Clear_Stack()//limpa a pilha
{
	Free_Reg = NULL;
}

int verify_string(char * string, int size){
    for(int i = 0; i<size;i++){
        char c =  Peek_Stack();
        if (string[i] == '('){
        	Push_Stack(string[i]);
        }else{
            if (string[i] == '['){
            	Push_Stack(string[i]);
            }else{
            	if (string[i] == '['){
                    Push_Stack(string[i]);
                }else{
                    if (string[i] == ')'){
                        
                        if (Verifica_Stack() == 0){
                                return 0;
                        }else{
                            if (Peek_Stack() == '('){
                            	Pop_Stack();
                            }else{
                            	return 0;
                            }
                        }
                    }else{
                        if (string[i] == '}'){
                        	if (Verifica_Stack() == 0){
                                return 0;
                            }else{
                                if (Peek_Stack() == '{'){
                                    Pop_Stack();
                                }else{
                                    return 0;
                                }
                            }
                        }else{
                        	if (string[i] == ']'){
                                if (Verifica_Stack() == 0){
                                    return 0;
                                }else{
                                    if (Peek_Stack() == '['){
                                        Pop_Stack();
                                    }else{
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return Verifica_Stack();
}

int main(){
    int* values;
    int n;
    char string[1000];
    int size;
    scanf("%d",&n);
    values = (int*)malloc(n*sizeof(int));
    for (int i = 0; i<n; i++){
    	//fgets(string, 256, stdin);
        scanf("%s",string);
     	size = strlen(&string);
        values[i] = verify_string(&string, size);
    }
    for (int i = 0; i<n; i++){
        if (values[i] == 1){
            printf("YES\n");
            
        }else{
            printf("NO\n");
        }
    }
}
