#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int n;

const int INF = 1e9;//khai báo hằng
int dijkstra(map<string, vector<pair<string, int>>> graph, string start, string end){
    map<string, int> distance;
    for (auto it : graph){
        distance[it.first] = INF;//cho khoảng cách đỉnh còn lại là inf
    }
    distance[start] = 0;//gán đỉnh bắt đầu bằng 0

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq; //Hàng đợi ưu tiên
    pq.push(make_pair(0, start));


    // Lưu đường đi ngắn nhất
    map<string, string> previous;
    previous[start] = start;

    while (!pq.empty()) {
        string current = pq.top().second;
        pq.pop();
        if (current == end) {
            // In ra đường đi ngắn nhất
            vector<string> path;
            string vertex = end;
            while (vertex != start) {//tìm các đỉnh trung gian push vào path
                path.push_back(vertex);
                vertex = previous[vertex];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            cout << "Duong di ngan nhat tu " << start << " den " << end << " la: ";
            for (const auto& v : path) {
                cout << v << " -> ";
            }
            cout << "END" << endl;
            return distance[current];
        }

        for (auto it : graph[current]) {
            string neighbor = it.first;
            int weight = it.second;
            if (distance[current] + weight < distance[neighbor]) {
                distance[neighbor] = distance[current] + weight;
                pq.push(make_pair(distance[neighbor], neighbor));
                // Lưu đường đi ngắn nhất
                previous[neighbor] = current;
            }
        }
    }
}

int InputandMin_City(map<string, vector<pair<string, int>>> graph, string start, string end) {
    // Khởi tạo đồ thị bằng cách đọc đầu vào
    int n; //Nhập tổng số đường đi của các thành phố
    int m;
    cout << "Nhap tong so duong di cua cac thanh pho: ";
    cin >> n;

    // map<string, vector<pair<string, int>>> graph;
    for (int i = 0; i < n; i++) {
        string city1, city2; //2 thành phố có quãng đường qua nhau
        int distance;          //độ dài quãng đường của 2 thành phố
        cin >> city1 >> city2 >> distance;

        graph[city1].push_back(make_pair(city2, distance));
        graph[city2].push_back(make_pair(city1, distance));
    }
    do {
        cout << "Nhap so luot kiem tra hoac nhap 0 de thoat: ";
        cin >> m;
        if (m == 0) {
            return 0;
        }
        else {
            cout << "Nhap ten thanh pho xuat phat: ";
            cin >> start;
            cout << "Nhap ten thanh pho den: ";
            cin >> end;

            int shortest_distance = dijkstra(graph, start, end);

            // In ra kết quả
            if (shortest_distance == -1) {
                cout << "Khong co duong di giua hai thanh pho nay\n";
            }
            else {
                cout << "Quang duong ngan nhat giua " << start << " va " << end << " la " << shortest_distance << " km\n";
            }
        }
    } while (m != 0);

}
int main() {
    map<string, vector<pair<string, int>>> graph;
    string start;
    string end;
    InputandMin_City(graph, start, end);
    return 0;
}

