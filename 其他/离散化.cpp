vector<int> alls;
sort(alls.begin(), alls.end());
alls.erase(unique(alls.begin(), alls.end()), alls.end());
int find(int x) {
    return lower_bound(alls.begin(), alls.end(), x) - alls.begin();
}