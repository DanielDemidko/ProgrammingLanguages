#include "v2t_t2v.h"

#include <iostream>
#include <vector>
#include <tuple>

using std::cout;
using std::endl;
using std::is_same_v;
using std::vector;
using std::tuple;
using std::pair;

namespace testing
{
    template<typename VectorOfTuple>
    auto v2t(VectorOfTuple&& vec_tuple)
    {
        return vector_to_tuple(std::forward<VectorOfTuple>(vec_tuple));
    }

    template<typename TupleOfVector>
    auto t2v(TupleOfVector&& tuple_vec)
    {
        return tuple_to_vector(std::forward<TupleOfVector>(tuple_vec));
    }

    template<typename Tp, typename Tested>
    constexpr void check_t(Tested)
    {
        static_assert(std::is_same_v<Tp, Tested>);
    }

    template<typename... Ts>
    constexpr void easy_check()
    {
        using vec = vector<tuple<Ts...>>;
        using tpl = tuple<vector<Ts>...>;

        if constexpr (sizeof...(Ts) == 1)
        {
            using vec_solo = vector<std::tuple_element_t<0, tuple<Ts...>>>;

            check_t<vec_solo>(v2t(vec()));
            check_t<vec_solo>(t2v(tpl()));
            check_t<vec_solo>(t2v(v2t(vec())));
            check_t<vec_solo>(v2t(t2v(tpl())));

            vec v;
            check_t<vec_solo>(t2v(v2t(v)));
            tpl t;
            check_t<vec_solo>(v2t(t2v(t)));
        }
        else if constexpr (sizeof...(Ts) == 2)
        {
            using vec_pair = vector<pair<Ts...>>;
            using pair_vec = pair<vector<Ts>...>;

            check_t<pair_vec>(v2t(vec()));
            check_t<vec_pair>(t2v(tpl()));
            check_t<pair_vec>(v2t(t2v(tpl())));
            check_t<pair_vec>(v2t(t2v(pair_vec())));
            check_t<vec_pair>(t2v(v2t(vec())));
            check_t<vec_pair>(t2v(v2t(vec_pair())));

            pair_vec pv;
            check_t<pair_vec>(v2t(t2v(pv)));
            vec_pair vp;
            check_t<vec_pair>(t2v(v2t(vp)));
        }
        else
        {
            check_t<vec>(t2v(v2t(t2v(v2t(t2v(v2t(vec())))))));
            check_t<tpl>(v2t(t2v(v2t(t2v(v2t(t2v(tpl())))))));

            vec v;
            check_t<vec>(t2v(v2t(t2v(v2t(t2v(v2t(v)))))));
            tpl t;
            check_t<tpl>(v2t(t2v(v2t(t2v(v2t(t2v(t)))))));
        }
    }

    [[noreturn]] void fail()  { std::cout << -1 << std::endl; exit(0); }
}

int main()
{
    testing::easy_check<int>();
    testing::easy_check<double>();
    testing::easy_check<char>();
    testing::easy_check<float>();
    testing::easy_check<short>();

    testing::easy_check<int, double>();
    testing::easy_check<double, char>();
    testing::easy_check<char, float>();
    testing::easy_check<float, short>();
    testing::easy_check<short, int>();

    testing::easy_check<int, double, short>();
    testing::easy_check<short, int, double>();
    testing::easy_check<double, short, int>();

    testing::easy_check<float, double, int, unsigned int>();
    testing::easy_check<unsigned char, float, double, int, unsigned int>();
    testing::easy_check<signed char, unsigned char, float, double, int, unsigned int>();
    testing::easy_check<char, signed char, unsigned char, float, double, int, unsigned int>();
    
    {
        vector<tuple<int>> v;
        for (int i = 0; i < 100; ++i)
            v.push_back(tuple<int>{i});
        vector<int> single = vector_to_tuple(v);
        for (int i = 0; i < 100; ++i)
            if (single[i] != i)
                testing::fail();
        single = tuple_to_vector(single);
        for (int i = 0; i < 100; ++i)
            if (single[i] != i)
                testing::fail();
    }

    {
        vector<tuple<int, int>> v;
        for (int i = 0; i < 100; ++i)
            v.push_back(tuple<int, int>{i, -i});
        auto [v1, v2] = vector_to_tuple(v);
        for (int i = 0; i < 100; ++i)
            if (v1[i] != i || v2[i] != -i)
                testing::fail();
        auto vp = tuple_to_vector(pair<vector<int>, vector<int>>{v1, v2});
        for (int i = 0; i < 100; ++i)
            if (vp[i].first != i || vp[i].second != -i)
                testing::fail();
    }

    {
        vector<tuple<int, int, int>> v;
        for (int i = 0; i < 100; ++i)
            v.push_back(tuple<int, int, int>{i, -i, i << 1});
        auto [v1, v2, v3] = vector_to_tuple(v);
        for (int i = 0; i < 100; ++i)
            if (v1[i] != i || v2[i] != -i || v3[i] != i << 1)
                testing::fail();
        auto vt = tuple_to_vector(tuple<vector<int>, vector<int>, vector<int>>{v1, v2, v3});
        for (int i = 0; i < 100; ++i)
            if (std::get<0>(vt[i]) != i || std::get<1>(vt[i]) != -i || std::get<2>(vt[i]) != i << 1)
                testing::fail();
    }

    cout << 0 << endl;
    return 0;
}