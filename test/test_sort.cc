#include <iostream>
#include <vector>

// 快速排序
int partition(std::vector<int> &sort_vec, int start, int end)
{
    int pos = start + 1; // partiton最重要的就是这个参考位，为了防止移动比基准值小值需要将后续元素都往后移一位复杂度太高，这里使用一个参考位交换比基准值小的数
    for (int i = start + 1; i < end; i++) {
        if (sort_vec[i] < sort_vec[start]) { 
            std::swap(sort_vec[i], sort_vec[pos]); // 如果之后元素有比基准小的，先与sort_vec[pos]交换
            pos++; // 基准元素sort_vec[start]先不动，pos值加一，后续再有比sort_vec[start]小的与sort_vec[pos]交换，直至退出循环
        }
    }
    std::swap(sort_vec[start], sort_vec[pos - 1]); // 最后sort_vec[pos - 1]左边的(包括自己)除了sort_vec[start]都比sort_vec[start]小，右边都比sort_vec[start]大，于是交换sort_vec[start]和sort_vec[pos - 1]，达到了partition函数效果
    return pos - 1;
}

void quick_sort(std::vector<int> &sort_vec, int start, int end)
{
    if (start >= end) return; // 不断二分直至start大于end
    int pos = partition(sort_vec, start, end); // 调用partition函数将元素比基准值小的划到基准值左边，比基准值大的划到基准值右边
    quick_sort(sort_vec, start, pos - 1); // 递归左边
    quick_sort(sort_vec, pos + 1, end);  // 递归右边
}


// 归并排序1
std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> tmp;
    int l = 0, r = 0;
    while (l < left.size() && r < right.size()) {
        if (left[l] <= right[r]) {
            tmp.push_back(left[l++]);
        }
        else {
            tmp.push_back(right[r++]);
        }
    }
    if (r == right.size()) {
        tmp.insert(tmp.end(), left.begin() + l, left.end());
    }
    else if (l == left.size()) {
        tmp.insert(tmp.end(), right.begin() + r, right.end());
    }
    return tmp;
}

std::vector<int> merge_sort(std::vector<int> &sort_vec)
{
    if (sort_vec.size() < 2) return sort_vec;
    int mid = sort_vec.size() / 2;
    std::vector<int> left(sort_vec.begin(), sort_vec.begin() + mid);
    std::vector<int> right(sort_vec.begin() + mid, sort_vec.end());
    return merge(merge_sort(left), merge_sort(right));
}

// 归并排序2
void merge(std::vector<int> &sort_vec, int left_s, int left_e, int right_s, int right_e)
{
    int l = left_s, r = right_s;
    std::vector<int> tmp; // 这里需要一个临时数组保存这次排序好的部分元素
    while (l <= left_e && r <= right_e) {
        if (sort_vec[l] <= sort_vec[r]) {
            tmp.push_back(sort_vec[l++]);
        }
        else {
            tmp.push_back(sort_vec[r++]);
        }
    }
    while (l <= left_e) tmp.push_back(sort_vec[l++]);
    while (r < right_e) tmp.push_back(sort_vec[r++]);
    // 排序好后再把数据复制会原数组
    for (int i = 0; i < tmp.size(); i++) {
        sort_vec[left_s + i] = tmp[i];
    }
    return;
}

void merge_sort(std::vector<int> &sort_vec, int start, int end)
{
    if (start >= end) return;
    int mid = (start + end) / 2;
    merge_sort(sort_vec, start, mid); // 归并排序左半部分
    merge_sort(sort_vec, mid + 1, end); // 归并排序右半部分
    merge(sort_vec, start, mid, mid + 1, end); // 合并
}

int main()
{
    std::vector<int> sort_vec = {3,2,3,5,6,9,2,6,3,2,23,43,64,21,4};
    merge_sort(sort_vec, 0 , sort_vec.size() - 1);
    for (auto iter : sort_vec) {
        std::cout << iter << " ";
    }
    std::cout << "\n";
    return 0;
}
