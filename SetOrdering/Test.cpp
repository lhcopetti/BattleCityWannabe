#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

class TTT
{
	int _coords;
	int _cost;

public:

	TTT(int coords, int cost) { _coords = coords; _cost = cost; };

	friend bool operator==(const TTT l, const TTT r)
	{
		return l.coords() == r.coords();
	}

	int coords() const { return _coords; };
	int cost() const { return _cost; };
};

struct OrderTTT
{
	bool operator()(TTT* l, TTT* r)
	{
		return l->coords() > r->coords();
	}
};

bool lowestCost(const TTT* l, const TTT* r)
{
	return l->cost() < r->cost();
}

bool isEqual(const TTT* l, const TTT* r)
{
	return l->coords() == r->coords();

}

class myFuncObj
{
public:
	myFuncObj(TTT& t) { _coord = t.coords(); };

	bool operator()(const TTT* t) const { return _coord == t->coords(); };

private:
	int _coord;
};

int main()
{
	set<TTT*, OrderTTT> mySet{ new TTT(10, 25), new TTT(11, 100), new TTT(12, 15), new TTT(13, 20) };
	cout << "Count is: " << mySet.size() << endl;

	TTT* test = new TTT(10,9);

	std::for_each(mySet.begin(), mySet.end(), [](TTT * t) {cout << "Coords: " << t->coords() << "; Cost: " << t->cost() << endl; });

	cout << "Something is going to HAPPEN!" << endl;

	auto myIter = std::min_element(mySet.begin(), mySet.end(), lowestCost);
	
	mySet.erase(myIter);

	std::for_each(mySet.begin(), mySet.end(), [](TTT * t) {cout << "Coords: " << t->coords() << "; Cost: " << t->cost() << endl; });

//	auto myIter = std::find_if(mySet.begin(), mySet.end(), isEqual);
	//auto myIter = std::find_if(mySet.begin(), mySet.end(), myFuncObj(*test));
	//if (myIter == mySet.end())
	//	mySet.insert(test);
	//else
	//{
	//	cout << "Found a match!" << endl;
	//	if (test->cost() < (*myIter)->cost())
	//	{
	//	//	(*myIter)->update(newCost, newParent);
	//	}
	//}
	std::for_each(mySet.begin(), mySet.end(), [](TTT * t) {cout << "Coords value: " << t->coords() << "; Cost: " << t->cost() << endl; });
	//TTT* minValue = *std::min_element(mySet.begin(), mySet.end());

	//cout << "Min value is: " << minValue->value() << endl;
	//cout << "First Element is: " << (*mySet.begin())->value() << endl;
	//cout << "Last Element is: " << (*--mySet.end())->value() << endl;

	//mySet.insert(new TTT(2));
	//mySet.insert(new TTT(4));
	//mySet.insert(new TTT(2));
	//mySet.insert(new TTT(4));
	//	mySet.insert(new TTT(2));
	//mySet.insert(new TTT(4));

	//cout << "Min value is: " << minValue->value() << endl;
	//cout << "First Element is: " << (*mySet.begin())->value() << endl;
	//cout << "Count is: " << mySet.size() << endl;
}
