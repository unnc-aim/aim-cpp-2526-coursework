/**
 * @file main.cpp
 * @brief MiniDJ 音乐播放列表管理器的命令行界面 (CLI) 主程序。
 */

#include "Song.h"

#include <algorithm>   // std::sort / std::find_if / std::find_if_not
#include <iostream>
#include <string>
#include <vector>

// 使用 std 命名空间
using namespace std;

// --- 字符串与输入辅助工具 ---

/**
 * @brief 返回字符串的副本，移除了首尾的空白字符。
 * @param s 输入字符串。
 * @return 去除首尾空白后的字符串。
 */
static string trim_copy(const string& s) {
    auto first = find_if_not(s.begin(), s.end(),
                             [](const unsigned char ch){ return isspace(ch); });
    auto last  = find_if_not(s.rbegin(), s.rend(),
                             [](const unsigned char ch){ return isspace(ch); }).base();
    if (first >= last) return {};
    return {first, last};
}

/**
 * @brief 从控制台读取一整行输入（允许包含空格）。
 * @param prompt 显示给用户的提示信息。
 * @return 用户输入的（未 trim 的）原始字符串。
 */
static string read_line(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

/**
 * @brief 尝试将字符串解析为正整数。
 * @param text 要解析的（可能包含空白的）字符串。
 * @param[out] out 如果解析成功，整数结果存储在此处。
 * @return 如果字符串是纯数字且非空，返回 true；否则返回 false。
 */
static bool parse_positive_int(const string& text, int& out) {
    const string s = trim_copy(text);
    if (s.empty()) return false;

    int value = 0;
    for (const char ch : s) {
        if (!isdigit(static_cast<unsigned char>(ch))) return false;
        value = value * 10 + (ch - '0');
    }
    out = value;
    return true;
}

/**
 * @brief 从控制台读取一个必须的正整数。
 * 如果输入无效（空、非数字、<=0），将循环提示。
 * @param prompt 显示给用户的提示信息。
 * @return 一个有效的正整数。
 */
static int read_required_positive_int(const string& prompt) {
    for (;;) {
        string line = read_line(prompt);
        int x = 0;
        if (parse_positive_int(line, x) && x > 0) {
            return x;
        }
        cout << "[提示] 请输入正整数。\n";
    }
}

/**
 * @brief 根据 ID 在播放列表中查找歌曲。
 * @param pl 播放列表 (vector)。
 * @param id 要查找的歌曲 ID。
 * @return 如果找到，返回指向该 Song 对象的指针；否则返回 nullptr。
 */
static Song* find_by_id(vector<Song>& pl, const int id) {
    for (auto& s : pl) {
        if (s.id() == id) {
            return &s; // 返回找到的 Song 对象的地址
        }
    }
    return nullptr; // 未找到
}

// --- 核心功能操作 ---

/**
 * @brief (操作 1) 添加新歌曲。
 * 引导用户输入信息，构造 Song 对象。
 * 只有 Song 构造函数确认合法 (s.is_valid()) 后才添加入列。
 */
static void op_add(vector<Song>& pl) {
    string title  = trim_copy(read_line("标题: "));
    string artist = trim_copy(read_line("艺人: "));
    int duration = read_required_positive_int("时长(秒): ");

    // 处理评分：允许回车使用默认值 3
    string rt_str = read_line("评分(1-5，回车默认3): ");
    int rating = 3; // 默认值
    int temp_rating = 0;
    if (!rt_str.empty()) {
        if (parse_positive_int(rt_str, temp_rating) && temp_rating >= 1 && temp_rating <= 5) {
            rating = temp_rating;
        } else {
            cout << "[提示] 评分需在 1..5，已用默认 3。\n";
        }
    }

    Song s(title, artist, duration, rating);

    // 构造函数会进行校验
    if (!s.is_valid()) {
        cout << "[失败] 歌曲信息不合法（如标题为空），未添加。\n";
        return;
    }

    pl.push_back(s);
    cout << "[已添加] " << pl.back() << "\n";
}

/**
 * @brief (操作 2) 列出所有歌曲。
 */
static void op_list(const vector<Song>& pl) {
    if (pl.empty()) {
        cout << "[空] 播放列表为空。\n";
        return;
    }
    for (const auto& s : pl) {
        cout << s << "\n";
    }
}

/**
 * @brief (操作 3) 按关键词搜索歌曲。
 * 搜索是大小写不敏感的。
 */
static void op_search(const vector<Song>& pl) {
    const string kw = trim_copy(read_line("关键词: "));
    if (kw.empty()) {
        cout << "[提示] 关键词不能为空。\n";
        return;
    }

    int cnt = 0;
    for (const auto& s : pl) {
        if (s.matches_keyword(kw)) {
            if (cnt == 0) {
                cout << "[搜索结果]\n";
            }
            cout << s << "\n";
            ++cnt;
        }
    }

    if (cnt == 0) {
        cout << "[提示] 未找到匹配项。\n";
    }
}

/**
 * @brief (操作 4) 修改现有歌曲信息。
 * 允许用户对指定 ID 的歌曲的各项属性进行修改，留空表示不修改。
 */
static void op_edit(vector<Song>& pl) {
    int id = read_required_positive_int("要修改的歌曲 id: ");
    Song* p = find_by_id(pl, id);
    if (!p) {
        cout << "[提示] 未找到该 id。\n";
        return;
    }

    cout << "当前： " << *p << "\n（留空=不改）\n";

    // 读取新信息
    string new_title  = trim_copy(read_line("新标题: "));
    string new_artist = trim_copy(read_line("新艺人: "));
    string new_dur_str = read_line("新时长(秒): ");
    string new_rate_str = read_line("新评分(1-5): ");

    // 按需更新（只有非空输入才尝试更新）
    if (!new_title.empty())  p->set_title(new_title);
    if (!new_artist.empty()) p->set_artist(new_artist);

    int dur = 0;
    if (!new_dur_str.empty()) {
        if (parse_positive_int(new_dur_str, dur) && dur > 0) {
            p->set_duration(dur);
        } else {
            cout << "[提示] 时长需正整数，已忽略。\n";
        }
    }

    int rate = 0;
    if (!new_rate_str.empty()) {
        if (parse_positive_int(new_rate_str, rate) && rate >= 1 && rate <= 5) {
            p->set_rating(rate);
        } else {
            cout << "[提示] 评分需在 1..5，已忽略。\n";
        }
    }

    cout << "更新后： " << *p << "\n";
}

/**
 * @brief (操作 7) 删除指定 ID 的歌曲。
 */
static void op_delete(vector<Song>& pl) {
    int id = read_required_positive_int("要删除的歌曲 id: ");

    // 使用 std::find_if 和 lambda 表达式来定位迭代器
    auto it = find_if(pl.begin(), pl.end(), [id](const Song& s){
        return s.id() == id;
    });

    if (it == pl.end()) {
        cout << "[提示] 未找到该 id。\n";
        return;
    }

    cout << "[已删除] " << *it << "\n";
    pl.erase(it); // 根据迭代器删除
}

/**
 * @brief (操作 5) 为指定 ID 的歌曲添加标签。
 */
static void op_tag_add(vector<Song>& pl) {
    int id = read_required_positive_int("添加标签的歌曲 id: ");
    Song* p = find_by_id(pl, id);
    if (!p) {
        cout << "[提示] 未找到该 id。\n";
        return;
    }

    string tg = trim_copy(read_line("标签内容: "));
    if (tg.empty()) {
        cout << "[提示] 空标签忽略。\n";
        return;
    }

    // add_tag 内部会处理重复和打印提示
    if (p->add_tag(tg)) {
        cout << "[完成] " << *p << "\n";
    }
}

/**
 * @brief (操作 6) 移除指定 ID 歌曲的某个标签。
 */
static void op_tag_remove(vector<Song>& pl) {
    const int id = read_required_positive_int("移除标签的歌曲 id: ");
    Song* p = find_by_id(pl, id);
    if (!p) {
        cout << "[提示] 未找到该 id。\n";
        return;
    }

    const string tg = trim_copy(read_line("要移除的标签: "));
    if (tg.empty()) {
        cout << "[提示] 空输入忽略。\n";
        return;
    }

    // remove_tag 内部会处理未找到的情况和打印提示
    if (p->remove_tag(tg)) {
        cout << "[完成] " << *p << "\n";
    }
}

/**
 * @brief (操作 8) 对播放列表进行排序。
 * 排序规则依赖于 Song 定义的 operator<。
 */
static void op_sort(vector<Song>& pl) {
    sort(pl.begin(), pl.end());
    cout << "[完成] 排序已应用。\n";
}

/**
 * @brief 打印主菜单。
 */
static void print_menu() {
    cout << "\n=== MiniDJ（接口版）===\n"
         << "1) 添加   2) 列表   3) 搜索   4) 修改   5) 标签+   6) 标签-   7) 删除   8) 排序   0) 退出\n";
}

// --- 主程序 ---

int main() {
    // 确保 Windows 终端能正确显示 UTF-8 字符（如果需要）
    #ifdef _WIN32
        system("chcp 65001");
    #endif

    vector<Song> playlist;

    for (;;) {  // ;;表示无限循环直到用户选择退出
        print_menu();
        string op_text = read_line("> ");

        int op = -1;
        parse_positive_int(op_text, op); // 尝试解析

        // 使用扁平的 if-else 结构进行操作分发
        if (op == 1) op_add(playlist);
        else if (op == 2) op_list(playlist);
        else if (op == 3) op_search(playlist);
        else if (op == 4) op_edit(playlist);
        else if (op == 5) op_tag_add(playlist);
        else if (op == 6) op_tag_remove(playlist);
        else if (op == 7) op_delete(playlist);
        else if (op == 8) op_sort(playlist);
        else if (op == 0) {
            cout << "Bye!\n";
            break;
        }
        else {
            cout << "[提示] 无效选项。\n";
        }
    }
    return 0;
}