    #include <iostream>
    #include <thread>
    #include <vector>

    using namespace std;

    void min_elem(vector<int> const& elements, vector<int>& min, const int l, const int r, const int i) {
        int min_el = elements[l];

        for (int j = l; j <= r; ++j)
        {
            if (elements[j] < min_el)
                min_el = elements[j];
        }
        min[i] = min_el;
    }

    void max_elem(vector<int> const& elements, vector<int>& max, const int l, const int r, const int i) {
        int max_el = elements[l];

        for (int j = l; j <= r; ++j)
        {
            if (elements[j] > max_el)
                max_el = elements[j];
        }
        max[i] = max_el;
    }

    int main() {
        int th_n, el_n;
        cout << "Enter threads number: \n";
        cin >> th_n;
        cout << "Enter number of elements and each element: \n";
        cin >> el_n;

        vector<int> elements(el_n);
        vector<int> min(th_n);
        vector<int> max(th_n);
        vector<thread> threads(th_n);

        for (int i = 0; i < el_n; ++i)
            cin >> elements[i];

        int l = 0;
        int delta = el_n / th_n;
        int last_id = th_n - 1;

        for (int i = 0; i < th_n; ++i)
        {
            if (i != last_id)
            {
                threads[i] = thread(min_elem, ref(elements), ref(min), l, l + delta - 1, i);
                l += delta;
            } else
            {
                threads[i] = thread(min_elem, ref(elements), ref(min), l, el_n - 1, i);
            }
        }

        for (int i = 0; i < th_n; ++i)
        {
            threads[i].join();
        }

        cout << "min elements for each thread:" << endl;
        for (int i = 0; i < th_n; ++i)
            cout << min[i] << ' ';

        cout << endl;

        int ans_min = min[0];
        for (int i = 1; i < th_n; ++i)
            if (min[i] < ans_min)
                ans_min = min[i];

        cout << "min element: " << ans_min << endl;
        
        threads.clear();
        l = 0;

        for (int i = 0; i < th_n; ++i)
        {
            if (i != last_id)
            {
                threads[i] = thread(max_elem, ref(elements), ref(max), l, l + delta - 1, i);
                l += delta;
            } else
            {
                threads[i] = thread(max_elem, ref(elements), ref(max), l, el_n - 1, i);
            }
        }

        for (int i = 0; i < th_n; ++i)
        {
            threads[i].join();
        }

        cout << "max elements for each thread:" << endl;
        for (int i = 0; i < th_n; ++i)
            cout << max[i] << ' ';

        cout << endl;

        int ans_max = max[0];
        for (int i = 1; i < th_n; ++i)
            if (max[i] > ans_max)
                ans_max = max[i];
        cout << "max element: " << ans_max << endl;
    }