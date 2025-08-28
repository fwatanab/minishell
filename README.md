# minishell

このプロジェクトの目的は、Bash のようなシンプルなシェルを作成することです。<br>

## プロジェクト仕様

このプロジェクトでは、ターミナルの対話（履歴 & 入力読み取り）を処理するために GNU の readline ライブラリを使用することが許可されています。
その他の機能については、限られた低レベル関数といくつかの POSIX システムコールのみを使用することが許可されています。

<b>使用可能な関数:</b>
```sh
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc,
free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset,
sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir,
closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
```

## 機能

### 基本機能:
- 入力したコマンドの履歴を保存
- `PATH` 変数に基づき、相対パス・絶対パスを使用した適切な実行ファイルを検索して実行
- 環境変数 (`$` に続く文字列) をその値に展開
- カレントディレクトリ内のワイルドカード `*` を処理
- `Ctrl+C`, `Ctrl+D`, `Ctrl+\` が Bash と同じように動作
- `’` (シングルクォート) によるメタキャラクタの無効化
- `"` (ダブルクォート) によるメタキャラクタの無効化（ただし `$` は展開）
- `$?` が直前の終了ステータスに展開
- `|` によるコマンドのパイプ接続
- `&&` および `||` を括弧で優先順位を指定して使用可能

### 組み込みコマンド:
- `echo` (`-n` オプション対応)
- `cd` (相対・絶対パス、`-` で OLDPWD、引数なしで HOME)
- `pwd` (オプションなし)
- `export` (オプションなし)
- `unset` (オプションなし)
- `env` (オプションなし)
- `exit [exit_status]` (オプションなし)

### リダイレクト:

- `[n]< file` → 標準入力を `file` にリダイレクト
- `[n]<< limiter` → ヒアドキュメント
- `[n]> file` → 標準出力を `file` にリダイレクト
- `[n]>> file` → 標準出力を `file` に追記

## 使用方法

現在の `minishell` は macOS で開発・テストされていますが、すべての UNIX/LINUX 系 OS で動作するはずです。

<b>必要なもの:</b>
- GCC / CLANG コンパイラ
- GNU Make
- GNU Readline ライブラリ

```sh
git clone https://github.com/fwatanab/minishell.git
cd minishell && make
./minishell
```

## 依存関係

### Homebrew を使用した readline のインストール

```sh
brew install readline
brew link --force readline
```

パスを `lib` に追加:

```sh
echo 'export C_INCLUDE_PATH="/usr/local/opt/readline/include:$C_INCLUDE_PATH"' >> ~/.zshrc
echo 'export LIBRARY_PATH="/usr/local/opt/readline/lib:$LIBRARY_PATH"' >> ~/.zshrc
source ~/.zshrc
```


