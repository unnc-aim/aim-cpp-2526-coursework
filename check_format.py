#!/usr/bin/env python3
"""
C++ 代码格式检查脚本
根据嵌入式工程代码规范检查代码格式
"""

import re
import sys
from pathlib import Path


class FormatChecker:
    def __init__(self):
        self.violations = []
        self.score_deduction = 0

    def check_file(self, filepath):
        """检查单个文件"""
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
            lines = content.split('\n')

        filename = Path(filepath).name
        print(f"\n检查文件: {filename}")

        # 检查各项规范
        self.check_function_names(content, filename)
        self.check_variable_names(content, filename)
        self.check_class_names(content, filename)
        self.check_macro_names(content, filename)
        self.check_global_variables(content, filename)

        if filename.endswith('.h'):
            self.check_header_guards(content, filename)
            self.check_header_structure(content, filename)

        if filename.endswith('.cpp'):
            self.check_cpp_structure(content, filename)

    def check_function_names(self, content, filename):
        """检查函数名：所有函数（包括类成员函数）应为全小写加下划线"""
        # 1. 检查构造函数（没有返回类型）
        constructor_pattern = r'^([A-Z][a-zA-Z0-9]*)::([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*(?:const)?\s*[{;]'
        constructor_matches = re.finditer(
            constructor_pattern, content, re.MULTILINE)

        for match in constructor_matches:
            class_name = match.group(1)
            func_name = match.group(2)

            # 检查构造函数名是否与类名匹配
            if func_name != class_name:
                self.add_violation(
                    f"构造函数名 '{func_name}' 应与类名 '{class_name}' 相同", filename)
                continue

            # 构造函数名应该是 PascalCase（首字母大写），这里不检查命名规范
            continue

        # 2. 检查类成员函数（有返回类型）
        member_pattern = r'\b(?:void|int|bool|float|double|char|string|std::string|auto)\s+[A-Z][a-zA-Z0-9]*::\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*(?:const)?\s*[{;]'
        member_matches = re.finditer(member_pattern, content)

        for match in member_matches:
            func_name = match.group(1)

            # 跳过构造函数和析构函数
            # 从匹配的文本中提取类名
            full_match = match.group(0)
            class_match = re.search(r'([A-Z][a-zA-Z0-9]*)::', full_match)
            if class_match:
                class_name = class_match.group(1)
                # 跳过构造函数和析构函数
                if func_name == class_name or func_name == '~' + class_name:
                    continue

            # 检查是否符合全小写加下划线规范
            if not re.match(r'^[a-z][a-z0-9_]*$', func_name):
                self.add_violation(f"类成员函数 '{func_name}' 应使用全小写加下划线", filename)

        # 3. 检查普通函数（不在类中的函数）
        pattern = r'\b(?:void|int|bool|float|double|char|string|std::string|auto)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*(?:const)?\s*[{;]'
        matches = re.finditer(pattern, content)

        for match in matches:
            func_name = match.group(1)

            # 跳过类成员函数（已经在上面检查过了）
            context_before = content[max(0, match.start()-50):match.start()]
            if '::' in context_before:
                continue

            # 检查是否符合全小写加下划线规范
            if not re.match(r'^[a-z][a-z0-9_]*$', func_name):
                self.add_violation(f"函数名 '{func_name}' 应使用全小写加下划线", filename)

    def check_variable_names(self, content, filename):
        """检查变量名：应为小驼峰（成员变量除外）"""
        # 这个检查比较复杂，这里做简化处理
        # 检查局部变量声明
        pattern = r'\b(?:int|bool|float|double|char|string|std::string|auto)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*[=;]'
        matches = re.finditer(pattern, content)

        for match in matches:
            var_name = match.group(1)
            # 跳过常量（全大写）
            if var_name.isupper():
                continue
            # 跳过成员变量（带下划线后缀）
            if var_name.endswith('_'):
                continue

            # 检查是否符合小驼峰规范（首字母小写）
            if var_name[0].isupper():
                self.add_violation(f"变量名 '{var_name}' 应使用小驼峰（首字母小写）", filename)

    def check_class_names(self, content, filename):
        """检查类名：应为大驼峰"""
        pattern = r'\bclass\s+([a-zA-Z_][a-zA-Z0-9_]*)'
        matches = re.finditer(pattern, content)

        for match in matches:
            class_name = match.group(1)
            # 检查是否符合大驼峰规范（首字母大写，无下划线）
            if not re.match(r'^[A-Z][a-zA-Z0-9]*$', class_name):
                self.add_violation(f"类名 '{class_name}' 应使用大驼峰（无下划线）", filename)

    def check_macro_names(self, content, filename):
        """检查宏定义：应为全大写加下划线"""
        pattern = r'#define\s+([a-zA-Z_][a-zA-Z0-9_]*)'
        matches = re.finditer(pattern, content)

        for match in matches:
            macro_name = match.group(1)
            # 跳过头文件保护宏
            if macro_name.endswith('_H') or macro_name.endswith('_HPP'):
                continue

            # 检查是否符合全大写加下划线规范
            if not re.match(r'^[A-Z][A-Z0-9_]*$', macro_name):
                self.add_violation(f"宏定义 '{macro_name}' 应使用全大写加下划线", filename)

    def check_global_variables(self, content, filename):
        """检查全局变量：应避免使用，或使用 static"""
        # 检查文件级别的变量定义（不在函数内）
        # 简化检查：查找不在类或函数内的变量定义
        lines = content.split('\n')
        in_function = 0
        in_class = 0

        for i, line in enumerate(lines):
            stripped = line.strip()

            # 跟踪大括号层级
            in_function += line.count('{') - line.count('}')
            if 'class ' in line:
                in_class += 1

            # 在全局作用域检查变量定义
            if in_function == 0 and in_class == 0:
                var_pattern = r'^\s*(?:int|bool|float|double|char|string|std::string)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*[=;]'
                match = re.match(var_pattern, stripped)
                if match and not stripped.startswith('static'):
                    var_name = match.group(1)
                    self.add_violation(
                        f"全局变量 '{var_name}' 应使用 static 或避免使用", filename, severity="warning")

    def check_header_guards(self, content, filename):
        """检查头文件保护宏"""
        if not content.strip().startswith('#ifndef'):
            self.add_violation("头文件应使用 #ifndef 保护宏", filename)

    def check_header_structure(self, content, filename):
        """检查头文件结构（简化版）"""
        # 这里可以添加更详细的结构检查
        pass

    def check_cpp_structure(self, content, filename):
        """检查 .cpp 文件结构（简化版）"""
        # 这里可以添加更详细的结构检查
        pass

    def add_violation(self, message, filename, severity="error"):
        """添加违规记录"""
        self.violations.append({
            'message': message,
            'file': filename,
            'severity': severity
        })
        print(f"  ❌ {message}")

    def calculate_score(self):
        """计算扣分"""
        if not self.violations:
            return 0

        # 第一处违规 -10 分
        # 后续每处 -2 分
        # 最多扣 20 分
        error_count = sum(
            1 for v in self.violations if v['severity'] == 'error')

        if error_count == 0:
            return 0
        elif error_count == 1:
            return 10
        else:
            return min(20, 10 + (error_count - 1) * 2)

    def print_summary(self):
        """打印检查摘要"""
        deduction = self.calculate_score()

        print("\n" + "="*60)
        print("代码格式检查结果")
        print("="*60)

        if not self.violations:
            print("✅ 未发现格式问题")
            print("扣分: 0")
        else:
            print(f"发现 {len(self.violations)} 处格式问题")
            print(f"扣分: -{deduction}")

            if deduction > 0:
                print("\n详细问题列表:")
                for i, v in enumerate(self.violations, 1):
                    print(f"{i}. [{v['file']}] {v['message']}")

        print("="*60)
        return deduction


def main():
    if len(sys.argv) < 2:
        print("用法: python check_format.py <文件1> [文件2] ...")
        sys.exit(1)

    checker = FormatChecker()

    for filepath in sys.argv[1:]:
        if Path(filepath).exists():
            checker.check_file(filepath)
        else:
            print(f"警告: 文件不存在: {filepath}")

    deduction = checker.print_summary()

    # 返回扣分作为退出码（用于 CI）
    sys.exit(deduction if deduction > 0 else 0)


if __name__ == '__main__':
    main()
