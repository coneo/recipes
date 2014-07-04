#include <set>
#include <iostream>

class Rank
{
public:
	Rank() : level(0),time(0),id(0)
	{
	}
	Rank(int _level, int _time, int _id) : level(_level),time(_time),id(_id)
	{
	}
	bool operator==(Rank* a);
	~Rank()
	{
	}
public:
	int level;
	int time;
	int id;
};

bool Rank::operator == (Rank *a)
{
		return (a->level==this->level && a->time==this->time && a->id==this->id);
}

struct Compare
{
		bool operator () (Rank* a, Rank *b)
		{
				return (a->level!=b->level)?(a->level < b->level):(a->time > b->time);
		}
};

int main(int argc, char**argv)
{
		std::set<Rank*, Compare> ranks;
		//std::set<Rank*> ranks;

		int id = 0;
		for (int i = 0; i < 3; ++i,++id)
		{
				Rank *data = new Rank(2,3,id);
				if (data)
				{
						ranks.insert(data);
				}
		}
		//print 
		std::cout << "ranks.size=" << ranks.size() << std::endl;

		//release resources
		std::set<Rank*, Compare>::iterator last = ranks.end();
		for (std::set<Rank*,Compare>::iterator it = ranks.begin(); it!=last;++it)
		{
				if (*it)
						delete (*it);
				ranks.erase(it);
		}
}
