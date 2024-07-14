CC := gcc

all: axi_mm axi_lite perf

axi_mm: axi_mm.cc
	$(CC) axi_mm.cc -o axi_mm

axi_lite: axi_lite.cc
	$(CC) axi_lite.cc -o axi_lite

perf: perf.cc
	$(CC) perf.cc -o perf

clean:
	rm -rf axi_mm axi_lite perf
