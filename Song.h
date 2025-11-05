#pragma once
/**
 * @file Song.h
 * @brief Song 类的头文件定义。
 *
 * 考核项目：MiniDJ 播放列表（单类项目）
 * 这是“接口版”头文件，定义了 Song 类的公共接口。
 * 实现需要在 Song.cpp 中完成。
 */

#include <iosfwd> // 仅用于 ostream 的前向声明，避免引入 <iostream> 完整头文件
#include <string>
#include <vector>

// ----------------------------------------------------------------------------
// 注意：头文件 (.h) 中【禁止】使用 "using namespace std;"
// 这会污染所有 include 本文件的代码的命名空间，导致潜在的命名冲突。
// 因此，在 .h 文件中，我们必须坚持使用 "std::" 前缀。
// ----------------------------------------------------------------------------

class Song {
    // --- 私有成员 ---
  private:
    int id_{-1};                    // 歌曲唯一 ID (>=1)，构造成功后分配
    std::string title_;             // 标题
    std::string artist_;            // 艺人
    int duration_sec_{0};           // 时长（秒）
    int rating_{3};                 // 评分 1..5，默认 3
    std::vector<std::string> tags_; // 标签集合 (如：rock, jp, live)

    bool valid_{false}; // 标记：本对象的数据是否有效（用于替代异常）

    // --- 静态成员 ---
    static int next_id_; // 用于生成下一个 ID 的静态计数器

    // --- 公共接口 ---
  public:
    /**
     * @brief 构造函数。
     * * @details
     * 在构造时进行基本的数据校验。
     * 要求：标题/艺人非空；时长 > 0；评分在 [1,5] 区间。
     * - 如果数据非法：打印提示，保持 valid_ = false。
     * - 如果数据合法：分配新 ID (id_ = next_id_++)，并设置 valid_ = true。
     *
     * @param title        标题
     * @param artist       艺人
     * @param duration_sec 时长（秒），必须为正整数
     * @param rating       评分（1-5），默认为 3
     */
    Song(const std::string &title,
         const std::string &artist,
         int duration_sec,
         int rating = 3);

    // --- 实现提示 ---
    // 1. 使用 trim_copy() 清理输入的 'title' 和 'artist'。
    // 2. 校验清理后的数据：
    //    - 如果清理后的标题为空，打印错误。
    //    - 如果清理后的艺术家为空，打印错误。
    //    - 如果 duration_sec <= 0，打印错误。
    //    - 如果 rating < 1 或 rating > 5，打印错误。
    // 3. 如果上述任何校验失败：
    //    - 打印一条错误信息。
    //    - 保持 valid_ = false（默认值）。
    //    - 直接 return，中断构造。
    // 4. 如果所有校验都通过：
    //    - 分配 ID: id_ = next_id_++;
    //    - 将（清理后的）title, artist, duration, rating 赋值给成员变量。
    //    - 设置 valid_ = true;

    // --- 只读访问器 (Getters) ---

    int id() const { return id_; }
    bool is_valid() const { return valid_; }
    const std::string &title() const { return title_; }
    const std::string &artist() const { return artist_; }
    int duration() const { return duration_sec_; }
    int rating() const { return rating_; }
    const std::vector<std::string> &tags() const { return tags_; }

    // --- 修改器 (Setters) ---
    // (非法输入将打印提示并返回 false)

    /**
     * @brief 设置歌曲标题（校验后）。
     * @param t 新的标题。
     * @return 如果标题有效并已设置，返回 true；否则返回 false。
     */
    bool set_title(const std::string &t);

    // --- 实现提示 ---
    // 1. 使用 trim_copy() 清理输入 't'。
    // 2. 检查清理后的字符串是否为空。
    // 3. 如果为空，打印错误并返回 false。
    // 4. 如果有效，将清理后的字符串赋值给 title_ 并返回 true。

    /**
     * @brief 设置艺术家（校验后）。
     * @param a 新的艺术家。
     * @return 如果艺术家有效并已设置，返回 true；否则返回 false。
     */
    bool set_artist(const std::string &a);

    // --- 实现提示 ---
    // 1. 使用 trim_copy() 清理输入 'a'。
    // 2. 检查清理后的字符串是否为空。
    // 3. 如果为空，打印错误并返回 false。
    // 4. 如果有效，将清理后的字符串赋值给 artist_ 并返回 true。

    /**
     * @brief 设置时长（校验后）。
     * @param sec 新的时长（秒），必须 > 0。
     * @return 如果时长有效并已设置，返回 true；否则返回 false。
     */
    bool set_duration(int sec);

    // --- 实现提示 ---
    // 1. 检查 sec 是否 > 0。
    // 2. 如果不是，打印错误并返回 false。
    // 3. 如果有效，将 sec 赋值给 duration_sec_ 并返回 true。

    /**
     * @brief 设置评分（校验后）。
     * @param r 新的评分，必须在 [1, 5] 区间内。
     * @return 如果评分有效并已设置，返回 true；否则返回 false。
     */
    bool set_rating(int r);

    // --- 实现提示 ---
    // 1. 检查 (r >= 1 && r <= 5)。
    // 2. 如果不是，打印错误并返回 false。
    // 3. 如果有效，将 r 赋值给 rating_ 并返回 true。

    // --- 标签管理 ---

    /**
     * @brief 添加一个新标签（进行大小写不敏感的重复检查）。
     * @param tag 要添加的标签。
     * @return 如果标签被成功添加，返回 true；如果标签为空或已存在，返回 false。
     */
    bool add_tag(const std::string &tag);

    // --- 实现提示 ---
    // 1. 使用 trim_copy() 清理 'tag'。
    // 2. 检查清理后的标签是否为空，为空则打印错误并返回 false。
    // 3. 遍历已有的 tags_ 向量：
    //    - 将 'tag' 和每个已有标签都用 to_lower_copy() 转换为小写进行比较。
    //    - 如果发现（忽略大小写的）重复，打印提示并返回 false。
    // 4. 如果不重复，将（清理后的、原始大小写的）'tag' push_back 到 tags_，并返回 true。

    /**
     * @brief 移除一个已有标签（大小写不敏感）。
     * @param tag 要移除的标签。
     * @return 如果找到并移除了标签，返回 true；如果未找到，返回 false。
     */
    bool remove_tag(const std::string &tag);

    // --- 实现提示 ---
    // 1. 使用 trim_copy() 和 to_lower_copy() 清理并转换 'tag' 为小写，用于比较。
    // 2. 遍历 tags_ 向量（建议使用带索引的 for 循环）：
    //    - 将当前遍历到的标签（例如 tags_[i]）也用 to_lower_copy() 转为小写。
    //    - 如果两者相等，说明找到：
    //      - 使用 tags_.erase(tags_.begin() + i) 来移除该元素。
    //      - 返回 true。
    // 3. 如果循环结束都没找到，打印提示并返回 false。

    // --- 功能函数 ---

    /**
     * @brief 检查歌曲是否匹配关键词（大小写不敏感的子串匹配）。
     *
     * @param kw 关键词。
     * @return 如果 title, artist 或任何一个 tag 中包含该关键词（忽略大小写），返回 true。
     */
    bool matches_keyword(const std::string &kw) const;

    // --- 实现提示 ---
    // 1. 使用 trim_copy() 和 to_lower_copy() 清理并转换 'kw'。
    // 2. 如果 'kw' 为空，直接返回 false。
    // 3. 将 title_ 和 artist_ 也转换为小写副本。
    // 4. 使用 string::find() 检查小写 'kw' 是否存在于：
    //    - 小写的 title_ 中？
    //    - 小写的 artist_ 中？
    //    - 任何一个（也转为小写的）tag 中？
    // 5. 只要任意一个匹配（find() != string::npos），就立刻返回 true。
    // 6. 如果所有检查都不匹配，返回 false。

    // --- 友元函数 (操作符重载) ---

    /**
     * @brief 重载 << 操作符，用于友好地打印歌曲信息到输出流。
     * @param os 输出流 (例如 std::cout)。
     * @param s 要打印的 Song 对象。
     * @return 输出流。
     */
    friend std::ostream &operator<<(std::ostream &os, const Song &s);

    // --- 实现提示 ---
    // 格式: [#id] Artist - Title (时长s) 评分* [tags: a, b]
    //
    // 1. 打印 ID, Artist, Title, Duration。
    // 2. 打印评分：可以使用 string(s.rating_, '*') 来构造星号字符串。
    // 3. 打印标签：
    //    - 检查 s.tags_ 是否为空 (s.tags_.empty())。
    //    - 如果不为空，调用 join_tags(s.tags_) 获取拼接后的字符串。
    //    - 打印 " [tags: ...]" 部分。

    /**
     * @brief 重载 < 操作符，定义歌曲的排序规则。
     * * 排序逻辑：
     * 1. 评分（rating）高的排前面（降序）。
     * 2. 评分相同时，标题（title）按字典序排前面（升序）。
     * 3. 标题也相同时，ID 小的排前面（升序）。
     *
     * @param a 歌曲 A。
     * @param b 歌曲 B。
     * @return 如果 A "小于" B (即 A 应该排在 B 前面)，返回 true。
     */
    friend bool operator<(const Song &a, const Song &b);

    // --- 实现提示 ---
    // 用于 std::sort(..., std::less<Song>()) 或默认的 std::sort()。
    // sort 是升序排序，它会把 "true" (a < b) 的元素放前面。
    //
    // 1. 比较评分（降序）：
    //    if (a.rating_ > b.rating_) return true;  // A 评分高，A 排前面
    //    if (a.rating_ < b.rating_) return false; // B 评分高，B 排前面
    //
    // 2. 评分相等，比较标题（升序）：
    //    if (a.title_ < b.title_) return true;  // A 标题靠前，A 排前面
    //    if (a.title_ > b.title_) return false; // B 标题靠前，B 排前面
    //
    // 3. 标题相等，比较 ID（升序）：
    //    return a.id_ < b.id_; // A 的 ID 小，A 排前面
};
