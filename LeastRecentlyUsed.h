#include <tuple>
#pragma once
class LeastRecentlyUsed
{
public:
	static std::tuple<int, int, int>  LRU(); //funkcja zwracająca krotkę, która zawiera illość błędów stron i ilość sukcesów. 
										//krotka jest potrzebna, żeby zwrócić trzy watrości z jednej funkcji
};

