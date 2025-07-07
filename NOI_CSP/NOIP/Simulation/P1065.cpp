#include <iostream>
#include <vector>
#include <algorithm>
#define INT32_MAX 2147483647
using namespace std;

// 区间结构体，表示机器被占用的时间段
struct Slot {
    int start, end;
    Slot(int s, int e) : start(s), end(e) {}
};

// 查找可插入的最早空闲时间段的起点
int findInsertSlot(const vector<Slot>& intervals, int earliestStart, int duration) {
    for (size_t i = 0; i <= intervals.size(); ++i) {
        int prevEnd = (i == 0) ? 0 : intervals[i-1].end;
        int nextStart = (i == intervals.size()) ? INT32_MAX : intervals[i].start;
        int slotStart = max(prevEnd, earliestStart);
        int slotEnd = nextStart;
        if (slotEnd - slotStart >= duration) {
            return slotStart;
        }
    }
    return -1; // 理论上不会发生
}

// 在 intervals 中插入一个新的 Slot，保持有序
void insertSlot(vector<Slot>& intervals, int startTime, int endTime, int earliestStart, int duration) {
    for (size_t i = 0; i <= intervals.size(); ++i) {
        int prevEnd = (i == 0) ? 0 : intervals[i-1].end;
        int nextStart = (i == intervals.size()) ? INT32_MAX : intervals[i].start;
        int slotStart = max(prevEnd, earliestStart);
        int slotEnd = nextStart;
        if (slotStart == startTime && slotEnd - slotStart >= duration) {
            intervals.insert(intervals.begin() + i, Slot(startTime, endTime));
            break;
        }
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    vector<int> order(m * n);
    // 读取任务顺序
    for (int i = 0; i < m * n; ++i) cin >> order[i];

    // machineForStep[j][k] 表示第j个工件第k道工序所用机器编号
    vector<vector<int>> machineForStep(n + 1, vector<int>(m + 1));
    // durationByStep[j][k] 表示第j个工件第k道工序所需时间
    vector<vector<int>> durationByStep(n + 1, vector<int>(m + 1));
    // 读取每台机器的每一步骤的机器编号
    for (int j = 1; j <= n; ++j)
        for (int k = 1; k <= m; ++k)
            cin >> machineForStep[j][k];
    // 读取每台机器的每一步骤的持续时间
    for (int j = 1; j <= n; ++j)
        for (int k = 1; k <= m; ++k)
            cin >> durationByStep[j][k];

    // 每台机器的已占用区间
    vector<vector<Slot>> machineSlots(m + 1);
    // currentStep[j] 表示第j个工件当前要做的工序编号
    vector<int> currentStep(n + 1, 1);
    // lastStepEndTime[j] 表示第j个工件上一步工序的结束时间
    vector<int> lastStepEndTime(n + 1, 0);

    // 遍历任务顺序
    for (int jobId : order) {
        int step = currentStep[jobId];
        int machineId = machineForStep[jobId][step];
        int duration = durationByStep[jobId][step];
        int earliestStart = lastStepEndTime[jobId];

        auto& intervals = machineSlots[machineId]; // 获取该机器的已占用区间
        int startTime = findInsertSlot(intervals, earliestStart, duration);
        int endTime = startTime + duration; // 计算结束时间
        // 如果找不到合适的插入位置，说明需要等待
        insertSlot(intervals, startTime, endTime, earliestStart, duration);
        
        lastStepEndTime[jobId] = endTime;
        currentStep[jobId]++;
    }

    // 统计所有机器的最大结束时间
    int totalTime = 0;
    for (int i = 1; i <= m; ++i) {
        if (!machineSlots[i].empty())
            totalTime = max(totalTime, machineSlots[i].back().end);
    }
    cout << totalTime << endl;
    return 0;
}