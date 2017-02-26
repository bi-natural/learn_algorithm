### Git Ignore

목적: Git에서 파일/디렉토리 무시하기 (로컬에서만 사용하고 리모트에 올리지 않음)

규칙:
  - #으로 시작하는 것은 무시함 (comment)
  - 표준 Glob 패턴 사용
  - /로 시작하는 것은 현재 디렉토리에만 적용되고 하위 디렉토리에는 적용되지 않음
  - 디텍토리와 파일은 뒤에 /가 붙으면 디렉토리
  - !로 시작되는 패턴은 ignore 패턴에서 제외

예제

```
  # 확장자가 .a로 끝나는 것은 무시
  *.a

  # 모든 *.a는 무시하지만 lib.a는 무시하지 않음
  !lib.a

  # 현재 디렉토리의 TODO 파일는 무시, sub-dir에 있는 TODO 파일은 무시하지 않음
  /TODO

  # build 라는 디렉토리는 모두 무시
  build/

  # doc 이라는 디렉토리 아래 *.txt는 무시하지만, sub-dir에 있는 .txt는 무시하지 않음
  doc/*.txt

  # doc 밑에 있는 모든 .txt 무시
  doc/**/*.txt


```

### .gitignore를 만들지 않아서 이미 쓸데없는 파일이 올라갔을때 remote 저장소를 청소하는 방법

1. .gitignore 작성

2. 모든 파일을 git index에서 제거한다. (무시대상 파일 + 전부 index)

```
  $ git rm -r --cached
```

3. 다시 Index에 추가함
```
  $ git add .
```

4. commit 한다.
```
  $ git commit -m ".gitignore 적용"
  $ git push
```


### Local repository에서 파일 무시하기

형상관리는 되어야하는데 (remote repository에 올라는 가야 함.), 경우에 따라서 로컬에서 자주 변경
하여 사용은 하는데 반영은 하지 않아도 되는 것들에 대한 관리.

임시로 변경을 무시할 수 있음.

```
# 특정 파일에 대해서 변경사항 무시하기 (예를 들어, SDK 같이 변경되지 않는 경우)

$ git update-index --assume-unchanged <file>

# 특정 파일에 대해서 변경사항 다시 추적하기

$ git update-index --no-assume-unchanged <file>

# 변경사항이 무시되고 있는 것들 찾기
$ git ls-files -v | grep '^h'

```

```
# 특정 파일에 대해 remote에 있는 것을 따로 변경하지 않음 (로컬에 있는 것은 그대로 사용)

$ git update-index --skip-worktree <file>

```
