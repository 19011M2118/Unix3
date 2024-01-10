#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"
void add(){
            printf("\tpopq\t%%rax\n");
            printf("\tpopq\t%%rbx\n");
            printf("\taddq\t%%rax,%%rbx\n");
            printf("\tpushq\t%%rbx\n");
}	
void subtract(){
            printf("\tpopq\t%%rax\n");
            printf("\tpopq\t%%rbx\n");
            printf("\tsubq\t%%rax,%%rbx\n");
            printf("\tpushq\t%%rbx\n");
}
void multiply(){
            printf("\tpopq\t%%rax\n");
            printf("\tpopq\t%%rbx\n");
            printf("\timulq\t%%rax,%%rbx\n");
            printf("\tpushq\t%%rbx\n");
}
void divide(){
            printf("\tpopq\t%%r14\n");
            printf("\tpopq\t%%rax\n");
            printf("\txorq\t%%rdx,%%rdx\n");
            printf("\tidivq\t%%r14\n");
            printf("\tpushq\t%%rax\n");
}
void gcd(){
            printf("\tpopq\t%%rax\n");
            printf("\tpopq\t%%rbx\n");
            printf("gcd:\n");
            printf("\txorq\t%%rdx,%%rdx\n");
            printf("\tidivq\t%%rbx\n");
            printf("\tmovq\t%%rbx,%%rax\n");
            printf("\tmovq\t%%rdx,%%rbx\n");
            printf("\ttest\t%%rbx,%%rbx\n");
            printf("\tjnz\tgcd\n");
            printf("\tpushq\t%%rax\n");
}
static int lbl;

int ex(nodeType *p) {
    int lbl1, lbl2;

    if (!p) return 0;
    switch(p->type) {
//--------------------------------------------------------------          
    case typeCon:       
        printf("\tpushq\t$%d\n", p->con.value); 
        break;
//--------------------------------------------------------------          
    case typeId:        
        printf("\tpush\t%c\n", p->id.i + 'a'); 
        break;
//--------------------------------------------------------------          
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            lbl2 = lbl++;
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
//--------------------------------------------------------------            
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                lbl1 = lbl++;
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                lbl1 = lbl++;
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
//------------------------------------------------------------------           
        case PRINT:     
            ex(p->opr.op[0]);
            printf("\tpopq\t%%rsi\n");
            printf("\tpushq\t%%rax\n");
            printf("\tpushq\t%%rbx\n");
            printf("\tmovq\t$print123,%%rdi\n");
            printf("\tmovq\t$0,%%rax\n");
            printf("\tcall\tprintf\n");
            printf("\tpopq\t%%rbx\n");
            printf("\tpopq\t%%rax\n");
            break;
//------------------------------------------------------------------            
        case '=':       
            ex(p->opr.op[1]);
            printf("\tpopq\t%c\n", p->opr.op[0]->id.i + 'a');
            break;
        case UMINUS:    
            ex(p->opr.op[0]);
            printf("\tpopq\t%%rax\n");
            printf("\tnegq\t%%rax\n");
            printf("\tpushq\t%%rax\n");
            break;
//------------------------------------------------------------------------------            
	case FACT:
  	    ex(p->opr.op[0]);
	    printf("\tfact\n");
	    break;
	case LNTWO:
	    ex(p->opr.op[0]);
	    printf("\nlntwo\n");
	    break;
//--------------------------------------------------------------------------------------------        
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
	        
            case GCD:   
                gcd();
            break;
//------------------------------------------------------------------------------            
            case '+':   
                add();
            break;
//------------------------------------------------------------------------------            
            case '-':   
                subtract();
            break; 
//------------------------------------------------------------------------------            
            case '*':   
                multiply();
            break;
//------------------------------------------------------------------------------            
            case '/':
                divide();
            break;
            
            case '<':
            printf("\tpopq\t%%rbx\n");
            printf("\tpopq\t%%rax\n");
            printf("\tcmpq\t%%rbx,%%rax\n");
            printf("\tjge\tL%03d\n",lbl);
            break;
            
            case '>':   
            printf("\tpopq\t%%rbx\n");
            printf("\tpopq\t%%rax\n");
            printf("\tcmpq\t%%rbx,%%rax\n");
            printf("\tjle\tL%03d\n",lbl);
            break;
//------------------------------------------------------------------------------            
            
            case GE:
            printf("\tpopq\t%%rbx\n");
            printf("\tpopq\t%%rax\n");
            printf("\tcmpq\t%%rbx,%%rax\n");
            printf("\tjl\tL%03d\n",lbl); 
            break;
            
            case LE:
            printf("\tpopq\t%%rbx\n");
            printf("\tpopq\t%%rax\n");
            printf("\tcmpq\t%%rbx,%%rax\n");
            printf("\tjg\tL%03d\n",lbl); 
            break;
            
            case NE:    
            printf("\tpopq\t%%rbx\n");
            printf("\tpopq\t%%rax\n");
            printf("\tcmpq\t%%rbx,%%rax\n");
            printf("\tje\tL%03d\n",lbl); 
            break;
            
            case EQ:
            printf("\tpopq\t%%rbx\n");
            printf("\tpopq\t%%rax\n");
            printf("\tcmpq\t%%rbx,%%rax\n");
            printf("\tjne\tL%03d\n",lbl); 
            break;
            }
        }
    }
    return 0;
}
