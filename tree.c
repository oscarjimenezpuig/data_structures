#include "tree.h"

struct Tree {
    void* val;
    struct Tree* fat;
    Array son;
    uchar sov;
};

Tree tre_new(uchar sov,void* v) {
    Tree t=malloc(sizeof(struct Tree));
    if(t) {
        t->val=malloc(sov);
        if(t->val) {
            val_cpy(t->val,v,sov);
            t->sov=sov;
            t->son=arr_new(sizeof(Tree),0);
            t->fat=NULL;
        } else {
            free(t);
            t=NULL;
        }
    }
    return t;
}

void tre_del(Tree* t) {
    if(t && *t) {
        size_t s=arr_siz((*t)->son);
        Tree son;
        for(size_t k=0;k<s;k++) {
            arr_get((*t)->son,k,&son);
            tre_del(&son);
        }
        free((*t)->val);
        arr_del(&((*t)->son));
        free(*t);
        *t=NULL;
    }
}

int tre_val(Tree t,void* v) {
    if(t) {
        val_cpy(v,t->val,t->sov);
        return 1;
    }
    return 0;
}

Tree tre_fat(Tree t) {
    if(t) return t->fat;
    else return NULL;
}

Array tre_son(Tree t) {
    if(t) {
        size_t acap=arr_siz(t->son);
        Array a=arr_new(t->sov,acap);
        Tree ts;
        for(size_t n=0;n<acap;n++) {
            arr_get(t->son,n,&ts);
            arr_ins(a,ts->val);
        }
        return a;
    }
    return NULL;
}

size_t tre_siz(Tree t) {
    size_t size=0;
    if(t) {
        size=1;
        size_t sson=arr_siz(t->son);
        Tree son;
        for(size_t ns=0;ns<sson;ns++) {
            arr_get(t->son,ns,&son);
            size+=tre_siz(son);
        }
    }
    return size;
}

static size_t _tre_len(Tree t) {
    size_t max=0;
    if(t) {
        size_t ss=arr_siz(t->son);
        Tree s;
        for(size_t ns=0;ns<ss;ns++) {
            arr_get(t->son,ns,&s);
            size_t sa=1+_tre_len(s);
            max=(max<sa)?sa:max;
        }
    }
    return max;
}

size_t tre_len(Tree t) {
    return _tre_len(t);
}

Tree tre_rot(Tree t) {
    if(t) {
        Tree a=t;
        while(a->fat) {
            a=a->fat;
        }
        return a;
    }
    return NULL;
}

static void _tre_lef(Tree t,Array a) {
    size_t ns=arr_siz(t->son);
    if(ns==0) arr_ins(a,&t);
    else {
        Tree ts;
        for(size_t s=0;s<ns;s++) {
            arr_get(t->son,s,&ts);
            _tre_lef(ts,a);
        }
    }
}           

Array tre_lef(Tree t) {
    Array a=NULL;
    if(t) {
        a=arr_new(sizeof(Tree),1);
        _tre_lef(t,a);
    }
    return a;
}

int tre_is_anc(Tree a,Tree b) {
    if(a && b) {
        Tree act=b;
        while(act) {
            if(act==a) return 1;
            else act=act->fat;
        }
    }
    return 0;
}

int tre_is_rot(Tree t) {
    if(t) return t->fat==NULL;
    return 0;
}

int tre_is_lef(Tree t) {
    if(t) return arr_siz(t->son)==0;
    return 0;
}

int tre_ins(Tree f,Tree s) {
    if(f && s && f->sov==s->sov && s->fat==NULL && tre_rot(f)!=s) {
        if(arr_ins(f->son,&s)) {
            s->fat=f;
            return 1;
        }
    }
    return 0;
}

static int comtree(void* a,void* b) {
    Tree ta=cast(Tree,a);
    Tree tb=cast(Tree,b);
    if(ta>tb) return 1;
    else if(ta==tb) return 0;
    else return -1;
}

int tre_pod(Tree t) {
    Tree f;
    if(t && (f=t->fat)) {
        size_t pos;
        if(arr_fnd(f->son,&t,comtree,&pos)) {
            if(arr_era(f->son,pos)) {
                t->fat=NULL;
                return 1;
            }
        }
    }
    return 0;
}
        

static void _tre_pre(Tree s,Array a) {
    arr_ins(a,s->val);
    size_t ss=arr_siz(s->son);
    Tree son;
    for(size_t ns=0;ns<ss;ns++) {
        arr_get(s->son,ns,&son);
        _tre_pre(son,a);
    }
} 

Array tre_pre(Tree t) {
    if(t) {
        Array a=arr_new(t->sov,tre_siz(t));
        _tre_pre(t,a);
        return a;
    } 
    return NULL;
}

static void _tre_pos(Tree s,Array a) {
    size_t ss=arr_siz(s->son);
    Tree son;
    for(size_t ns=0;ns<ss;ns++) {
        arr_get(s->son,ns,&son);
        _tre_pos(son,a);
    }
    arr_ins(a,s->val);
} 

Array tre_pos(Tree t) {
    if(t) {
        Array a=arr_new(t->sov,tre_siz(t));
        _tre_pos(t,a);
        return a;
    }
    return NULL;
}

static void _tre_lev(Array s,Array r) {
    if(arr_siz(s)>0) {
        Tree t;
        arr_get(s,0,&t);
        arr_ins(r,t->val);
        arr_era(s,0);
        Tree ts;
        for(size_t ns=0;ns<arr_siz(t->son);ns++) {
            arr_get(t->son,ns,&ts);
            arr_ins(s,&ts);
        }
        _tre_lev(s,r);
    }
}

Array tre_lev(Tree t) {
    if(t) {
        size_t st=tre_siz(t);
        Array s=arr_new(sizeof(Tree),st);
        arr_ins(s,&t);
        Array r=arr_new(t->sov,st);
        _tre_lev(s,r);
        arr_del(&s);
        return r;
    }
    return NULL;
}

static void _tree_prt(size_t tab,Tree t,void(*p)(void*)) {
    if(t) {
        for(size_t k=0;k<tab;k++) printf("-");
        printf(">");
        p(t->val);
        printf("\n");
        size_t sos=arr_siz(t->son);
        Tree son;
        for(size_t s=0;s<sos;s++) {
            arr_get(t->son,s,&son);
            _tree_prt(tab+1,son,p);
        }
    }
}

void tre_prt(Tree t,void (*p)(void*)) {
    _tree_prt(0,t,p);
}
