// Fenwick tree                       
#define MAX_SIZE 100000

template <class type> class Fenwick {
private:
    type tree[MAX_SIZE];
    int n;

public:
    type read(int idx){
        type sum = 0;
        while (idx > 0){
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    void update(int idx , type val){
        while (idx <= n){
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    void reset(int n) {
        this->n = n;
        FOR(i, n + 1) tree[i] = 0;
    }
};

Fenwick<int> fenwick;
