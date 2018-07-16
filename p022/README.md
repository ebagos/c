# メモリ操作

## 問題
5000個以上の名前が書かれている46Kのテキストファイル names.txt を用いる. まずアルファベット順にソートせよ.<br>

のち, 各名前についてアルファベットに値を割り振り, リスト中の出現順の数と掛け合わせることで, 名前のスコアを計算する.<br>

たとえば, リストがアルファベット順にソートされているとすると, COLINはリストの938番目にある. またCOLINは 3 + 15 + 12 + 9 + 14 = 53 という値を持つ. よってCOLINは 938 × 53 = 49714 というスコアを持つ.<br>

ファイル中の全名前のスコアの合計を求めよ.<br>

## ねらい
ファイルI/Oはできればいい（エラー処理を考慮していることが重要）<br>
大きなデータ＝メモリを効率よく扱う問題<br>
ポインタに苦しんでもらいたが、この程度では大したことないか？<br>