import os

def main():
    try:

        script_dir = os.path.dirname(__file__)  # 获取脚本所在目录
        with open(os.path.join(script_dir, "poker2.in"), "r") as fin, \
            open(os.path.join(script_dir, "poker2.out"), "w") as fout:

            cards = set()
            n = int(fin.readline().strip())

            for _ in range(n):
                card = fin.readline().strip()
                cards.add(card)

            remaining_cards = 52 - len(cards)
            fout.write(f"{remaining_cards}\n")
            print(f"还需要：{remaining_cards} 张牌。")

    except IOError:
        print("无法打开文件")

if __name__ == "__main__":
    main()
