#include <iostream>  
#include<map>
#include<set>
#include <algorithm>
#define N 50
using namespace std;

int page[N];//页面引用号 
int block[N];//物理块，内存 
int dist[N][N];//表示第i次访问内存的时候，内存中的页面j 在以后被访问的最小时间 

int n;//页面引用号个数 
int m;//物理块数目 
int page_max;//最大页面号 

int nru[N];// i 最近时候被访问过 
int page_in_block[N];//页面 i 在 block的下标索引 
int NRU(){
	int index = 1;
	int page_lack = 0;
	memset(block, -1, sizeof(block));
	for (int i = 1; i <= n; ++i){
		if (page_in_block[page[i]]){// page[i]已经在内存中 
			nru[page_in_block[page[i]]] = 1;//重新标记被访问的页面			cout << endl << "第" << i << "次: 页面" << page[i] << "已经存在物理块" << page_in_block[page[i]] << "中" << endl;
		}
		else {
			while (true){
				if (index > m) index = 1;
				if (block[index] == -1) {
					nru[index] = 1;
					page_in_block[page[i]] = index;
					block[index++] = page[i];
					//cout << "页面" << page[i] << "不在内存，直接放入物理块" << j << "中" << endl;
					++page_lack;
					break;
				}
				if (block[index] == page[i]){
					nru[index++] = 1;
					break;
				}
				else {
					index = 1;
					if (nru[index] == 0){//替换该页面 
						nru[index] = 1;
						page_in_block[block[index]] = 0;
						cout << endl << "第" << i << "次: 物理块" << index << "中的页面" << block[index] << "最近未被使用，将要被页面" << page[i] << "替换" << endl;
						page_in_block[page[i]] = index;
						block[index++] = page[i];
						++page_lack;
						break;
					}
					else
						nru[index++] = 0;
				}
			}
		}
		for (int k = 1; k <= m; ++k)
			cout << block[k] << " ";
		cout << endl;
	}
	return page_lack;
}

int pre[N];//page[i]在page中的索引
int opt(){//最佳页面置换算法 
	int page_lack = 0;
	memset(pre, 0, sizeof(pre));
	memset(dist, 0x3f, sizeof(dist));
	memset(block, -1, sizeof(block));
	for (int i = n; i >= 1; --i){
		for (int j = 0; j <= page_max; ++j)
		if (pre[j])
			dist[i][j] = pre[j] - i;
		pre[page[i]] = i;
	}

	for (int i = 1; i <= n; ++i){ 
		int j;
		int max_dist = 0, p;
		for (j = 1; j <= m; ++j){
			if (block[j] == -1){//直接放入, 产生缺页 
				block[j] = page[i];
				page_lack++;
				break;
			}
			else if (block[j] == page[i])//存在内存中 
				break;

			if (max_dist < dist[i][block[j]]){
				max_dist = dist[i][block[j]];//block[j] 对应的页面以后会长时间不会用到 
				p = j;//block[] 第j个页面会被替换掉 
			}
		}
		if (j > m){//页面替换 
			cout << "页面" << page[i] << "不在内存，将物理块" << p << "中的页面" << block[p] << "替换" << endl;
			block[p] = page[i];
			page_lack++;
		}
		//cout << endl << "当前内存中页面的情况:" << endl;
		for (int k = 1; k <= m; ++k) 
			cout << block[k] << " ";
		cout << endl << endl;
	}
	return page_lack;//返回缺页次数 
}

int main(){
	cout << "请输入进程个数" << endl;
	cin >> n ;
	cout << "请输入内存可以控制的页面数" << endl;
	cin>> m;
	cout << "请输入" << n << "进程需要的页面数,以空格隔开"<<endl;
	for (int i = 1; i <= n; ++i){
		cin >> page[i];
		page_max = max(page_max, page[i]);
	}
	cout << "***********************************" << endl;
	cout << "最近没有使用页面淘汰算法NRU" << endl;
	cout << "缺页中断次数:" << NRU() << endl;
	cout << endl<<"***********************************" << endl;
	cout << "理想型淘汰算法OPT" << endl;
	cout << "缺页中断次数:" << opt() << endl;
	
	system("pause");
	return 0;
}
