#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Activity
{
	int start;
	int end;
};

bool Compare(struct Activity a, struct Activity b)
{
	// TODO:
	return false;
}

void Print(vector<Activity>& activities)
{
	if (activities.empty())
	{
		cout << "Empty." << endl;
		return;
	}

	vector<int> temp(activities.size() * 2);
	memcpy(&temp[0], &activities[0], sizeof(int) * temp.size());
	int min_time = *std::min_element(temp.begin(), temp.end());
	int max_time = *std::max_element(temp.begin(), temp.end());

	for (int i = min_time; i <= max_time; i++)
		cout << i % 10;
	cout << endl;
	for (auto a : activities)
	{
		for (int i = min_time; i <= max_time; i++)
			cout << (a.start <= i && i <= a.end ? "#" : " ");
		cout << " (" << a.start << ", " << a.end << ")" << endl;
	}
	cout << endl;
}

vector<Activity> GreedyActivitySelection(vector<Activity>& activities)
{
	sort(activities.begin(), activities.end(), Compare);

	Print(activities);

	vector<Activity> schedule;

	// TODO:

	return schedule;
}

int main()
{
	vector<Activity> activities =
	{ {5, 7}, {2, 5}, {6, 13}, {1, 8}, { 6, 9 }, {3, 8}, {9, 11}, {5, 12}, {8, 10}, {1, 4}, {3, 6}, {8, 14}, {13, 15} };

	Print(activities);

	auto schedule = GreedyActivitySelection(activities);

	cout << schedule.size() << " activities selected." << endl;
	Print(schedule);

	return 0;
}

// CS161 예제에서는 끝나는 시간이 포함이고 CLRS p.422에서는 half-open이라서 끝나는 시간 미포함입니다.
// 여기서는 CS161 방식이 더 직관적이라서 그대로 사용하였습니다. 예) {5, 12}이면 12도 활동 시간에 포함