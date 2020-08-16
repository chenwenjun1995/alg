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


// 归并排序
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

int main()
{
    std::vector<int> sort_vec = {3,2,3,5,6,9,2,6,3,2,23,43,64,21,4};
    sort_vec = merge_sort(sort_vec);
    for (auto iter : sort_vec) {
        std::cout << iter << " ";
    }
    std::cout << "\n";
    return 0;
}
