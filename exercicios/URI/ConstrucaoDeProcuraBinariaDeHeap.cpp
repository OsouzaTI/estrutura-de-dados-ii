#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

#define ISNULL(x) (x == nullptr)
#define   LEFT(i) (2 * i + 1)
#define  RIGHT(i) (2 * i + 2)


namespace SegTree {

	struct SNode
	{
		string 	s;
    	int 	v;
	};
	
	struct SPNode {
		SNode x;
    	SPNode *left, *right; 
    	SPNode(SNode &t) : x(t), left(NULL), right(NULL){}
	};

	SNode arr[50001];
	struct Segtree{
		pair<int, int> seg[200001];	
		void build(int l, int r, int i){
			if(l == r){
				seg[i].first = arr[l].v;
				seg[i].second = l;
				return;
			}
			int mid = (l+r)/2;
			build(l, mid, LEFT(i));
			build(mid+1, r, RIGHT(i));
		
			if(seg[LEFT(i)].first > seg[RIGHT(i)].first) seg[i] = seg[LEFT(i)];
			else seg[i] = seg[RIGHT(i)];
		}

		int query(int l, int r, int i, int x, int y){
			if(r < x || l > y) return -1;
			if(l >= x && r <= y) return seg[i].second;
			int mid = (l+r)/2;
			int left = query(l, mid, LEFT(i), x, y);
			int right = query(mid+1, r, RIGHT(i), x, y);
		
			if(left == right) 
				return left;
			else if(left == -1)
				return right;
			else if(right == -1)
				return left;
		
			if(arr[left].v > arr[right].v)
				return left;
			else
				return right;
		}

	};

	bool cmp1(SNode& a, SNode& b){
		return a.s < b.s;
	}
	
	bool cmp2(int& a, int& b){
		return a > b;
	}
	
	Segtree *s;
	SPNode* build(int l, int r, int n){
		if(l > r) return NULL;
		if(l == r){
			SPNode* temp = new SPNode(arr[l]);
			return temp;
		}
		int pos = s->query(0, n-1, 0, l, r);
		SPNode* curr = new SPNode(arr[pos]);
		curr->left = build(l, pos-1, n);
		curr->right = build(pos+1, r, n);
		return curr;
	}
	
	void infoSegTree(SPNode* root){
		if(!root) return;
		cout << "(";
		infoSegTree(root->left);
		cout << root->x.s << "/" << root->x.v;
		infoSegTree(root->right);
		cout << ")";
	}

}

int findIndex(string target, char k){
    return target.find(k);
}

int main(){
    // Declaração de variáveis
	ofstream file; // usado para debug
    int n, i; // entradas de 0 a 50000
    string entrada;    
    // Recebe a entrada
    while(cin >> n && n != 0){ 
		SegTree::s = new SegTree::Segtree();
        for(i = 0; i < n; i++){
            cin >> entrada;
            // pegando indice do caracter
            int indexOfBar = findIndex(entrada, '/');
            // formato de entrada : a/7
            string label = entrada.substr(0, indexOfBar);
            stringstream _prioridade(entrada.substr(indexOfBar+1));
            // transformando a string em inteiro
            int  prioridade = 0;
            _prioridade >> prioridade;
            // cout << "label: " << label << " prioridade: " << prioridade << endl;
            SegTree::arr[i].s = label;
			SegTree::arr[i].v = prioridade;
        }
		sort(SegTree::arr, SegTree::arr+n, SegTree::cmp1);
		SegTree::s->build(0, n-1, 0);
		SegTree::SPNode* ans = SegTree::build(0, n-1, n);
		SegTree::infoSegTree(ans);
		std::cout << std::endl;
    }
    // cout << endl;
	return 0;
}
