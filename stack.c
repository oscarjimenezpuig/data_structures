#include "stack.h"

struct Node {
    void* val;
    struct Node* prv;
};

struct Stack {
    uchar sov;
    struct Node* lst;
};

static struct Node* nod_new(void* val,uchar sov,struct Node* prv) {
    //se crea un nuevo nodo
    struct Node* nn=malloc(sizeof(struct Node));
    if(nn) {
        nn->val=malloc(sov);
        if(nn->val) {
            val_cpy(nn->val,val,sov);
            nn->prv=prv;
        } else {
            free(nn);
            nn=NULL;
        }
    }
    return nn;
}

static void nod_del(struct Node* n) {
    if(n) {
        nod_del(n->prv);
        free(n->val);
        free(n);
    }
}

Stack stk_new(size_t sv) {
    Stack s=malloc(sizeof(struct Stack));
    if(s) {
        s->sov=sv;
        s->lst=NULL;
    }
    return s;
}

void stk_del(Stack* s) {
    if(s) {
        nod_del((*s)->lst);
        free(*s);
        *s=NULL;
    }
}

int stk_psh(Stack s,void* v) {
    if(s && v) {
        struct Node* nn=nod_new(v,s->sov,s->lst);
        if(nn) {
            s->lst=nn;
            return 1;
        }
    }
    return 0;
}

int stk_pop(Stack s,void* v) {
    if(s && s->lst) {
        struct Node* n=s->lst;
        s->lst=n->prv;
        n->prv=NULL;
        val_cpy(v,n->val,s->sov);
        nod_del(n);
        return 1;
    }
    return 0;
}

int stk_emp(Stack s) {
    if(!s || !s->lst) return 1;
    return 0;
}
