# How to make this book?

Using `docsify` to view markdown files, which has been Dockered in `dawneve/docsify:4.4.4`.



## (1) Start the environment in Docker

```
$ docker pull dawneve/docsify:4.4.4

$ docker run -it -d --name docsify -p 8003:3000 -v /home/wangjl/data/project/learnCpp:/home/docsify/learnCpp dawneve/docsify:4.4.4 bash
$ docker exec -it docsify bash

Init the docs
# cd /home/docsify/learnCpp
# docsify init docs
yes.

Start the server on port 3000:
# docsify serve docs

Browser on host:
http://192.168.2.120:8003/#/
```



## (2) add new user in containner

```
$ id #check your uid on host
uid=1001(wangjl) gid=1001(wangjl) groups=1001(wangjl),1004(docker) 

I added a user named tom when making this image:
if(0){
	# useradd -s /bin/bash -d /home/docsify  -m docsify -u 1001
	# passwd docsify
	# chown -R docsify /home/docsify
}

Change the uid of user tom in the containner to your id on the host as shown above.
# usermod -u 1001 tom

Change owner of these files in the containner
# chown -R tom *


Start the server on port 3000/ host 8003
# docsify serve docs
```

Then we can:
* Editing while viewing
* Then we can edit md files on the host with VIM or other text editer like vsCode through ssh.






## (3) add side bar

```
$ cd docs/
$ vim index.html
<script> window.$docsify = { loadSidebar: true } </script> 

$ vim _sidebar.md
* [README](README.md)
* Part O Preface
    * [Make this book](A0/1_readme.md)
    * [Resource](A0/2_resource.md)
* Part I Basics
    * [README](A1/1_readme.md)
* [Part II Class](A2/1_readme.md)
* [Part III template](A3/1_readme.md)
* [Part IV algorithm](A4/1_readme.md)
```

Control the sub menu shown level:
```
<script>
  window.$docsify = {
    loadSidebar: true,
    subMaxLevel: 3
  }
</script>
```


Overwrite _sidebar.md in nested folds:
```
<script>
  window.$docsify = {
    loadSidebar: true,
    alias: {
      '/.*/_sidebar.md': '/_sidebar.md',
      '/.*/_navbar.md': '/_navbar.md',
    }
  }
</script>
```





## (4) add top menu

When the menu are very few, just edit index.html
```
<body>
  <nav>
    <a href="#/">项目</a>
    <a href="#/home1">home1</a>
    <a href="#/bar/a">bar/a</a>
  </nav>
</body>
```

Another better way:
```
<script>
  window.$docsify = {
    loadNavbar: true
  }
</script>


$ vim _navbar.md
* [Basic](A1/1_readme)
* [Class](A2/1_readme)
* Help
	* [README](README)
	* [Editing Guid](A0/1_readme)
```




## (5) add cover

Default cover is ./README.md, but we can add one.

```
<script>
  window.$docsify = {
    coverpage: true
  }
</script>

$ vim _coverpage.md
![logo](images/logo/icon.svg)
# My C++ docs
## 个人文档网站
> 一个神奇的文档网站生成工具 docsify
* Simple and lightweight (~12kb gzipped)
* Multiple themes
* Not build static html files

[GitHub](https://github.com/DawnEve/learn_C)
[Get Started](/A0/1_readme)
```



## (6) save source files to local

Save css and js to local, prevant loading…… problem.

```
$ vim index.html
<link rel="stylesheet" href="static/css/vue.css">
<script src="static/js/docsify.min.js"></script>

$ mkdir static
$ mkdir static/css
$ mkdir static/js

Save the css and js files.
$ wget https://cdn.jsdelivr.net/npm/docsify@4/lib/themes/vue.css -O static/css/vue.css
$ wget https://cdn.jsdelivr.net/npm/docsify@4 -O static/js/docsify.min.js
```



## (7) Other tips

> You need to create a `.nojekyll` in `./docs` to prevent GitHub Pages from ignoring files that begin with an underscore.




## (8) Push to github

```
$ git remote add origin https://github.com/DawnEve/learnCpp.git
http/https 不能用了。
$ git remote add origin git@eve:DawnEve/learnCpp.git
fatal: remote origin already exists. 

$ git remote rm origin

I am using multiple username on one machine.
$ git remote add origin git@eve:DawnEve/learnCpp.git
$ git push origin master
```

The repo of this docs: `https://github.com/DawnEve/learnCpp`




## (9) resume 

When power off, start the service again.

```
$ docker start docsify
$ docker exec -it docsify bash

# cd /home/docsify/learnCpp

Start the server on port 3000:
# docsify serve docs
```




## Refer

- https://docsify.js.org/#/?id=docsify
- https://github.com/docsifyjs/docsify/blob/develop/docs/_sidebar.md
- https://jingping-ye.github.io/docsify-docs-zh/#/
