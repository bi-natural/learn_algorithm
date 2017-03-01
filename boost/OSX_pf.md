## OSX pf

- based on OpenBSD 4.3 (outdated, but it is close to OS X Yosemite PF.)
- 기존의 ipfw는 없어지고 pf만 남음

### Activation / De-activation

- enable / disable pf
```
  # pfctl -e
  # pfctl -d
```
% 이것은 단순히 pf를 사용할지 말지만을 결정하는 것임. 어떤 rule set를 쓸지에 대해서는 실제로 로딩하지 않은 상태임.

- configuration
  - macros : 사용자 정의 변수 (예: IP주소, 인터페이스 이름)
  - tables : IP주소 목록
  - options : pf동작에 대한 여러가지 옵션
  - scrub : 패킷들에 대한 정규화나 de-fragment하는 등의 처리 설정
  - translation : NAT나 redirection에 대한 설정
  - filter rule : allow/block등에 대한 설정

- control of pf

```
  # pfctl -f /etc/pf.conf     % 전체 룰을 로드함.
  # pfctl -Nf /etc/pf.conf    % NAT관련된 룰을 로드함.

  # pfctl -sn   % NAT 상태 보여주기
  # pfctl -sa   % 전체 상태 보여주기
```
### pf rules

- Lists : { } 으로 정의함

```
  { tcp udp }
  { 192.168.0.1, 10.5.32.6 }   # ,는 있었도 되고 없어도 되는 것 같음. (대부분 단일 IP주소일때는 넣는 것 같음)
  { 10.0.0.0/8, !10.1.2.3 }    # !도 있음.
  { 22 80 }
```

- macros

```
  ext_if = "fxp0"             # 변수로 정의
  block in on $ext_if from any to any
```
