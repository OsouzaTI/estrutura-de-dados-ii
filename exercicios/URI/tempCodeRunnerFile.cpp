namespace Treap {
    
    using std::string;
    
    struct TNode {
        string v; 		// texto
        unsigned int p; // prioridade
        TNode* l; 		// esquerda
        TNode* r; 		// direita
        TNode(string v, unsigned int p) 
            : v(v), p(p), l(nullptr), r(nullptr){};
    };

    typedef struct TNode   TNode;
    typedef struct TNode* pTNode;

    bool find(TNode *t, string x ){
        if(ISNULL(t))
            return false;
        if(t->v == x)
            return true;
        if(t->v < x)
            return find(t->r, x);
        return find(t->l, x);
    };

    void merge(pTNode & t, TNode* l, TNode* r){
        
        if(ISNULL(l)){
            t = r;
            return;
        }

        if(ISNULL(r)){
            t = l;
            return;
        }

        if(l->p > r->p){
            merge(l->r,l->r,r);
            t=l;
        } else {                    
            merge(r->l,l,r->l);
            t=r;
        }

    };

    void split(TNode* t, string v, pTNode & l, pTNode & r){
        if(ISNULL(t)){
            l = r = nullptr;
            return;
        }

        if(t->v >= v){
            split(t->l, v, l, t->l);
            r = t;
        } else {
            split(t->r, v, t->r, r);
            l = t;
        }
        
    }   

    void insert(pTNode & t, string x, unsigned int p){
        if(find(t, x)) 
            return;
        TNode* l = nullptr;
        TNode* r = nullptr;
        split(t, x, l , r);
        TNode* k = new TNode(x, p);
        merge(l, l, k);
        merge(t, l, r);
    }

    void info(pTNode & t){
        if(ISNULL(t))return;
        std::cout << "(";
        info(t->l);
        std::cout << t->v << "/" << t->p;
        info(t->r);
        std::cout << ")";
    }

	void infoLn(pTNode & t){
		info(t);
		// std::cout << std::endl;
	}

	void infoLog(pTNode & t, ofstream& f){
		if(ISNULL(t))return;
        f << "(";
        infoLog(t->l, f);
        f << t->v << "/" << t->p;
        infoLog(t->r, f);
    	f << ")";
	}

};
