template <>
struct Convert<int, float> {
    float operator()(const int& a) {
        return a;
    }
};
