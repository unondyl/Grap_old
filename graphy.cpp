#include <bits/stdc++.h>

using namespace std;

// bool add_color()
// {
      
// }

int main()
{
      cin.tie(0)->sync_with_stdio(0);
      freopen("fin.inp","r",stdin);
      ofstream out("data.js");
      out << "const graphData = {\n";
      out << "  edges: [\n";
      int size_x=0,x,y;
      int a[710][710];
      while(scanf("%d%d",&x,&y)!=EOF)
      {
            //if (x==NULL && y==NULL) break;
            out << "{ from: " << x << ", to: " << y << " }, \n";
            a[x][y]=1;a[y][x]=1;
            cout<<x<<" "<<y<<endl;
            size_x=max(size_x,max(x,y));
      }
      out << "  ],\n";
      //
      multimap<int,int> level_a;
      for(int inter=0;inter<size_x;inter++)
      {
            int count_level=0;
            for(int i=1;i<=size_x;i++) count_level+=a[inter+1][i];
            level_a.insert(make_pair(count_level,inter+1));
      }
      //
      vector<int> f(size_x+2,0);
      map<int, vector<int> > color;
      int icol=1;
      //
      for (auto i = level_a.rbegin(); i != level_a.rend(); i++) {
            int u = i->second; // Đỉnh gốc đang xét
            
            if (!f[u]) { // Nếu đỉnh u chưa có màu
                  vector<int> col;
                  f[u] = icol;
                  col.push_back(u);
                  // Tạo mảng đánh dấu chặn cho RIÊNG màu 'icol' hiện tại
                  // blocked[v] = true nghĩa là đỉnh v kề với ít nhất 1 đỉnh đã có màu 'icol'
                  vector<bool> blocked(size_x + 2, false);

                  // Đánh dấu chặn các đỉnh kề với u
                  for(int v = 1; v <= size_x; v++) {
                        if(a[u][v]) blocked[v] = true;
                  }

                  // Duyệt các đỉnh tiếp theo có bậc nhỏ hơn u
                  auto next_it = i; 
                  next_it++; // Bỏ qua đỉnh u, bắt đầu từ đỉnh ngay sau nó
                  for (auto x = next_it; x != level_a.rend(); x++) {
                        int curr = x->second;

                        // Nếu curr chưa có màu VÀ không bị đánh dấu chặn
                        if (!f[curr] && !blocked[curr]) { 
                              f[curr] = icol;       // Tô màu
                              col.push_back(curr);  // Gom vào nhóm
                        
                              // Cập nhật chặn ngay các đỉnh kề với đỉnh curr vừa được tô
                              for(int v = 1; v <= size_x; v++) {if(a[curr][v]) blocked[v] = true;}
                        }
                  }
                  color.insert(make_pair(icol++, col));
            }
      }
      for(auto pr : color)
      {
            cout<<"var: "<<pr.first<<" : "<<pr.second.size()<<" = ";
            for(auto i : pr.second) cout<<i<<" ";
            cout<<endl;
      }
      // Tạo biến toàn cục trong JS
      out << "  nodes: [\n";
      
      // Bảng màu hệ HEX
      string colors[] = {"", "#FF5733", "#33FF57", "#3357FF", "#F033FF", "#FFFF33"};
      
      for (int i = 1; i <= size_x; i++) {
            string c = (f[i] <= 5) ? colors[f[i]] : "#CCCCCC"; // Cấp màu, nếu quá 5 màu thì tô xám
            out << "    { id: " << i << ", label: 'Đỉnh " << i << "', color: '" << c << "' }";
            if (i < size_x) out << ",";
            out << "\n";
      }
      
      out << "  ]\n";
      out << "};\n";
      out.close();
      cout << "Chay thuat toan xong! Da tao file data.js thanh cong.\n";
}
