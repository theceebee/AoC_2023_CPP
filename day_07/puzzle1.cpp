#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

enum Type
{
    high_card,        // 6
    one_pair,         // 5
    two_pair,         // 4
    three_of_a_kind,  // 3
    full_house,       // 2
    four_of_a_kind,   // 1
    five_of_a_kind,   // 0
};

class Hand
{
    string m_hand{};

private:
    map<char, int> m_hand_map{};
    map<char, int> m_hand_map_flipped{};

public:
    Hand(string hand) : m_hand{hand}
    {
        for (auto h : m_hand)
        {
            int count = 1;
            auto it = m_hand_map.find(h);
            if (it != m_hand_map.end())
                count += it->second;

            m_hand_map[h] = count;
        }

        for (const auto &h : m_hand_map)
            m_hand_map_flipped[h.second] = h.first;
    }

    Type getType() const;

    friend bool operator<(const Hand& x, const Hand& y);
    friend ostream &operator<<(ostream &os, const Hand &hand);
};

Type Hand::getType() const
{
    Type result;

    if (m_hand_map.size() == 1)
    {
        result = Type::five_of_a_kind;  // 0
    }
    else if (m_hand_map.size() == 2)
    {
        // Could be four of a kind OR full house.
        if (m_hand_map_flipped.count(4) == 1)
        {
            result = Type::four_of_a_kind;  // 1
        }
        else
        {
            result = Type::full_house;  // 2
        }
    }
    else if (m_hand_map.size() == 3)
    {
        // Could be three of a kind or two pair.
        if (m_hand_map_flipped.count(3) == 1)
        {
            result = Type::three_of_a_kind;  // 3
        }
        else
        {
            result = Type::two_pair;  // 4
        }
    }
    else if (m_hand_map.size() == 4)
    {
        result = Type::one_pair;  // 5
    }
    else
    {
        result = Type::high_card;  // 6
    }

    return result;
}


ostream& operator<<(ostream& os, const Hand& hand)
{
    os << hand.m_hand;
    return os;
}


bool operator<(const Hand& x, const Hand& y)
{
    bool result;

    if (x.getType() == y.getType())
    {
        string order = "23456789TJQKA";

        for (int i = 0; i < 5; i++)
        {
            size_t x_i = order.find(x.m_hand[i]);
            size_t y_i = order.find(y.m_hand[i]);

            if (x_i != y_i)
            {
                result = x_i < y_i;
                break;
            }
        }
    }
    else
    {
        result = x.getType() < y.getType();
    }

    return result;
}


int main(int argc, char **argv)
{
    string line, hand;
    int bid;
    vector<pair<Hand, int>> hands{};

    while (getline(cin, line))
    {
        stringstream ss(line);
        ss >> hand >> bid;
        hands.push_back({hand, bid});
    }

    sort(hands.begin(), hands.end());

    int result = 0;
    for (int i = 0; i < hands.size(); i++)
        result += (i + 1) * hands[i].second;

    cout << "Result: " << result << endl;

    return 0;
}