all: submake 

submake:
	$(MAKE) -C ${CURDIR}/src/

.PHONY: clean

clean:
	 make clean -C ${CURDIR}/src/ 
