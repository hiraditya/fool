TensorShape: class describing a shape of a tensor (multi-dimensional array).
Implement GetIntersect()

[2:6] [4:9]   -> [4:6]
[2:6] [6:10]  -> [6:6]

[2:6] [4:5]  -> [4:5]
[5:10] [20:40]

using VecPairInt = std::vector<std::pair<int, int>>;
class TensorShape {
    public:
        TensorShape(VecPairInt d):dims(d) {}
        TensorShape(int sz) { dims.reserve(sz); }

        const VeVecPairIntcInt& getDims() { return dims; }
        TensorShape & operator[](int idx, pair<int, int> p) {
            dims[idx] = p;
}
        int size() { return dims.size(); }
        bool empty() { return size() == 0; }
        TensorShape GetIntersect(TensorShape t1, TensorShape t2) {
            auto d1 = t1.getDims(); // [2:6]
            auto d2 = t2.getDims(); // [4:5]
            TensorShape in(d1.size());
            if (d1.size() != d2.size())
                return {};

            for (int i = 0; i < d1.size(); ++i) {
    auto p1 = d1[i];
    auto p2 = d2[i];
    if (p1.first > p2.first)
        std::swap(p1, p2);
    if (p1.second < p2.first)
        return {};
    // Finite intersection
    int last = std::min(p1.second, p2.second);
    in[i] = {std::max(p1.first, p2.first), last};
}
return in;
        }
        vector<TensorShape> GetUnion(TensorShape t1, TensorShape t2) {
            auto d1 = t1.getDims(); // [2:6]
            auto d2 = t2.getDims(); // [4:5]
            TensorShape in(d1.size());
            vector<TensorShape> vec;
            if (d1.size() != d2.size())
                return {};

            for (int i = 0; i < d1.size(); ++i) {
    auto p1 = d1[i];
    auto p2 = d2[i];
    if (p1.second < p2.first){
        // clone the vector
    }
    in[i] = {
std::min(p1.first, p2.first),
std::max(p1.second, p2.second)
};
}
return in;
}
private:
    vector<pair<int, int>> dims;
};



TensorShape a;
TensorShape b;
c = GetIntersect(a, b);

GetIntersect(a, c);

Union?

GetUnion?


[2:4] [6:9]

[2:4] [6:9]
[2:4][2:4] [6:9][6:9]

N dimensional tensor, 2^N
