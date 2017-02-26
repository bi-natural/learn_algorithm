## Git

- ~/.gitconfig

[user "<repository>"]
  name =
  email =

[http "<domain>"]
  sslVerify = true/false
  proxy =

예제)
```
[user]
	email = jaeho3.yang@samsung.com
	name = Jaeho Yang
[gui]
	recentrepo = D:/Work/DevOps/GitHome/celloplus_policyserver/work

[http]
	sslVerify = false
	proxy = http://70.10.15.10:8080

[https]
	sslVerify = false
	proxy = http://70.10.15.10:8080
```

### Git debugging

GIT_CURL_VERBOSE=1 git ...
