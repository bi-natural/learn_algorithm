## CentOS Jenkins 설치

ref: http://titaniumspider.tistory.com/218

1. 다운로드 및 설치

jenkins의 LTS(Long-Term Support)버전에 대해 설치한다.

```
sudo wget -O /etc/yum.repos.d/jenkins.repo http://pkg.jenkins-ci.org/redhat-stable/jenkins.repo

sudo rpm --import http://pkg.jenkins-ci.org/redhat-stable/jenkins.repo

sudo yum install jenkins
```

2. (필요시) 젠킨스 포트를 변경한다.

```
$ vi /etc/sysconfig/jenkins

:
JENKINS_PORT="9000"
:

```
