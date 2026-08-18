#include "array.h"

struct Array {
    size_t cap; //capacidad
    size_t siz; //tamaño
    uchar sov; //tamaño del dato
    void* val; //memoria donde reposan todos los valores
};

Array arr_new(uchar sv,size_t c) {
    Array a=malloc(sizeof(struct Array));
    if(a) {
        a->val=malloc(sv*c);
        a->cap=c;
        a->sov=sv;
        a->siz=0;
    }
    return a;
}

void arr_del(Array* a) {
    if(a && *a) {
        free((*a)->val);
        free(*a);
        *a=NULL;
    }
}

Array arr_cpy(Array a) {
    Array b=NULL;
    if(a) {
        b=arr_new(a->sov,a->cap);
        void* val=malloc(a->sov);
        for(int k=0;k<a->siz;k++) {
            arr_get(a,k,val);
            arr_ins(b,val);
        }
        free(val);
    }
    return b;
}

size_t arr_siz(Array a) {
    if(a) return a->siz;
    return 0;
}

size_t arr_cap(Array a) {
    if(a) return a->cap;
    return 0;
}

int arr_ins(Array a,void* v) {
    if(a && v) {
        if(a->cap==a->siz) {
            void* ptr=realloc(a->val,a->sov*(a->siz+1));
            if(ptr) {
                a->val=ptr;
                ++a->cap;
            }
        }
        if(a->cap>a->siz) {
            val_cpy(a->val+(a->sov*a->siz),v,a->sov);
            ++a->siz;
            return 1;
        }
    }
    return 0;
}

int arr_get(Array a,size_t p,void* v) {
    if(a && v && p<a->siz) {
        val_cpy(v,a->val+(a->sov*p),a->sov);
        return 1;
    }
    return 0;
}

int arr_fnd(Array a,void* v,int (*c)(void*,void*),size_t* pos) {
    int ret=0;
    if(a && v && c && pos) {
        void* val=malloc(a->sov);
        for(int k=0;k<a->siz && !ret;k++) {
            arr_get(a,k,val);
            if(c(val,v)==0) {
                *pos=k;
                ret=1;
            }
        }
        free(val);
    }
    return ret;
}  

int arr_era(Array a,size_t p) {
    if(a && p<a->siz) {
        void* ptr=a->val+(a->sov*p);
        while(ptr!=a->val+(a->siz-1)*a->sov) {
            val_cpy(ptr,ptr+a->sov,a->sov);
            ptr+=a->sov;
        }
        --a->siz;
        return 1;
    }
    return 0;
}

void arr_prt(Array a,void (*p)(void*)) {
    if(a && p) {
        void* val=malloc(a->sov);
        if(val) {
            for(int k=0;k<a->siz;k++) {
                arr_get(a,k,val);
                p(val);
                printf(" ");
            }
            printf("\n");
        }
        free(val);
    }
}

int arr_rev(Array a) {
    if(a) {
        void* pi=a->val;
        void* pf=a->val+(a->siz-1)*a->sov;
        size_t tot=(a->siz%2==0)?a->siz/2:(a->siz+1)/2;
        void* brd=malloc(a->sov);
        while(pi!=a->val+(tot*a->sov)) {
            val_cpy(brd,pf,a->sov);
            val_cpy(pf,pi,a->sov);
            val_cpy(pi,brd,a->sov);
            pi+=a->sov;
            pf-=a->sov;
        }
        free(brd);
        return 1;
    }
    return 0;
}

int arr_srt(Array a,int(*c)(void*,void*)) {
    if(a && c) {
        void* vc=malloc(a->sov);
        size_t changes;
        do {
            changes=0;
            void* ptr=a->val;
            while(ptr!=a->val+a->sov*(a->siz-1)) {
                if(c(ptr,ptr+a->sov)==-1) {
                    val_cpy(vc,ptr+a->sov,a->sov);
                    val_cpy(ptr+a->sov,ptr,a->sov);
                    val_cpy(ptr,vc,a->sov);
                    ++changes;
                }
                ptr+=a->sov;
            }
        } while(changes>0);
        free(vc);
        return 1;
    }
    return 0;
}       

        

