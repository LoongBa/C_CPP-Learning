#include <iostream>
#include <fstream>

using namespace std;

int main() {

    typedef long long ll; // 定义长整型别名，方便处理大数

    ifstream fin("road2.in"); // 输入文件流，用于读取输入数据
    ofstream fout("road2.out"); // 输出文件流，用于写入输出数据

    int n, d; // n为站点数，d为每单位油料能行驶的距离
    fin >> n >> d; // 从文件中读取n和d
    ll distances[n - 1]; // 使用原生数组存储每段距离
    ll prices[n]; // 使用原生数组存储每个站点油价

    // for (int i = 0; i < n - 1; ++i) {
    //     fin >> distances[i]; // 读取每段距离
    // }    
    // for (int i = 0; i < n; ++i) {
    //     fin >> prices[i]; // 读取每个站点的油价
    // }
    for (ll& distance : distances) 
        fin >> distance; // 读取每段距离
    for (ll& price : prices) 
        fin >> price; // 读取每个站点的油价

    ll totalCost = 0; // 总花费初始化为0
    ll lowestPrice = prices[0]; // 当前油价初始化为第一个站点的油价
    ll restDistance = 0; // 剩余可行驶距离初始化为0

    for (int i = 0; i < n - 1; ++i) {
        cout << "#" << i << endl;
        cout << "Distance:\t" << distances[i] << " - " << restDistance << " = " << (distances[i] - restDistance) << endl; // 输出当前段所需行驶距离到控制台
        cout << "Lowest Price:\t" << lowestPrice << "\tNow/Next Price: " << prices[i] << "/" << prices[i + 1] << endl; // 输出当前油价到控制台
        ll distance = distances[i] - restDistance; // 计算当前段所需行驶距离，考虑剩余可行驶距离
        ll fuel = (distance + d - 1) / d; // 计算需要购买的油料量，向上取整
        ll cost = fuel * lowestPrice;
        cout << "Cost:\t\t" << fuel << " * " << lowestPrice << " = " << cost << endl; // 输出当前段油料花费到控制台
        cout << "Total Cost:\t" << totalCost << " + " << cost << " = " << totalCost + cost << endl; // 输出总花费到控制台
        totalCost += cost; // 累加当前段的油料花费
        restDistance = fuel * d - distance; // 更新剩余可行驶距离
        cout << "Rest Distance:\t" << restDistance << endl; // 输出剩余可行驶距离到控制台
        cout << "-----------------------------" << endl; // 输出分隔线到控制台

        // 如果下一站的油价更低，更新当前油价
        //lowestPrice = min(lowestPrice, prices[i + 1]);
        if( lowestPrice > prices[i + 1])
        {
            lowestPrice = prices[i + 1];
            cout << "*** [" << i << "] Lowest Price Updated to: " << lowestPrice << endl;
        }
    }

    cout << totalCost << endl; // 输出总花费到控制台
    cout.flush(); // 刷新输出缓冲区
    fout << totalCost << endl; // 输出总花费到文件

    fin.close(); // 关闭输入文件流
    fout.close(); // 关闭输出文件流

    return 0; // 返回0表示程序正常结束
}