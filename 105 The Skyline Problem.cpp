#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

class Ve {
public:
	Ve(int x, int y, int open) : x(x), y(y), open(open), y_stack(0) {}

	int x;
	int y;

	bool open;

	int y_stack;
};



int main() {
	
	stringstream ss;
	string str;

	list<Ve> l;

	auto last_v1x_inserted = l.begin();

	//ifstream f("in12.txt");

	//cin.rdbuf(f.rdbuf());

	while (!cin.eof()) {
		
		getline(cin, str);

		if (str.size() == 0) break;

		ss << str;

		int L, H, R;

		ss >> L >> H >> R;

		ss.clear();

		Ve v1( L, H, true );
		Ve v2( R, H, false );

		bool isCovered = false;

		// wierzcho³ek otwieraj¹cy
		auto it = last_v1x_inserted;
		while (it != l.end()) {

			
			if (it->x == L) {

				// wierzcho³ek poni¿ej jest usuniêty
				if (it->y <= H) {

					list<Ve>::iterator tmp = it;
					it++;

					l.erase(tmp);

					break; //brak krycia --- isCovered = false

				}

				// wierzcho³ek jest kryty, nie wyjdzie z krycia

				isCovered = true;

				break;
			}

			

			if (it->x > L ) {
				if (it->y >= H) isCovered = true;
				break;
			}

			it++;

		}

		if (!isCovered) {
			last_v1x_inserted = l.insert(it, v1);
		}

		auto it_v2 = last_v1x_inserted;
		if (!isCovered) {
			it_v2++;
		}

		isCovered = false;

		//wierzcho³ek zamykaj¹cy
		while (it_v2 != l.end()) {

			if (it_v2->x > R) {
				if (it_v2->y >= H) {
					isCovered = true; break;
				}
				if (it_v2->open == false) {
					v2.y_stack = it_v2->y;
				}
				break;
			}

			if (it_v2->x == R && it_v2->y >= H) {
				isCovered = true; break;
			}
			
			if (it_v2->y <= H) {
				list<Ve>::iterator tmp = it_v2;
				it_v2++;
				l.erase(tmp);
				continue;
			}
			else {
				if(it_v2->y_stack < H)
				it_v2->y_stack = H;
			}

			it_v2++;

		}

		if (!isCovered) {
			l.insert(it_v2, v2);
		}
	}

	auto end = l.end();
	end--;

	for (auto it = l.begin(); it != end; it++) {

		if (it->open == true) {
			cout << it->x << " " << it->y << " ";
		}
		else {
			cout << it->x << " " << it->y_stack << " ";
		}
	}

	if (end->open == true) {
		cout << end->x << " " << end->y;
	}
	else {
		cout << end->x << " " << end->y_stack;
	}

	cout << endl;
}