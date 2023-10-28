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
	gzip ../CS4348OS_project2.tar
