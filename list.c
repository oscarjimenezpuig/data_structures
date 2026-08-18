#include "list.h"

struct Node {
    void* val;
    struct Node* nxt;
};

struct List {
    uchar sov;
    struct Node* fst;
    struct Node* lst;
};

static struct Node* nod_new(void* val,uchar sov) {
    //se crea un nuevo nodo
    struct Node* nn=malloc(sizeof(struct Node));
    if(nn) {
        nn->val=malloc(sov);
        if(nn->val) {
            val_cpy(nn->val,val,sov);
            nn->nxt=NULL;
        } else {
            free(nn);
            nn=NULL;
        }
    }
    return nn;
}

static void nod_del(struct Node* n) {
    if(n) {
        nod_del(n->nxt);
        free(n->val);
        free(n);
    }
}

List lst_new(size_t sov) {
    struct List* l=malloc(sizeof(struct List));
    if(l) {
        l->fst=l->lst=NULL;
        l->sov=sov;
    }
    return l;
}

void lst_del(List* l) {
    if(l && *l) {
        nod_del((*l)->fst);
        free(*l);
        *l=NULL;
    }
}

int lst_psh(List l,void* v) {
    if(l && v) {
        struct Node* n=nod_new(v,l->sov);
        if(l->fst) l->lst->nxt=n;
        else l->fst=n;
        l->lst=n;
        return 1;
    }
    return 0;
}

int lst_pop(List l,void* v) {
    if(l && v && l->fst) {
        struct Node* ntd=l->fst;
        l->fst=l->fst->nxt;
        ntd->nxt=NULL;
        val_cpy(v,ntd->val,l->sov);
        nod_del(ntd);
        return 1;
    }
    return 0;
}

size_t lst_siz(List l) {
    size_t r=0;
    if(l) {
        struct Node* p=l->fst;
        while(p) {
            ++r;
            p=p->nxt;
        }
    }
    return r;
}
