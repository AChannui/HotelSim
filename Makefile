default:
	@echo "use 'make build'"

build:
	docker build -t clion .

shell:
	docker run --rm -it -v $(HOME):$(HOME) --workdir /Users/alex/CLionProjects/CS4348OS_project2 clion

build-centos:
	docker build -f Dockerfile.centos -t clion-centos .

shell-centos:
	docker run --rm -it -v $(HOME):$(HOME) --workdir /Users/alex/CLionProjects/CS4348OS_project2 clion-centos

export:
	git archive --prefix=CS4348OS_project2/ -o ../CS4348OS_project2.tar HEAD
	gzip -f ../CS4348OS_project2.tar

tar:
	tar -zcv --exclude .git --exclude 'cmake*' --exclude .idea -f ../CS4348OS_project2.tar.gz -C .. CS4348OS_project2

cs1:
	scp ../CS4348OS_project2.tar.gz cs1:
	ssh cs1 "rm -rf CS4348OS_project2 build"
	ssh cs1 "tar -xvf CS4348OS_project2.tar.gz &&  mkdir build && cd build && cmake  -DCMAKE_BUILD_TYPE=Debug ../CS4348OS_project2 && make && ./CS4348OS_project2"
