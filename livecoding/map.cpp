#include <map>
#include <iostream>
#include <string>


int main()
{
    using MyMap = std::map<int, std::string>;
    MyMap m{
        {0, "null"},
        {1, "eins"},
    };

    // inserting
    {
        m[2] = "zwei"; // new element
        m[1] = "one";  // overwrite existing element

        // c++98 (old) style
        {
            std::pair<MyMap::iterator, bool> maybe_inserted = m.insert(std::make_pair(2, "two"));
            if (maybe_inserted.second)
                std::cout << "2 inserted as 'two'" << std::endl;
            else {
                std::cout << "2 NOT inserted as 'two'" << std::endl;
                std::cout << "  ... iterator is (" << maybe_inserted.first->first << ',' << maybe_inserted.first->second << ')' << std::endl;
            }
        }

        // c++17 structured binding style
        {
            auto [iter, inserted] = m.insert(std::make_pair(2, "two"));
            if (inserted)
                std::cout << "2 inserted as 'two'" << std::endl;
            else {
                std::cout << "2 NOT inserted as 'two'" << std::endl;
                std::cout << "  ... iterator is (" << iter->first << ',' << iter->second << ')' << std::endl;
            }
        }
    }

    // searching
    {
        std::cout << "[1]: " << m[1] << std::endl;
        
        std::cout << m.size() << std::endl;
        auto found = m.find(1);
        if (found == m.end())
            std::cout << "1 not found" << std::endl; 
        else
            std::cout << found->second << std::endl;

        found = m.find(666);
        if (found == m.end())
            std::cout << "666 not found" << std::endl; 
        else
            std::cout << found->second << std::endl;

        std::cout << m.size() << std::endl;
    }

    return 0;
}
