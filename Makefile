
objects=src/api-impl/commands.o src/api-impl/regex_list.o src/api/client.o src/comms/comm_in.o src/comms/comm_manager.o src/comms/comm_out.o src/discovery/discover.o src/discovery/searchpacket.o src/utility/allocator.o src/utility/charbuffer.o src/utility/debugging.o src/utility/extraction.o src/utility/formatting.o src/utility/queue.o src/utility/rbst.o src/utility/regex_wrapper.o src/utility/timing.o

all: libdigifi cli

libdigifi: api-impl $(objects)
	echo "building libdigifi"

cli: libdigifi
	echo "building cli"

api-impl: 
	echo "generating api"
	if [ ! -e ./src/api-impl ]; then mkdir ./src/api-impl; fi
	./gen/bin/gen ./version/commands.xml ./version/types.json ./src/api-impl

pcre: ext/pcre/build
	if [ ! -e ./ext/pcre/build ]; then mkdir ./ext/pcre/build; fi
	pushd ./ext/pcre/build; ../configure; make; popd



$(objects): src/api/client.h src/api-impl/types.h src/comms/comm_manager.h





clean:
	echo "cleaning"
	rm -r ./src/api-impl
	rm -r ./ext/pcre/build
