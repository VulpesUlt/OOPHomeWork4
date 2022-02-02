#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>

// Task 1 (from guidence material)

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }
    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int* data = new int[newLength];

        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        delete[] m_data;

        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);

        int* data = new int[m_length + 1];

        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        data[index] = value;

        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) { insertBefore(value, m_length); }

    // Task 1 itself ================================================

    void print()
    {
        for (int index = 0; index < m_length; ++index)
            std::cout << m_data[index] << " ";
        std::cout << std::endl;
    }
    
    void pop_back() 
    {
        int* data = new int[m_length - 1];

        for (int before = 0; before < m_length - 1; ++before)
            data[before] = m_data[before];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void pop_front()
    {
        int* data = new int[m_length - 1];

        for (int before = 1; before < m_length; ++before)
            data[before - 1] = m_data[before];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void insertSort()
    {
        for (int step = 0; step < m_length; step++)
            for (int i = step; i > 0; i--)
                if (m_data[i - 1] > m_data[i])
                    std::swap(m_data[i - 1], m_data[i]);
    }


    // ==============================================================


    ~ArrayInt()
    {
        delete[] m_data;
    }
};


// Task 3

class Card // Class from home work 3
{
private:
    enum class suit
    {
        SPADES,
        CLUBS,
        HEARTS,
        DIAMONDS
    };

    enum class rank
    {
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,
    };

    suit m_suit;
    rank m_rank;
    bool m_faceUp;

public:

    void Flip()
    {
        m_faceUp = !m_faceUp;
    }

    uint32_t GetValue()
    {
        switch (m_rank)
        {
        case Card::rank::TWO:
            return 2;
        case Card::rank::THREE:
            return 3;
        case Card::rank::FOUR:
            return 4;
        case Card::rank::FIVE:
            return 5;
        case Card::rank::SIX:
            return 6;;
        case Card::rank::SEVEN:
            return 7;
        case Card::rank::EIGHT:
            return 8;
        case Card::rank::NINE:
            return 9;
        case Card::rank::TEN:
            return 10;
        case Card::rank::JACK:
            return 10;
        case Card::rank::QUEEN:
            return 10;
        case Card::rank::KING:
            return 10;
        case Card::rank::ACE:
            return 11; // changed from 1 to 11 due to the task
        default:
            return 0;
        }
    }
};

class Hand
{
private:
    std::vector<Card*> m_collection;

public:
    void Add(Card* newCard) { m_collection.push_back(newCard); }

    void Clear() { m_collection.clear(); }

    uint32_t GetValue()
    {
        std::vector<Card*>::iterator it = m_collection.begin();
        uint32_t result = 0;
        while (it != m_collection.end())
        {
            result += (*it)->GetValue();
            it++;
        }

        return result;
    }
};



int main()
{
    
    // Task 1

    const int TASKONE = 15;
    ArrayInt taskOne;
    for (int i = TASKONE; i > 0; i--)
        taskOne.push_back(i);

    taskOne.print();
    taskOne.insertSort();
    taskOne.print();

    taskOne.pop_front();
    taskOne.pop_back();
    taskOne.print();


    // Task 2

    std::vector<int> taskTwo;
    for (int i = 0; i < 100; i++)
    {
        taskTwo.push_back(i);
        taskTwo.push_back(i);
        taskTwo.push_back(i);
    }

    std::vector<int>::const_iterator it;
    it = taskTwo.begin();
    
    std::set<int> unique;
    while (it != taskTwo.end())
    {
        unique.insert(*it);
        it++;
    }
    std::cout << "Number of unique elements: " << unique.size() << std::endl;

    return 0;
}