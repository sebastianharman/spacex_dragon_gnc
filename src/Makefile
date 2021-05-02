spacex_dragon_gnc : main.o virtual_key_press.o sim_data.o gnc_loop.o
	g++ -o spacex_dragon_gnc main.o virtual_key_press.o sim_data.o gnc_loop.o

main.o : main.cpp
	g++ -c main.cpp

virtual_key_press.o : virtual_key_press.cpp virtual_key_press.h
	g++ -c virtual_key_press.cpp virtual_key_press.h

sim_data.o : sim_data.cpp sim_data.h
	g++ -c sim_data.cpp sim_data.h

gnc_loop.o : gnc_loop.cpp gnc_loop.h
	g++ -c gnc_loop.cpp gnc_loop.h

clean :
	rm *.o spacex_dragon_gnc *.gch