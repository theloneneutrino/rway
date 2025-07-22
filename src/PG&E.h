#ifndef MYUTILS_H
#define MYUTILS_H

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <stack>
#include <functional>
#include <limits>
#include <cctype>
#include <fstream>
#include <sstream>

namespace utils {

    // ansi escape codes for console output
    namespace console_colors {
        // Made constexpr instead of const to avoid potential ODR violations
        constexpr const char* RESET = "\033[0m";
        constexpr const char* BLACK = "\033[30m";
        constexpr const char* RED = "\033[31m";
        constexpr const char* GREEN = "\033[32m";
        constexpr const char* YELLOW = "\033[33m";
        constexpr const char* BLUE = "\033[34m";
        constexpr const char* MAGENTA = "\033[35m";
        constexpr const char* CYAN = "\033[36m";
        constexpr const char* WHITE = "\033[37m";
        constexpr const char* BRIGHT_BLACK = "\033[90m";
        constexpr const char* BRIGHT_RED = "\033[91m";
        constexpr const char* BRIGHT_GREEN = "\033[92m";
        constexpr const char* BRIGHT_YELLOW = "\033[93m";
        constexpr const char* BRIGHT_BLUE = "\033[94m";
        constexpr const char* BRIGHT_MAGENTA = "\033[95m";
        constexpr const char* BRIGHT_CYAN = "\033[96m";
        constexpr const char* BRIGHT_WHITE = "\033[97m";
    }

    // common string manipulation functions
    namespace string_utils {
        // cleans a word by removing non-alphabetic characters and converting to lowercase
        inline std::string cleanWord(const std::string& word) {
            std::string cleaned;
            for (char c : word) {
                if (std::isalpha(c)) {
                    cleaned += std::tolower(c);
                }
            }
            return cleaned;
        }

        // strip punctuation but preserve case (for case-sensitive operations)
        inline std::string stripPunctuation(const std::string& word) {
            std::string cleaned;
            for (char c : word) {
                if (std::isalnum(c)) {
                    cleaned += c;
                }
            }
            return cleaned;
        }

        // get character at position d, return -1 if out of bounds
        // used in MSD and 3-way radix quicksort
        inline int charAt(const std::string& s, int d) {
            return (d < static_cast<int>(s.length())) ? s[d] : -1;
        }

        // get digit at position d from right (for LSD radix sort)
        inline int getDigit(const std::string& str, int d) {
            if (d >= static_cast<int>(str.length())) return 0;
            return str[str.length() - 1 - d] - '0';
        }

        // safe string to long conversion
        inline long stringToLong(const std::string& s) {
            try {
                return std::stol(s);
            }
            catch (...) {
                return 0;  // or handle error as needed
            }
        }

        // rolling hash for Rabin-Karp and similar algorithms
        inline long rollingHash(const std::string& key, int len, long radix, long modulus) {
            long hashVal = 0;
            for (int i = 0; i < len; i++) {
                hashVal = (hashVal * radix + key[i]) % modulus;
            }
            return hashVal;
        }

        // update rolling hash by removing old char and adding new char
        inline long updateRollingHash(long oldHash, char oldChar, char newChar,
            long rm, long radix, long modulus) {
            long hash = (oldHash + modulus - rm * static_cast<long>(oldChar) % modulus) % modulus;
            hash = (hash * radix + static_cast<long>(newChar)) % modulus;
            return hash;
        }

        // suffix comparison for sorting
        struct SuffixComparator {
            const std::string& text;
            explicit SuffixComparator(const std::string& t) : text(t) {}
            bool operator()(int i, int j) const {
                return text.substr(i) < text.substr(j);
            }
        };

        // create suffix array (indices of sorted suffixes)
        inline std::vector<int> buildSuffixArray(const std::string& text) {
            int n = static_cast<int>(text.length());
            std::vector<int> suffixes(n);
            for (int i = 0; i < n; i++) suffixes[i] = i;
            std::sort(suffixes.begin(), suffixes.end(), SuffixComparator(text));
            return suffixes;
        }
    }

    // text processing utilities
    namespace text_utils {
        // track line and column positions in text
        struct TextPosition {
            int line;
            int column;
            int absoluteIndex;
        };

        // convert absolute index to line/column
        inline TextPosition indexToPosition(const std::string& text, int index) {
            TextPosition pos = { 1, 1, index };
            for (int i = 0; i < index && i < static_cast<int>(text.length()); i++) {
                if (text[i] == '\n') {
                    pos.line++;
                    pos.column = 1;
                }
                else {
                    pos.column++;
                }
            }
            return pos;
        }

        // read file into string preserving all characters
        inline std::string readFileToString(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Cannot open file: " + filename);
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }
    }

    // common data structures
    namespace data_structures {

        // last-in, first-out stack
        template<typename T>
        class Stack {
        private:
            std::vector<T> container;
        public:
            void push(const T& value) { container.push_back(value); }
            T pop() {
                if (is_empty()) throw std::out_of_range("stack is empty");
                T value = container.back();
                container.pop_back();
                return value;
            }
            const T& top() const {
                if (is_empty()) throw std::out_of_range("stack is empty");
                return container.back();
            }
            bool is_empty() const { return container.empty(); }
            size_t size() const { return container.size(); }
        };

        // first-in, first-out queue
        template<typename T>
        class Queue {
        private:
            std::vector<T> container;
            size_t head = 0;
        public:
            void enqueue(const T& value) { container.push_back(value); }
            T dequeue() {
                if (is_empty()) throw std::out_of_range("queue is empty");
                T value = container[head++];
                if (head > container.size() / 2) {
                    container.erase(container.begin(), container.begin() + head);
                    head = 0;
                }
                return value;
            }
            const T& front() const {
                if (is_empty()) throw std::out_of_range("queue is empty");
                return container[head];
            }
            bool is_empty() const { return head >= container.size(); }
            size_t size() const { return container.size() - head; }
        };

        // priority queue (max-heap by default)
        template<typename T, typename Container = std::vector<T>, typename Compare = std::less<T>>
        class PriorityQueue {
        private:
            Container heap_container;
            Compare comp;
        public:
            explicit PriorityQueue(const Compare& compare = Compare()) : comp(compare) {}
            void push(const T& value) {
                heap_container.push_back(value);
                std::push_heap(heap_container.begin(), heap_container.end(), comp);
            }
            T pop() {
                if (is_empty()) throw std::out_of_range("priorityqueue is empty");
                std::pop_heap(heap_container.begin(), heap_container.end(), comp);
                T value = heap_container.back();
                heap_container.pop_back();
                return value;
            }
            const T& top() const {
                if (is_empty()) throw std::out_of_range("priorityqueue is empty");
                return heap_container.front();
            }
            bool is_empty() const { return heap_container.empty(); }
            size_t size() const { return heap_container.size(); }
        };

        // indexed minimum priority queue
        template <typename Key>
        class IdxMinPQ {
        private:
            int n;
            std::vector<int> pq;
            std::vector<int> qp;
            std::vector<Key> keys;

            bool greater(int i, int j) { return keys[pq[i]] > keys[pq[j]]; }

            void exch(int i, int j) {
                int temp = pq[i];
                pq[i] = pq[j];
                pq[j] = temp;
                qp[pq[i]] = i;
                qp[pq[j]] = j;
            }

            void swim(int k) {
                while (k > 1 && greater(k / 2, k)) {
                    exch(k, k / 2);
                    k = k / 2;
                }
            }

            void sink(int k) {
                while (2 * k <= n) {
                    int j = 2 * k;
                    if (j < n && greater(j, j + 1)) j++;
                    if (!greater(k, j)) break;
                    exch(k, j);
                    k = j;
                }
            }

        public:
            IdxMinPQ() : n(0) {}

            bool is_empty() { return n == 0; }

            bool contains(int i) {
                if (i < 0 || i >= static_cast<int>(qp.size())) return false;
                return qp[i] != -1;
            }

            void insert(int i, Key key) {
                if (contains(i)) throw std::invalid_argument("index is already in the priority queue");
                while (i >= static_cast<int>(keys.size())) {
                    keys.push_back(Key());
                    qp.push_back(-1);
                }
                while (pq.size() <= static_cast<size_t>(n + 1)) {
                    pq.push_back(0);
                }
                n++;
                qp[i] = n;
                pq[n] = i;
                keys[i] = key;
                swim(n);
            }

            int delMin() {
                if (n == 0) throw std::out_of_range("priority queue underflow");
                int minIndex = pq[1];
                exch(1, n--);
                sink(1);
                qp[minIndex] = -1;
                return minIndex;
            }

            void decreaseKey(int i, Key key) {
                if (!contains(i)) throw std::out_of_range("index is not in the priority queue");
                if (key > keys[i]) throw std::invalid_argument("calling decreaseKey() with a strictly greater key");
                keys[i] = key;
                swim(qp[i]);
            }
        };

        // double-ended queue
        template <typename T>
        class Deque {
        private:
            std::vector<T> container;
            size_t head = 0, tail = 0, count = 0;
            void resize() {
                std::vector<T> new_container(container.size() * 2);
                for (size_t i = 0; i < count; ++i) {
                    new_container[i] = container[(head + i) % container.size()];
                }
                container = std::move(new_container);
                head = 0;
                tail = count;
            }
        public:
            explicit Deque(size_t initial_capacity = 8) : container(initial_capacity) {}
            void push_back(const T& value) {
                if (count == container.size()) resize();
                container[tail] = value;
                tail = (tail + 1) % container.size();
                count++;
            }
            void push_front(const T& value) {
                if (count == container.size()) resize();
                head = (head == 0) ? container.size() - 1 : head - 1;
                container[head] = value;
                count++;
            }
            T pop_back() {
                if (is_empty()) throw std::out_of_range("deque is empty");
                tail = (tail == 0) ? container.size() - 1 : tail - 1;
                T value = container[tail];
                count--;
                return value;
            }
            T pop_front() {
                if (is_empty()) throw std::out_of_range("deque is empty");
                T value = container[head];
                head = (head + 1) % container.size();
                count--;
                return value;
            }
            bool is_empty() const { return count == 0; }
            size_t size() const { return count; }
        };

        // circular queue (overwrites oldest element when full)
        template <typename T>
        class CircularQueue {
        private:
            std::vector<T> container;
            size_t head = 0, tail = 0, count = 0, capacity;
        public:
            explicit CircularQueue(size_t cap) : capacity(cap), container(cap) {}
            void enqueue(const T& value) {
                container[tail] = value;
                tail = (tail + 1) % capacity;
                if (count < capacity) {
                    count++;
                }
                else {
                    head = (head + 1) % capacity;
                }
            }
            T dequeue() {
                if (is_empty()) throw std::out_of_range("circularqueue is empty");
                T value = container[head];
                head = (head + 1) % capacity;
                count--;
                return value;
            }
            bool is_empty() const { return count == 0; }
            bool is_full() const { return count == capacity; }
            size_t size() const { return count; }
        };
    }

    // graph-related data structures and algorithms
    namespace graph {

        // an unweighted directed edge from v to w
        class directed_edge {
        private:
            unsigned int v, w;
        public:
            directed_edge(unsigned int a, unsigned int b) : v(a), w(b) {}
            unsigned int from() const { return v; }
            unsigned int to() const { return w; }
        };

        // an unweighted directed graph
        class digraph {
        private:
            unsigned int V_count, E_count;
            std::vector<std::vector<directed_edge>> adj_list;
        public:
            explicit digraph(unsigned int n) : V_count(n), E_count(0), adj_list(n) {}
            unsigned int V() const { return V_count; }
            void add_edge(const directed_edge& e) {
                if (e.from() < V_count && e.to() < V_count) {
                    adj_list[e.from()].push_back(e);
                    E_count++;
                }
            }
            const std::vector<directed_edge>& adj(unsigned int v) const {
                if (v >= V_count) throw std::out_of_range("vertex out of range");
                return adj_list[v];
            }
        };

        // a weighted directed edge
        class DirectedEdge {
        private:
            int v_node, w_node;
            double wt;
        public:
            DirectedEdge(int v = -1, int w = -1, double weight = 0.0) : v_node(v), w_node(w), wt(weight) {}
            int from() const { return v_node; }
            int to() const { return w_node; }
            double weight() const { return wt; }
        };

        // an edge-weighted directed graph
        class EdgeWeightedDigraph {
        private:
            int V_count, E_count;
            std::vector<std::vector<DirectedEdge>> adj_list;
        public:
            explicit EdgeWeightedDigraph(int V) : V_count(V), E_count(0), adj_list(V) {}
            int getV() const { return V_count; }
            void addEdge(const DirectedEdge& e) {
                adj_list[e.from()].push_back(e);
                E_count++;
            }
            const std::vector<DirectedEdge>& getAdj(int v) const {
                return adj_list[v];
            }
        };

        // weighted undirected edge (for MST and other graph algorithms)
        class WeightedEdge {
        private:
            int v_node, w_node;
            double wt;
        public:
            WeightedEdge(int v = -1, int w = -1, double weight = 0.0)
                : v_node(v), w_node(w), wt(weight) {
            }
            int either() const { return v_node; }
            int other(int vertex) const {
                return (vertex == v_node) ? w_node : v_node;
            }
            double weight() const { return wt; }
            bool operator<(const WeightedEdge& e) const { return wt < e.wt; }
            bool operator>(const WeightedEdge& e) const { return wt > e.wt; }
        };

        // edge relaxation for shortest path algorithms
        template<typename Edge>
        bool relax(const Edge& e, std::vector<double>& distTo,
            std::vector<Edge>& edgeTo) {
            int v = e.from(), w = e.to();
            if (distTo[w] > distTo[v] + e.weight()) {
                distTo[w] = distTo[v] + e.weight();
                edgeTo[w] = e;
                return true;  // Edge was relaxed
            }
            return false;  // No relaxation needed
        }
    }

    // common algorithms
    namespace algorithms {

        // topological sort using depth-first search
        class depth_first_order {
        private:
            std::vector<bool> marked;
            std::stack<unsigned int> reverse_post_order;
            void depth_first(const utils::graph::digraph& g, unsigned int v) {
                marked[v] = true;
                for (const auto& edge : g.adj(v)) {
                    unsigned int w = edge.to();
                    if (!marked[w]) depth_first(g, w);
                }
                reverse_post_order.push(v);
            }
        public:
            explicit depth_first_order(const utils::graph::digraph& g) {
                marked.resize(g.V(), false);
                for (unsigned int v = 0; v < g.V(); ++v) {
                    if (!marked[v]) depth_first(g, v);
                }
            }
            std::stack<unsigned int> get_topological_sorted_digraph() const {
                return reverse_post_order;
            }
        };

        // dijkstra's algorithm for shortest paths
        class DijkstraSP {
        private:
            std::vector<graph::DirectedEdge> edgeTo;
            std::vector<double> distTo;
            data_structures::IdxMinPQ<double> pq;

            void relax(const graph::EdgeWeightedDigraph& G, int v) {
                for (const auto& e : G.getAdj(v)) {
                    int w = e.to();
                    if (distTo[w] > distTo[v] + e.weight()) {
                        distTo[w] = distTo[v] + e.weight();
                        edgeTo[w] = e;
                        if (pq.contains(w)) pq.decreaseKey(w, distTo[w]);
                        else pq.insert(w, distTo[w]);
                    }
                }
            }

        public:
            DijkstraSP(const graph::EdgeWeightedDigraph& G, int source) :
                edgeTo(G.getV()),
                distTo(G.getV(), std::numeric_limits<double>::infinity()) {
                distTo[source] = 0.0;
                pq.insert(source, 0.0);
                while (!pq.is_empty()) {
                    relax(G, pq.delMin());
                }
            }
            double distanceTo(int v) const { return distTo[v]; }
        };

        // KMP string searching algorithm
        class KMP {
        private:
            std::string pattern;
            std::vector<int> lps;
            void buildLPS() {
                int m = static_cast<int>(pattern.length());
                lps.resize(m, 0);
                int len = 0;
                int i = 1;
                while (i < m) {
                    if (pattern[i] == pattern[len]) {
                        len++;
                        lps[i] = len;
                        i++;
                    }
                    else {
                        if (len != 0) len = lps[len - 1];
                        else {
                            lps[i] = 0;
                            i++;
                        }
                    }
                }
            }
        public:
            explicit KMP(const std::string& pat) : pattern(pat) { buildLPS(); }
            int search(const std::string& text) {
                int n = static_cast<int>(text.length());
                int m = static_cast<int>(pattern.length());
                if (m == 0) return 0;
                if (n < m) return -1;
                int i = 0, j = 0;
                while (i < n) {
                    if (pattern[j] == text[i]) {
                        i++; j++;
                    }
                    if (j == m) return i - j;
                    else if (i < n && pattern[j] != text[i]) {
                        if (j != 0) j = lps[j - 1];
                        else i++;
                    }
                }
                return -1;
            }
        };

        // LSD Radix Sort for strings of digits
        class radix_sort {
        private:
            int get_digit(const std::string& str, int d) {
                if (d >= static_cast<int>(str.length())) return 0;
                return str[str.length() - 1 - d] - '0';
            }
            int get_max_digits(const std::vector<std::string>& arr) {
                int max_digits = 0;
                for (const auto& s : arr) max_digits = std::max(max_digits, static_cast<int>(s.length()));
                return max_digits;
            }
            void counting_sort_by_digit(std::vector<std::string>& arr, int digit_pos) {
                const int RADIX = 10;
                int n = static_cast<int>(arr.size());
                std::vector<std::string> output(n);
                std::vector<int> count(RADIX, 0);
                for (int i = 0; i < n; i++) count[get_digit(arr[i], digit_pos)]++;
                for (int i = 1; i < RADIX; i++) count[i] += count[i - 1];
                for (int i = n - 1; i >= 0; i--) {
                    int digit = get_digit(arr[i], digit_pos);
                    output[count[digit] - 1] = arr[i];
                    count[digit]--;
                }
                for (int i = 0; i < n; i++) arr[i] = output[i];
            }
        public:
            void lsd(std::vector<std::string>& arr) {
                if (arr.empty()) return;
                int max_digits = get_max_digits(arr);
                for (int d = 0; d < max_digits; d++) counting_sort_by_digit(arr, d);
            }
        };

        // 3-Way Radix Quicksort for strings
        namespace three_way_radix_quicksort {
            inline int char_at(const std::string& s, int d) {
                return d < static_cast<int>(s.length()) ? s[d] : -1;
            }

            inline void sort_recursive(std::vector<std::string>& arr, int low, int high, int d) {
                if (high <= low) return;
                int lt = low, gt = high;
                int v = char_at(arr[low], d);
                int i = low + 1;
                while (i <= gt) {
                    int t = char_at(arr[i], d);
                    if (t < v) std::swap(arr[lt++], arr[i++]);
                    else if (t > v) std::swap(arr[i], arr[gt--]);
                    else i++;
                }
                sort_recursive(arr, low, lt - 1, d);
                if (v >= 0) sort_recursive(arr, lt, gt, d + 1);
                sort_recursive(arr, gt + 1, high, d);
            }

            inline void sort(std::vector<std::string>& arr) {
                if (arr.empty()) return;
                sort_recursive(arr, 0, static_cast<int>(arr.size()) - 1, 0);
            }
        }

        // base class for pattern matching algorithms
        class PatternMatcher {
        protected:
            std::string pattern;
            int patternLength;
        public:
            explicit PatternMatcher(const std::string& pat)
                : pattern(pat), patternLength(static_cast<int>(pat.length())) {
            }
            virtual int search(const std::string& text) = 0;
            virtual ~PatternMatcher() = default;
        };

        // generic swap used in sorting algorithms
        template<typename T>
        inline void exch(std::vector<T>& arr, int i, int j) {
            std::swap(arr[i], arr[j]);
        }
    }
}

#endif // MYUTILS_H